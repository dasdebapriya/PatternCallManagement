// main.cpp
#include "pattern_call_manager.h"
#include <iostream>

template <typename T>
void makeQuery(std::shared_ptr<std::vector<std::shared_ptr<const PatternCall>>> spPcList, T data) {
    if(spPcList->size() > 0) {
        for (auto spPc : *spPcList) {
            if(nullptr != spPc) {
                std::cout << "\nPattern call present with (" << data << ") : "<< " -> " << *spPc << "\n";
            }
            else {
                std::cout << "\nNo pattern call is found with " <<  " : " << data << "\n";
            }
        }
    }
    else {
        std::cout << "\nNo pattern call is found with " << " : " << data << "\n";
    }
}


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
    //auto spSameIdList = manager.getByKey(manager.getIdMmap(), id);
    makeQuery(manager.getByKey(manager.getIdMmap(), id), id);
    

    // Query by name
    std::string name = "SleepSeq";
    makeQuery(manager.getByKey(manager.getNameMmap(), name), name);

    // Query by path
    std::string path = "src/patterns/Power_1.pat";
    makeQuery(manager.getByKey(manager.getPathMmap(), path), path);

    // Query by flag
    bool flag = false;
    makeQuery(manager.getByKey(manager.getFlagMmap(), flag), flag);
    
    // Write all entries to output file
    manager.writeToFile("output/output_patterns1.txt");

    return 0;
}
