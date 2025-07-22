# 运行和调试脚本run.sh的使用指南

本脚本用于运行 `./test/test.exe` 程序，支持参数输入、输出路径指定，以及 GDB 调试。

---

##  基本用法

```bash
bash run.sh [选项]
```

##  支持的选项

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

##  使用举例

1. **正常运行，使用默认参数**
   ```bash
   bash run.sh
   ```
   等价于：
   ```bash
   ./test/test.exe parameter/parameter.txt output/
   ```

2. **指定输入文件和输出目录**
   ```bash
   bash run.sh -i myinput.txt -o myresult/
   ```
   运行：
   ```bash
   ./test/test.exe myinput.txt myresult/
   ```

3. **指定输入文件名（自动加前缀）**
   ```bash
   bash run.sh -I test1.txt
   ```
   运行：
   ```bash
   ./test/test.exe ./parameter/test1.txt output/
   ```

4. **GDB 调试运行**
   ```bash
   bash run.sh -g
   ```
   它等价于:
   ```bash
   gdb --args ./test/test.exe parameter/parameter.txt output/
   ```

5. **GDB 调试并自定义 GDB 参数**
   ```bash
   bash run.sh -g -q
   ```
   执行：
   ```bash
   gdb -q --args ./test/test.exe parameter/parameter.txt output/
   ```

---

##  注意事项

- 输出目录如不存在，脚本会自动尝试创建，若失败（如无权限）会报错退出。
- `-g` 后的参数会原样传递给 GDB。
- 输入与输出参数均为必需项，缺失时会报错提醒。
- `-h` 可随时查看帮助信息。

---

如需进一步自定义或遇到问题，请参考脚本注释或与项目维护者联系。