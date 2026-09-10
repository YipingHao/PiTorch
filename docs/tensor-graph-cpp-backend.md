# 张量图 C++ 后端

## 1. 目标

`TensorCppBackend` 把已经完成微分和图变换的 `NetWork` 输出成一份独立的 C++11 源文件。生成文件不依赖 Pikachu、Hyperlex 或 HyperAlgebra，只依赖 C++ 标准库。

这条路径刻意保留项目原来的两层结构：

1. 张量图负责静态形状、指标映射、广播和归约；
2. `MonoFunc` / `DiFunc` 中的符号表达式先降到 `VISA1`，再由 `SymbolicCppBackend` 生成局部数值核。

因此，符号微分得到的大型非线性表达式仍是一个融合算子，而不是重新拆成大量张量图节点。

## 2. 使用方法

原有 DSL 无须修改：

```text
print.CPU(network_name, "./output/network.cpp");
```

`BackEnd::CPUbackEnd` 现在会调用 `TensorCppBackend`。也可以从 C++ 直接使用：

```cpp
Pikachu::TensorCppBackend backend;
int status = backend.build(network, "network.cpp", "my_network");
```

生成文件导出四个 C ABI 函数：

```cpp
extern "C" std::size_t my_network_input_count();
extern "C" std::size_t my_network_parameter_count();
extern "C" std::size_t my_network_output_count();
extern "C" void my_network(
    const double* input,
    const double* parameter,
    double* output);
```

输入、参数和输出都按照 `NetWork` 对应列表的顺序拼接；每个张量内部采用 row-major 顺序。调用方负责提供计数函数所报告长度的连续 `double` 数组。

## 3. 当前支持的节点

### 3.1 叶节点

- 输入叶节点映射到扁平 `input`；
- 参数叶节点映射到扁平 `parameter`；
- 常量叶节点写入工作区；
- 微分产生的单位张量、零张量也按普通常量张量处理。

### 3.2 `MonoLinear`

后端根据指标标签而不是 `dummy/new/repeated` 计数恢复语义：

- 同时出现在输入和输出中的标签表示逐坐标传递；
- 只出现在输入中的标签表示归约；
- 只出现在输出中的标签表示广播；
- 最后乘以节点的 `alpha`。

### 3.3 `DiLinear`

支持 `add`、`sub` 和 `mul`。共享输出指标执行逐元素操作，只出现在两个输入而不出现在输出中的共享指标执行归约，因此矩阵乘、外积、逐元素运算和反向传播中的张量收缩走同一套实现。

### 3.4 `MonoNonlinear` 与 `DiNonlinear`

对每个外层张量坐标，后端按 `x` / `omega` 指标收集符号算子的输入向量和参数向量，调用由 `SymbolicCppBackend` 生成的核，再把核输出放回目标张量。

符号系统可能把多个输出融合在一个 `Expres` 中，也可能把输出拆成多个 cluster。后端同时支持这两种布局。维度为 1 且在 DSL 中用 `.` 省略的函数指标会自动补成坐标 0。

## 4. 图遍历与工作区

后端不直接使用旧 `graph::TopoSortBFS`，而是从网络声明的输出沿入边做依赖 DFS。原因有两个：

- `x * x` 这类重复操作数在旧容器中可能保留两条入边、但合并成一条出邻接记录；
- 高阶微分图可能引用没有收入当前 `graph.content` 的种子或单位张量节点。

以输出为根的依赖遍历能正确包含这些节点，同时自然删除不可达死代码。所有中间张量和常量张量共享一个连续 `std::vector<double>` 工作区。

## 5. 这是参考后端，不是最终性能后端

当前版本首先追求语义清楚和可验证。线性张量节点输出显式嵌套循环；非线性节点目前仍按外层静态坐标生成符号核调用。它有几个明确限制：

- 只生成 CPU `double` / C++11；
- 只支持静态形状；
- 非线性符号算子目前要求一个输入组；
- 没有内存生命周期复用，工作区按所有可达中间结果的总大小分配；
- 非线性节点的大外层张量仍会增加生成源码体积；
- 融合符号核若有多个输出，当前可能在相邻输出坐标重复调用，尚未做调用合并；
- 没有 SIMD、OpenMP、BLAS 或 CUDA lowering。

合理的下一步不是改变前端或微分规则，而是在这个已跑通的语义基线上正式化一个小型张量循环 IR：对现有循环做融合、公共子表达式/核调用合并、工作区活跃区间复用，再选择朴素 C++、OpenMP、BLAS 或 CUDA 输出。

## 6. 错误码

`TensorCppBackend::Status` 包含：

- `Success`：生成成功；
- `InvalidArgument`：空路径、空文件指针等；
- `InvalidFunctionName`：导出函数名不是合法 C++ 标识符；
- `OpenFailure`：无法创建输出文件；
- `InvalidGraph`：形状、指标、依赖或 cluster 布局不一致；
- `UnsupportedNode`：遇到当前参考后端尚不支持的表达方式；
- `SymbolicFailure`：局部符号核 lowering/输出失败；
- `WriteFailure`：文件写入或关闭失败。
