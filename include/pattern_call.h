// pattern_call_manager.h
#ifndef PATTERN_CALL_H
#define PATTERN_CALL_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


class PatternCall {
    int id;
    std::string name;
    std::string patternFile;
    bool called;

    std::ostream& operator<<(std::ostream& os, const PatternCall& pc) {
        os << pc.id << "," << pc.name << "," << pc.patternFile << "," << (pc.called ? "true" : "false");
        return os;
    }

    PatternCall fromString(const std::string& line) {
        std::stringstream ss(line);
        std::string item;
        PatternCall pc;
        std::getline(ss, item, ','); pc.id = std::stoi(item);
        std::getline(ss, pc.name, ',');
        std::getline(ss, pc.patternFile, ',');
        std::getline(ss, item, ','); pc.called = (item == "true");
        return pc;
    }
};

#endif