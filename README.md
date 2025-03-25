# LongNumber: Arbitrary Precision Arithmetic Library

## Description
LongNumber is a library for performing arbitrary precision arithmetic in a binary fixed-point format. It allows precise arithmetic operations and supports user-defined computation precision.

## Features
- `long_number` class for handling large numbers.
- Supported operations:
  - Arithmetic: `+`, `-`, `*`, `/`.
  - Comparison: `==`, `!=`, `<`, `>`.
- Creation of a long number from a floating-point literal: `operator""_longnum(long double number);`
- Flexible computation precision setting (number of binary digits after the decimal point).
- Comprehensive test coverage for all functions.
- A program for calculating π (Pi) with a specified precision.

## Project Structure
```
📁 LongNumber/
├── pi_calc.cpp        # Pi computation program implementation
├── tests.cpp          # Library testing
├── long_number.hpp    # Declaration of LongNum class
├── long_number.cpp    # Implementation of LongNum class
├── Makefile           # Make build script
├── CMakeLists.txt     # CMake build configuration
├── README.md          # Project description
```

## Installation & Build
The project is built using `make`:

- **Build the library and all programs:**
  ```sh
  make
  ```

- **Run tests:**
  ```sh
  make test
  ```
  Each test outputs a verdict of `OK` or `FAIL`.

- **Compute π with 100 decimal places:**
  ```sh
  make pi
  ```

- **Compute π with a custom precision (e.g., 50 decimal places):**
  ```sh
  ./pi_calc 50
  ```

Alternatively, you can build the project using CMake:

```sh
mkdir build && cd build
cmake ..
make
```

## Requirements
- C++ compiler (GCC or Clang with C++17 support or higher)
- `make` or `cmake`
