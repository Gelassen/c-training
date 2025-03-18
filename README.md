# C++ Mastery Roadmap

This repository contains a set of tasks designed to help experienced software engineers master C++ in a hands-on way. The focus is on real-world, console-based tasks to cover core C++ concepts, tools, and best practices. Each task is designed to reinforce specific aspects of C++ that are essential for becoming proficient in the language.

## Table of Contents

1. [C++ Templates](#5-c-templates)
2. [C++ Standard Library (STL)](#6-c-standard-library-stl)
3. [C++ Concurrency and Multithreading](#7-c-concurrency-and-multithreading)
4. [Memory Management and Smart Pointers](#8-memory-management-and-smart-pointers)
5. [C++11, C++14, and C++17 Features](#9-c-11-c-14-and-c-17-features)
6. [C++ Design Patterns](#10-c-design-patterns)
7. [C++ Best Practices](#11-c-best-practices)

## 5. C++ Templates
### Task: Create a Generic Data Structure
- **Goal**: Master templates by building generic tools that work with different data types.
- **Instructions**:
  - Implement a generic stack (or queue) class using templates.
  - Add operations like push, pop, size, isEmpty, and peek.
  - Implement template specialization to handle specific types differently (e.g., `std::string` vs `int`).

---

## 6. C++ Standard Library (STL)
### Task: Implement a Word Frequency Counter
- **Goal**: Become comfortable with STL containers and algorithms.
- **Instructions**:
  - Use `std::map` or `std::unordered_map` to create a word frequency counter.
  - Read a text file and count the frequency of each word.
  - Sort the results alphabetically using `std::sort` with iterators.
  - Handle edge cases like punctuation and capitalization.
  - Bonus: Implement sorting by frequency.

---

## 7. C++ Concurrency and Multithreading
### Task: Parallelize File Downloading
- **Goal**: Learn how to use C++ for concurrent programming.
- **Instructions**:
  - Download multiple files concurrently using `std::thread`.
  - Implement synchronization using `std::mutex` to ensure thread-safe updates.
  - Handle errors such as failed downloads and ensure proper resource management.

---

## 8. Memory Management and Smart Pointers
### Task: Build a Memory Pool for Object Management
- **Goal**: Gain proficiency with manual memory management and smart pointers.
- **Instructions**:
  - Create a `MemoryPool` class that allocates and deallocates memory for objects.
  - Use `new`/`delete` for raw memory management.
  - Transition to `std::unique_ptr` for automatic memory management.
  - Test with dynamically allocated objects (e.g., `Car`, `Employee`).

---

## 9. C++11, C++14, and C++17 Features
### Task: Use Lambda Expressions for Filtering and Transformation
- **Goal**: Learn modern C++ features like lambda expressions.
- **Instructions**:
  - Create a list of objects (e.g., `Person` with `name` and `age`).
  - Use a lambda expression to filter people based on age.
  - Use `std::transform` to apply a transformation (e.g., uppercase the names).
  - Experiment with lambda capturing (value, reference).

Bonus: Learn and use `std::optional` for handling potential missing values.

---

## 10. C++ Design Patterns
### Task: Build a Simple Factory for Creating Objects
- **Goal**: Learn and apply the Factory design pattern.
- **Instructions**:
  - Create a base class `Vehicle` with a `start()` method.
  - Implement `Car`, `Truck`, and `Bicycle` classes, overriding `start()`.
  - Implement a factory function that creates the appropriate `Vehicle` based on input.

---

## 11. C++ Best Practices
### Task: Build a Command-Line Calculator with Input Validation
- **Goal**: Write clean, maintainable, and efficient C++ code.
- **Instructions**:
  - Implement basic arithmetic operations (addition, subtraction, etc.).
  - Ensure proper input validation (non-numeric inputs, division by zero).
  - Use exception handling to manage errors.
  - Cleanly separate logic using functions or classes.

---

## Getting Started

1. **Install C++ Development Tools**:
   - On Ubuntu, you can install the necessary tools by running:
     ```bash
     sudo apt-get update
     sudo apt-get install build-essential gdb
     ```
   
2. **Using VS Code**:
   - VS Code is a suitable IDE for C++ development with excellent support for syntax highlighting, debugging, and extensions.
   - Recommended extensions:
     - **C/C++** by Microsoft
     - **CMake Tools** for project management
     - **Clangd** for IntelliSense
  
3. **Build and Run**:
   - Create a `Makefile` or use CMake to organize and build your projects.
   - To compile C++ code, use:
     ```bash
     g++ -o output_file your_code.cpp
     ./output_file
     ```

---

## Conclusion

These tasks will guide you through the essential C++ concepts and their application in real-world scenarios. By completing them, you’ll not only understand theoretical concepts but also gain valuable practical experience that you can use in your software engineering career.

Happy coding!

(c) ChatGpt
