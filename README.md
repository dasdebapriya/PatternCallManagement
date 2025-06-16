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
├── doc/                                    # doc files
│ ├── PatternCall_Design_Document.pdf       # design doc
│
├── include/                                 # Header files
│ ├── pattern_call.h
│ ├── pattern_call_manager.h
│
├── input/                                   # input files
│ ├── input_patterns.txt                     # input file with pattern call tuples
│
├── output/                                  # output files
│ ├── output_patterns.txt                    # output file with pattern call tuples
│
├── src/                                     # Source files
│ ├── main.cpp                               # main application
│ ├── pattern_call.cpp                       
│ ├── pattern_call_manager.cpp
│
├── test/                                    # Test files
│ ├── test_patterns_in.txt                   # Unit test input file
│ ├── test_patterns_out.txt                  # Unit test output file
│ ├── test_runner.cpp                        # Unit test application
│
├── README.md                                # readme doc
└── Makefile                                 # Build configuration

## Build Instructions
Prerequisites
- C++17-compatible compiler (g++, clang++, etc.)
- Make

## Build
make patternCall_app                          # Build main application
make test_runner                              # Build test excutable
make clean                                    # Cleans the built binaries

## Running the App
./patternCall_app                             # Run the main app 
./test_runner                                 # Run the test suite 