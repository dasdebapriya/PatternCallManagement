// main.cpp
#include "pattern_call_manager.h"
#include <iostream>

int main() {
    PatternCallManager manager;

    // Load from file
    manager.loadFromFile("input/input_patterns.txt");

    // Add a few dummy entries
    manager.addPatternCall(std::make_shared<const PatternCall>(105, "InitSeq", "src/patterns/Init3.pat", true));
    manager.addPatternCall(std::make_shared<const PatternCall>(202, "WakeupSeq", "src/patterns/Power_1.pat", false));
    manager.addPatternCall(std::make_shared<const PatternCall>(305, "SleepSeq", "src/patterns/Shutdown_2.pat", true));

    // Query by ID
    int id = 105;
    if (std::shared_ptr<const PatternCall> scPc = manager.getById(id)) {
        if(nullptr != scPc) {
            std::cout << "\nPattern call present with ID : " << id << "\n" << *scPc << "\n";
        }
    }
    else {
        std::cout << "\nNo pattern call is found with ID : " << id << "\n";
    }

    // Query by name
    std::string name = "SleepSeq";
    auto sameNameList = manager.getByName(name);
    if(sameNameList.size() > 0) {
        std::cout << "\nAll entries with name : " << name << "\n";
        for (auto scPc : sameNameList) {
            if(nullptr != scPc) {
                std::cout << *scPc << "\n";
            }
            else {
                std::cout << "\nNull pointer encountered for pattern call name : " << name << "\n";
            }
        }
    }
    else {
        std::cout << "\nNo pattern call is found with name : " << name << "\n";
    }
    
    // Query by path
    std::string path = "src/patterns/Power_1.pat";
    auto samePathList = manager.getByPath(path);
    if(sameNameList.size() > 0) {
        std::cout << "\nAll entries with path : "<< path << "\n";
        for (auto scPc : manager.getByPath(path)) {
            if(nullptr != scPc) {
                std::cout << *scPc << "\n";
            }
            else {
                std::cout << "\nNull pointer encountered for pattern call path : " << path << "\n";
            }
        }
    }
    else {
        std::cout << "\nNo pattern call is found with path : " << path << "\n";
    }

    // Get skipped
    auto skippedList = manager.getSkipped();
    if(skippedList.size() > 0) {
        std::cout << "\nAll skipped entries (called == false):\n";
        for (auto scPc : skippedList) {
            if(nullptr != scPc) {
                std::cout << *scPc << "\n";
            }
            else {
                std::cout << "\nNull pointer encountered for skipped pattern call" << "\n";
            }
        }
    }
    else {
        std::cout << "\nNo pattern call is skipped \n";
    }
    
    // Get called
    auto calledList = manager.getCalled();
    if(calledList.size() > 0) {
        std::cout << "\nAll called entries (called == true):\n";
        for (auto scPc : manager.getCalled()) {
            if(nullptr != scPc) {
                std::cout << *scPc << "\n";
            }
            else {
                std::cout << "\nNull pointer encountered for called pattern call " << "\n";
            }
        }
    }
    else {
        std::cout << "\nAll pattern calls are skipped \n";
    }
    // Write all entries to output file
    manager.writeToFile("output/output_patterns_1.txt");

    return 0;
}
