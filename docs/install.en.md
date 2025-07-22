# Installation Script run.sh User Guide

This document provides instructions on how to use the build script run.sh, enabling efficient compilation, debugging, and cleaning.

## Basic Usage

Navigate to the root directory of the software (for example, Pikachu or PiTorch) in the terminal, and run:

```bash
bash install.sh [options]
```

## Supported Options

- `-g`  
  Enable debug information (equivalent to the `-g` parameter). The compiled executable will contain debug symbols for easier debugging.

- `-o <0|1|2|3>`  
  Set the optimization level. Acceptable values are 0, 1, 2, or 3, corresponding to `-O0` to `-O3`. For example, `-o 2` is equivalent to `-O2`.

- `-c`  
  Clean (delete) old build files before compiling.

- `-C`  
  Only clean (delete build files) and do not compile. Exits immediately after cleaning.

- `-h`  
  Show help information and exit.

## Parameter Combination Instructions

- You can specify both `-g` and `-o` at the same time, for example `-g -o 2`, which compiles with debug info and optimization level 2.
- If you only need to clean files and do not wish to compile, use `-C`.
- If you want to clean before compiling, use `-c`.

## Examples

1. **Normal compilation (no debug, default optimization O0)**  
   ```bash
   bash install.sh
   ```

2. **Compile with debug info**  
   ```bash
   bash install.sh -g
   ```

3. **Compile with specified optimization level (O2)**  
   ```bash
   bash install.sh -o 2
   ```

4. **Compile with both debug and optimization (O3)**  
   ```bash
   bash install.sh -g -o 3
   ```

5. **Clean before compiling**  
   ```bash
   bash install.sh -c
   ```

6. **Clean only, no compilation**  
   ```bash
   bash install.sh -C
   ```

7. **View help**  
   ```bash
   bash install.sh -h
   ```

## Notes

- This script will automatically switch to the `tools` and `extern/tools` directories for build operations.
- If directory switching or `make` fails, clear error messages will be shown.
- The optimization level parameter only accepts 0, 1, 2, or 3; other values will cause an error.
- You can improve the build logic and targets as needed for your project.

---

For further customization or if you encounter any issues, please refer to script comments or contact the maintainer.