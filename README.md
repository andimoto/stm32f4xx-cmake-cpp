# STM32F4xx CMake Cpp Template 
...for Linux Toolchain (on Linux Mint 19.1)

```
Remarks: This Repository contains experimental source code for STM32F4 devices.
```

## This Project contains following:
```
- example source for stm32f4xx controllers
- source files from stm cube library (v1.8)
- stm32 assambler files for gcc
- stm32 linker script for gcc
```

## Prerequisite
```
- install cmake
- install GNU ARM Toolchain from launchpad 
```

## Build
```
- make a new directory in the projects directory: `mkdir build` and change into it
- configure debug build: `cmake -DCMAKE_BUILD_TYPE=Debug ..`
- then run: `make` (or `make --trace` for verbose output) 
```


