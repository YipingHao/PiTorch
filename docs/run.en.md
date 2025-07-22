# User Guide for Running and Debugging Script run.sh

This script is used to run the `./test/test.exe` program. It supports specifying input files, output directories, and GDB debugging.

---

## Basic Usage

```bash
bash run.sh [options]
```

## Supported Options

- `-g [gdb options...]`  
  Use GDB to debug `test.exe`. You can pass additional GDB options (optional), see examples below.

- `-i <input file>`  
  Specify the input file path. The default is `parameter/parameter.txt`.  
  Example: `-i data/input.txt`

- `-I <filename>`  
  Specify the input filename (will automatically add the `./parameter/` prefix).  
  Example: `-I myparam.txt` will use `./parameter/myparam.txt` as input.

- `-o <output directory>`  
  Specify the output directory. The default is `output/`. If the directory does not exist, the script will try to create it automatically.

- `-h`  
  Show help information and exit.

---

## Usage Examples

1. **Run normally with default parameters**
   ```bash
   bash run.sh
   ```
   Equivalent to:
   ```bash
   ./test/test.exe parameter/parameter.txt output/
   ```

2. **Specify input file and output directory**
   ```bash
   bash run.sh -i myinput.txt -o myresult/
   ```
   Runs:
   ```bash
   ./test/test.exe myinput.txt myresult/
   ```

3. **Specify input filename (auto add prefix)**
   ```bash
   bash run.sh -I test1.txt
   ```
   Runs:
   ```bash
   ./test/test.exe ./parameter/test1.txt output/
   ```

4. **Run with GDB debugging**
   ```bash
   bash run.sh -g
   ```
   Equivalent to:
   ```bash
   gdb --args ./test/test.exe parameter/parameter.txt output/
   ```

5. **GDB debugging with custom GDB options**
   ```bash
   bash run.sh -g -q
   ```
   Executes:
   ```bash
   gdb -q --args ./test/test.exe parameter/parameter.txt output/
   ```

---

## Notes

- If the output directory does not exist, the script will attempt to create it automatically. If it fails (e.g., due to lack of permissions), it will report an error and exit.
- Any arguments after `-g` will be passed directly to GDB.
- Both input and output parameters are required. If missing, the script will report an error.
- `-h` can be used at any time to display help information.

---

For further customization or if you encounter any issues, please refer to the script comments or contact the project maintainer.