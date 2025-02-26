# cpp memory management examples

A collection of C++ examples demonstrating modern memory management techniques using smart pointers, move semantics, and RAII principles.

## Overview

This repository contains various examples that illustrate how to safely manage dynamic memory in C++ using modern constructs such as std::unique_ptr. Whether you’re looking to understand smart pointer basics, implement custom deleters, or build data structures (like linked lists) that avoid memory leaks, these examples will help you level up your C++ skills.

Still using raw pointers? That’s like driving a car without brakes—time to upgrade!

## Contents

- Smart Pointer Basics:
Learn how to create and work with std::unique_ptr to manage resource ownership.

- Move Semantics:
Explore practical implementations of move constructors and move assignment operators that efficiently transfer resource ownership.

- Custom Deleters:
See how custom deleters (including lambdas) can be used for resource cleanup, such as closing file handles automatically.

- Linked List Demo:
A safe implementation of a linked list using smart pointers that prevents deep recursive destruction.

- Exception Safety:
Understand how resource cleanup is maintained even when exceptions occur.

- Array Management:
Manage dynamically allocated arrays using smart pointers with automatic cleanup.


## Requirements

- A C++14 (or later) compliant compiler (e.g., GCC, Clang, MSVC)

- (Optional) CMake for building the project

- Basic familiarity with C++ and its modern memory management techniques


## How to Build

### Using g++:

```bash
g++ -std=c++14 -o memory_management_example main.cpp
./memory_management_example
```

### Using CMake:

```bash
mkdir build && cd build
cmake ..
make
./cpp_memory_management_examples
```

## Contributing

Contributions are welcome! If you have additional examples or improvements, feel free to fork the repository and submit a pull request. Remember: this is a learning journey—share your insights, help others, and always credit your sources.

## License

This project is licensed under the MIT License. See the [LICENSE](/LICENSE) file for details.

## Final Thoughts

Memory management in C++ can be a daunting topic, but with smart pointers and modern C++ techniques, you can write code that is both efficient and safe. Whether you’re a seasoned developer or just starting out, these examples are designed to help you understand and implement best practices in resource management. Happy coding—and may your memory always be leak-free!