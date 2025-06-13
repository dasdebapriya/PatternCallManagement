# Pattern Call Management

This project implements a Pattern Call Management System in modern C++ using `std::shared_ptr` to ensure efficient and safe memory management with immutable data objects.

## Features

- Parse and load `PatternCall` objects from a delimited text file.
- Store and manage calls with shared ownership (`std::shared_ptr<const PatternCall>`).
- Lookup calls by ID, name, file path, or call status.
- Write managed data to an output file.
- Clear separation of data (`PatternCall`) and management (`PatternCallManager`).

## Project Structure
/patternCallManagement/
├── doc
│ ├── PatternCall_Design_Document.pdf
│ ├── README.md
│
├── include
│ ├── pattern_call.h
│ ├── pattern_call_manager.h
│
├── input
│ ├── input_patterns.txt
│
├── output
│ ├── output_patterns.txt
│
├── src/
│ ├── main.cpp
│ ├── pattern_call.cpp
│ ├── pattern_call_manager.cpp
│
├── test/
│ ├── test_patterns_in.txt
│ ├── test_patterns_out.txt
│ ├── test_runner.cpp
│
├──Makefile
│
└── Design_Document.docx


## Compile
make demo_app test_runner

## Execute solution
./demo_app

## Execute test
./test_runner