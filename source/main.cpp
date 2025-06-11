// main.cpp
#include "pattern_call_manager.h"
#include <iostream>

int main() {
    PatternCallManager manager;

    // Step 1: Load from file
    manager.loadFromFile("input_patterns.txt");

    // Step 2: Add a few dummy entries
    manager.addPatternCall({101, "InitSeq", "src/patterns/Init.pat", true});
    manager.addPatternCall({102, "Shutdown", "src/patterns/Power.pat", false});
    manager.addPatternCall({103, "InitSeq", "src/patterns/Init.pat", true});

    // Step 3: Query by ID
    if (const PatternCall* pc = manager.getById(101)) {
        std::cout << "Found by ID 101: " << *pc << "\n";
    }

    // Step 4: Query by name
    std::cout << "\nAll entries with name 'InitSeq':\n";
    for (const auto& pc : manager.getByName("InitSeq")) {
        std::cout << pc << "\n";
    }

    // Step 5: Query by path
    std::cout << "\nAll entries with path 'src/patterns/Init.pat':\n";
    for (const auto& pc : manager.getByPath("src/patterns/Init.pat")) {
        std::cout << pc << "\n";
    }

    // Step 6: Get skipped
    std::cout << "\nAll skipped entries (called == false):\n";
    for (const auto& pc : manager.getSkipped()) {
        std::cout << pc << "\n";
    }

    // Step 7: Get called
    std::cout << "\nAll called entries (called == true):\n";
    for (const auto& pc : manager.getCalled()) {
        std::cout << pc << "\n";
    }

    // Step 8: Write all entries to output file
    manager.writeToFile("output_patterns.txt");

    return 0;
}
