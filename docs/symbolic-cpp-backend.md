# 符号 C++ 后端

## 1. 当前实现是什么

`SymbolicCppBackend` 将当前主符号表达式 `Expres` lowering 为 `VISA1`，再输出一个自包含的 C++11 函数。生成源码只依赖标准库 `<cmath>` 和 `<limits>`，编译、链接和运行时均不依赖 Pikachu2。

这完成的是第一层后端：**一个符号超级节点可以兑现为静态 C++ 标量核**。它还不是整个 `NetWork` 张量图的后端；张量循环、缩并、节点间缓冲区和全图调度仍未生成。

```text
Expres 符号 DAG
       │
       ├── MiniOperations：少重复加载/操作
       └── MiniRegisters：少同时存活寄存器
       │
       ▼
     VISA1
       │
       ▼
SymbolicCppBackend
       │
       ▼
独立的 .cpp 函数
```

## 2. 接口

声明位于 `src/header/Symbolic.h`：

```cpp
Pikachu::SymbolicCppBackend backend;
int status = backend.build(
    expression,
    "./output/kernel.cpp",
    "pip_kernel",
    Pikachu::SymbolicCppBackend::MiniRegisters);
```

也可以先自行构造 `VISA1`，再直接输出：

```cpp
Pikachu::VISA1 visa;
Pikachu::vector<size_t> freeRegisters;
expression.PrintForwardMiniOp(visa, freeRegisters);

int status = backend.build(visa, "./output/kernel.cpp", "pip_kernel");
```

若调用方已经管理 `FILE*`，可以使用 `print(visa, file, functionName)`。`build` 会负责打开并关闭目标文件。

### 返回状态

| 状态 | 含义 |
| --- | --- |
| `Success` | 生成成功 |
| `InvalidArgument` | 空路径、空指针参数或非法 lowering 选项 |
| `InvalidFunctionName` | 函数名为空、不是合法 C++ 标识符，或与 C++11 关键字/`main` 冲突 |
| `OpenFailure` | 无法创建目标文件 |
| `InvalidProgram` | VISA1 指令类型、操作码、常量索引或寄存器编号非法 |
| `WriteFailure` | 写入或关闭文件失败 |

## 3. 生成函数 ABI

生成函数采用稳定的 C ABI 名称和以下签名：

```cpp
extern "C" void pip_kernel(
    const double* const* input,
    const double* parameter,
    double* output);
```

- `input[group][offset]` 对应 `_LeafX_` 的 `src1/src2`；因此输入是“输入组指针数组”，而不是单一扁平数组。
- `parameter[offset]` 对应 `_LeafPara_::src2`，参数按一维数组传入。
- `output[index]` 对应 `Expres` 的输出顺序。
- 生成函数不分配堆内存、不做边界检查，也不拥有任何调用方内存。
- 调用方必须为实际被引用的输入组、参数和输出提供有效空间。

目前的 ABI 刻意与 `VISA1::compute` 保持一致，方便逐指令对照。未来完整张量后端可以在外层生成扁平缓冲区和循环，并在调用符号核时组装这些指针。

## 4. 指令映射

| VISA1 | 生成的 C++ |
| --- | --- |
| `_ld_` 输入 | `reg[d] = input[group][offset]` |
| `_ld_` 参数 | `reg[d] = parameter[offset]` |
| `_ld_` 常量 | 直接写入数值字面量或 `numeric_limits` |
| `_op_` | `+ - * /` |
| `_func_` | `std::sin/cos/exp/log/sqrt` 或一元负号 |
| `_func2_` | `std::pow` |
| `_st_` | `output[index] = reg[source]` |

虚拟寄存器变成函数内的固定大小 `double reg[N]`。寄存器 0 保留不用；生成前会验证所有真正的运算源和目标均落在 `[1, RegCount]`。NaN 和正负无穷分别输出为 `std::numeric_limits<double>::quiet_NaN()` 和 `infinity()`，普通有限常量用 17 位有效数字输出。

## 5. 两种 lowering 的选择

`MiniOperations` 让每个叶节点和内部节点尽量只计算一次，适合共享子表达式较多、重复加载代价明显的表达式。

`MiniRegisters` 在使用点重新加载叶节点，并尽快回收寄存器，通常产生更多 load，但局部寄存器数组较小。对很大的 PIP，较小的活跃值集合可能减轻编译器和机器寄存器压力；是否真正更快必须以生成源码规模、宿主编译时间和运行基准决定。

两者具有同一数值语义。本轮 Test064 会为同一表达式生成两份源码，并检查两份编译后函数、VISA1 解释器与解析结果一致。

## 6. 验证方法

先构建项目并生成两份测试源码：

```bash
bash ./install.sh -c -o 0
./test/test.exe ./parameter/symbolic_backend.txt
```

再脱离 Pikachu2 库，单独编译生成源码和测试调用器：

```bash
g++ -std=c++11 -O2 \
  output/symbolic_generated.cpp \
  output/symbolic_generated_miniop.cpp \
  test/symbolic_backend_driver.cpp \
  -o output/symbolic_backend_test

./output/symbolic_backend_test
```

成功时输出：

```text
generated C++ backend matches the analytic reference.
```

测试表达式覆盖两个输入组、一个参数、四个输出、共享叶节点、四则运算、全部现有一元函数、`pow`、NaN 和 Inf 常量。测试二进制没有链接 `libHyperPes.a`，因而能够证明生成文件是独立代码。

## 7. 这一步实现了什么“融合”

一个 `Expres` 无论内部包含多少标量节点，最终都被输出为一个普通 C++ 函数。外层只需要看到函数输入和输出，内部临时值保留在局部寄存器数组中，不必物化为张量图上的独立缓冲区。这把原先“表示上保留的融合边界”第一次兑现成了可编译代码。

不过，它还没有生成外层批次/张量循环，也没有把多个符号核与线性缩并统一调度。因此当前是 **symbolic-kernel fusion**，不是完整的 graph/kernel fusion。

## 8. 已知限制与下一步

- 仅支持当前 VISA1 原语集合和 `double`。
- 没有自动生成头文件、形状元数据或输入长度检查。
- 寄存器数组位于栈上；极大的 `RegCount` 需要改为调用方 workspace、堆缓冲或分块代码生成。
- 一条 VISA1 指令对应一条 C++ 语句，没有循环恢复、向量化、FMA、并行或代价模型。
- 常量池仍为线性去重，大型表达式的宿主编译时间和源码体积尚无基准。
- 数学定义域与现有解释器一致；`pow`、`log`、除零以及 fast-math/严格 IEEE 的取舍尚未规格化。
- 尚未处理外层 `NetWork` 的拓扑调度、张量指标循环、缩并、广播、临时张量规划和多个节点间的数据布局。

合理的下一步不是立刻增加 CUDA，而是让全图 CPU 后端为每个 `MonoNonlinear/DiNonlinear` 调用这里生成的符号核，同时用最朴素循环实现 `MonoLinear/DiLinear`。先跑通一个小型能量—力—参数梯度网络，再决定是否做循环融合和内存规划。
