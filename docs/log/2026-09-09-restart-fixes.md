# 2026-09-09 重启首轮修复记录

## 范围

这轮工作的目标不是重构架构，而是先清除代码走读中能够确定的构建错误、未定义行为和符号微分语义错误，为后续最小 C++ 后端建立一个可编译、可执行的参考基线。

修复分为两批：第一批处理工程入口和外层张量图中的明显错误；第二批集中处理 `Expres`、`DiFunc` 和 `VISA1` 中端，并新增数值回归。

## 第一批：构建与张量图确定性错误

- 修正 `src/parser/parser.cpp`、`src/parser/GUnit.cpp` 的错误相对 include 路径，使干净检出能够编译。
- 将 `extern/algebra/AlgebraMKL.cpp` 的 MKL 路径改为由 `HYPERALGEBRA_USE_MKL` 显式启用；默认构建不再假定本机安装 MKL。
- 将 `Indice::SetCount` 的返回类型由 `size_t` 改为 `void`，消除声明会返回值但实际没有返回的未定义行为。
- 修正 `DiNonlinear::compute` 的指标归属检查：每个目标指标必须恰好来自 source、function、parameter 三者之一；原条件会拒绝正常情况并放过冲突情况。
- `DiLinear::trivial` 现在复制源节点 descriptor，避免构造出的平凡导数节点缺少张量形状。
- 删除 `DiLinear::backward` 中对未初始化指针 `source` 的解引用。
- 修正 `DiLinear::forward`：加减节点的切向传播保持原 `add/sub` 运算，不再错误地一律生成乘法节点。
- 修正 `DiNonlinear::differential(false)`：参数导数的新指标写入 `indexPara`，不再误写 `indexSrc`；函数现在也实际返回创建的节点。
- 修正 `NetWork::Hv` 搜索反向输出时的循环上界，使用 `BackOut.count()` 而不是无关的拓扑序长度。
- 修正若干格式化参数类型、未初始化局部变量和 `manifold::MonoForward` 的指针声明；尚未实现的 `manifold::DiForward` 改为明确抛出 “not implemented”，避免无返回值地离开函数。

## 第二批：符号微分与 lowering

### 反向符号微分

- 将 `cos(x)` 的反向局部导数从错误的 `-cos(x)` 修为 `-sin(x)`。
- `Expres::backward` 的 label 数组改为按全公式节点数分配。此前按活跃序列长度分配、再用全局 site 索引，在有死节点或图重写空洞时可能越界。
- `ParameterBackward` 重建输出数组后显式初始化为空指针，避免无贡献参数读取未初始化槽位。
- `Funct2BackDiff` 按 `function2` 而不是无关的 `function` 枚举解释二元函数代码。

### `DiFunc`

- 标量参数微分现在传入 `X=false`，不再错误地对普通输入求导。
- 多输出非融合构建使用 `ShrinkOutput(i)` 抽取第 `i` 个输出，不再误调用输入微分。
- `copy` 会按来源大小复制 `original`；同时支持自复制保护，并在复制前清理目标旧状态。
- `build` 在重建前清理旧 cluster/original，实例重复使用时不再泄漏或混入旧表达式。

### 常量与 VISA1

- `FuncConst::nan()` 现在同步清除整数标记；`isZero()`、`isOne()` 不再把内部 NaN 误判为 0 或 1。
- `FuncConst::SetValue(double)` 在做整数转换前先处理 NaN、Inf 和超出 `long long` 范围的有限值，避免浮点到整数的未定义转换。
- `PrintForwardMiniReg` 释放寄存器时改为归还实际加载得到的 `src1/src2`，不再把叶节点未设置的 label（通常为保留寄存器 0）塞入空闲表。

## 新增回归

原先的 Test063 只是生成测试函数样板，现在改为符号中端回归入口，参数文件为 `parameter/symbolic_regression.txt`。当前覆盖：

- NaN 和超大有限常量的分类；
- 含死节点/site 空洞的 `cos(parameter)` 反向梯度；
- `input * parameter` 对单个参数的符号梯度；
- 多输出表达式的拆分；
- `DiFunc` 重复 build，以及复制到已有内容的目标；
- `sin(x) + cos(x)` 的 MiniOp、MiniReg 与解析值三方一致性。

测试参数显式给出三个输出文件名，因为旧测试入口会无条件读取并重写这些配置项；这属于测试壳的历史约束，不是符号中端接口要求。

## 验证结果

在 WSL 环境中完成了干净构建：

```sh
bash ./install.sh -c -o 0
```

随后运行定向回归：

```sh
./test/test.exe ./parameter/symbolic_regression.txt
```

结果为退出码 0，并输出：

```text
Test063: symbolic differentiation regressions passed.
```

## 仍未解决或未充分验证

- `pow` 的指数导数包含 `ln(base)`，负底数配合常整数指数时仍可能因 eager 求值产生 NaN；需要明确数学定义域和 strict/fast 模式。
- `0*x`、`x/x` 等化简按实代数处理，与含 NaN/Inf 的严格 IEEE 语义不完全一致。
- 多维输入与多维参数交错的高阶 `DiFunc` 排列尚缺完整数值矩阵。
- 每个化简 pass 的正例、反例、输出替换和多使用者测试尚未补齐。
- `manifold::DiForward` 仍未实现，静态 C++ 后端也仍是骨架。
- 尚未用十万到百万单项式的 PIP 做内存、编译时间和生成程序规模基准。

这些剩余项不会否定本轮修复，但意味着当前状态只能称为“符号中端有一组可信的最小回归”，还不能称为完整可用的训练框架。
