// pattern_call_manager.h
#ifndef PATTERN_CALL_MANAGER_H
#define PATTERN_CALL_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

struct PatternCall {
    int id;
    std::string name;
    std::string patternFile;
    bool called;

    friend std::ostream& operator<<(std::ostream& os, const PatternCall& pc) {
        os << pc.id << "," << pc.name << "," << pc.patternFile << "," << (pc.called ? "true" : "false");
        return os;
    }

    static PatternCall fromString(const std::string& line) {
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

class PatternCallManager {
public:
    void loadFromFile(const std::string& filePath);
    void writeToFile(const std::string& filePath) const;
    void addPatternCall(const PatternCall& pc);

    const PatternCall* getById(int id) const;
    std::vector<PatternCall> getByName(const std::string& name) const;
    std::vector<PatternCall> getByPath(const std::string& path) const;
    std::vector<PatternCall> getSkipped() const;
    std::vector<PatternCall> getCalled() const;

private:
    std::unordered_map<int, PatternCall> byId;
    std::unordered_multimap<std::string, int> nameIndex;
    std::unordered_multimap<std::string, int> pathIndex;
    std::unordered_set<int> skipped;
    std::unordered_set<int> called;
};

#endif
