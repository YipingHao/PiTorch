# 势能面拟合与PINN神经网络专用框架 by CPP

## 介绍
还在开发中的软件。
为计算化学领域的某些任务开发的神经网络训练和推理框架，主要服务于势能面拟合以及PINN任务。

在势能面拟合以及PINN中，往往需要对神经网络求取某些高阶导数。有时候需要对一些非常小众的算子比如大型的置换不变多项式做微分。此外高阶优化器比如LM的收敛结果往往往往显著战胜ADAM，SGD等一阶优化器，没人知道为什么。这些功能不是当今神经网络框架用户的核心需求，所以常常缺乏高性能实现。

### 这个软件的特色
#### 1 高性能的神经网络输出对输入的高阶导数求取。
#### 2 高阶优化器支持
#### 3 采用符号位分与反向前向传播微分相混合的微分技术。

在不增加代码的的同时可以高效的支持科学计算任务中的用户自定义算子。

### 不足
#### 1对混合精度几乎无支持。最多支持FP32FP64
#### 2入门比pytorch更复杂
#### 3不支持有一些机器学习中烂大街，但是计算化学中不常见的结构比如卷积。。。



#### 软件架构
软件还在开发中。

对此感兴趣的可以直接联系作者hyper@dicp.ac.cn



## 安装方法
```bash
git clone https://github.com/YipingHao/PiTorch.git
cd PiTorch
bash install.sh
```
### 脚本使用指南

本文档介绍了如何使用本构建脚本，便于高效地进行编译、调试和清理工作。

#### 基本用法

在终端进入脚本所在目录，运行：

```bash
./your_script.sh [选项]
```

#### 支持的选项

- `-g`  
  启用调试信息（等价于 `-g` 参数）。编译出的可执行文件将包含调试符号，便于调试。

- `-o <0|1|2|3>`  
  设定优化级别。可选参数为 0、1、2 或 3，对应 `-O0` 到 `-O3` 优化等级。例如 `-o 2` 等价于 `-O2`。

- `-c`  
  在构建前先清理（clean）一次，删除旧的编译文件，再进行编译。

- `-C`  
  仅清理（clean），不做编译。执行后直接退出。

- `-h`  
  显示帮助信息（usage），并退出。

#### 参数组合说明

- 可同时指定 `-g` 和 `-o`，例如 `-g -o 2`，则会以带调试信息和二级优化的方式编译。
- 若仅需清理文件而不编译，使用 `-C`。
- 若需在编译前清理一次，使用 `-c`。

#### 示例

1. **普通编译（无调试、默认优化等级 O0）**  
   ```bash
   ./your_script.sh
   ```

2. **带调试信息编译**  
   ```bash
   ./your_script.sh -g
   ```

3. **指定优化等级编译（O2）**  
   ```bash
   ./your_script.sh -o 2
   ```

4. **同时调试与优化（O3）**  
   ```bash
   ./your_script.sh -g -o 3
   ```

5. **编译前先清理**  
   ```bash
   ./your_script.sh -c
   ```

6. **只清理，不编译**  
   ```bash
   ./your_script.sh -C
   ```

7. **查看帮助**  
   ```bash
   ./your_script.sh -h
   ```

#### 注意事项

- 本脚本会自动切换到 `tools` 和 `extern/tools` 目录进行编译操作。
- 如果目录切换失败或 make 失败，会有明确错误提示。
- 优化级别参数只接受 0、1、2、3，其他数值会报错。
- 可根据实际项目需要完善构建逻辑与目标。

---

如需进一步自定义脚本行为，请参考脚本内注释或联系维护者。

## 使用说明

使用run.sh脚本即可运行。
```bash
bash run.sh
```

### 使用指南：运行和调试脚本run.sh

本脚本用于运行 `./test/test.exe` 程序，支持参数输入、输出路径指定，以及 GDB 调试。

---

####  基本用法

```bash
./your_script.sh [选项]
```

####  支持的选项

- `-g [gdb参数...]`  
  使用 GDB 调试程序 `test.exe`，可以跟随 GDB 的参数（可选）。示例见下方。

- `-i <输入文件>`  
  指定输入文件路径。默认值为 `parameter/parameter.txt`。  
  例：`-i data/input.txt`

- `-I <文件名>`  
  指定输入文件名（会自动加上 `./parameter/` 前缀）。  
  例：`-I myparam.txt` 会使用 `./parameter/myparam.txt` 作为输入。

- `-o <输出目录>`  
  指定输出目录。默认值为 `output/`。如果目录不存在，脚本会尝试自动创建。

- `-h`  
  显示帮助信息并退出。

---

####  使用举例

1. **正常运行，使用默认参数**
   ```bash
   ./your_script.sh
   ```
   等价于：
   ```bash
   ./test/test.exe parameter/parameter.txt output/
   ```

2. **指定输入文件和输出目录**
   ```bash
   ./your_script.sh -i myinput.txt -o myresult/
   ```
   运行：
   ```bash
   ./test/test.exe myinput.txt myresult/
   ```

3. **指定输入文件名（自动加前缀）**
   ```bash
   ./your_script.sh -I test1.txt
   ```
   运行：
   ```bash
   ./test/test.exe ./parameter/test1.txt output/
   ```

4. **GDB 调试运行**
   ```bash
   ./your_script.sh -g
   ```
   执行：
   ```bash
   gdb --args ./test/test.exe parameter/parameter.txt output/
   ```

5. **GDB 调试并自定义 GDB 参数**
   ```bash
   ./your_script.sh -g -q
   ```
   执行：
   ```bash
   gdb -q --args ./test/test.exe parameter/parameter.txt output/
   ```

---

####  注意事项

- 输出目录如不存在，脚本会自动尝试创建，若失败（如无权限）会报错退出。
- `-g` 后的参数会原样传递给 GDB。
- 输入与输出参数均为必需项，缺失时会报错提醒。
- `-h` 可随时查看帮助信息。

---

如需进一步自定义或遇到问题，请参考脚本注释或与项目维护者联系。

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
