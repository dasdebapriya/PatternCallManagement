// main.cpp
#include "pattern_call_manager.h"
#include <iostream>

int main() {
    PatternCallManager manager;

    // Load from file
    manager.loadFromFile("input/input_patterns.txt");

    // Add a few dummy entries
    manager.addPatternCall(PatternCall(105, "InitSeq", "src/patterns/Init3.pat", true));
    manager.addPatternCall(PatternCall(202, "WakeupSeq", "src/patterns/Power_1.pat", false));
    manager.addPatternCall(PatternCall(305, "SleepSeq", "src/patterns/Shutdown_2.pat", true));

    // Query by ID
    if (const PatternCall* pc = manager.getById(101)) {
        std::cout << "Found by ID 101: " << *pc << "\n";
    }

    // Query by name
    std::cout << "\nAll entries with name 'InitSeq':\n";
    for (const auto& pc : manager.getByName("InitSeq")) {
        std::cout << pc << "\n";
    }

    // Query by path
    std::cout << "\nAll entries with path 'src/patterns/Init_1.pat':\n";
    for (const auto& pc : manager.getByPath("src/patterns/Init_1.pat")) {
        std::cout << pc << "\n";
    }

    // Get skipped
    std::cout << "\nAll skipped entries (called == false):\n";
    for (const auto& pc : manager.getSkipped()) {
        std::cout << pc << "\n";
    }

    // Get called
    std::cout << "\nAll called entries (called == true):\n";
    for (const auto& pc : manager.getCalled()) {
        std::cout << pc << "\n";
    }

    // Write all entries to output file
    manager.writeToFile("output/output_patterns.txt");

    return 0;
}
