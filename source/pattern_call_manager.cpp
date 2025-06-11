// pattern_call_manager.cpp
#include "pattern_call_manager.h"

void PatternCallManager::loadFromFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    std::string line;
    while (std::getline(inFile, line)) {
        PatternCall pc = PatternCall::fromString(line);
        addPatternCall(pc);
    }
}

void PatternCallManager::writeToFile(const std::string& filePath) const {
    std::ofstream outFile(filePath);
    for (const auto& pair : byId) {
        outFile << pair.second << "\n";
    }
}

void PatternCallManager::addPatternCall(const PatternCall& pc) {
    byId[pc.id] = pc;
    nameIndex.emplace(pc.name, pc.id);
    pathIndex.emplace(pc.patternFile, pc.id);
    if (pc.called) {
        called.insert(pc.id);
    } else {
        skipped.insert(pc.id);
    }
}

const PatternCall* PatternCallManager::getById(int id) const {
    auto it = byId.find(id);
    if (it != byId.end()) return &it->second;
    return nullptr;
}

std::vector<PatternCall> PatternCallManager::getByName(const std::string& name) const {
    std::vector<PatternCall> results;
    auto range = nameIndex.equal_range(name);
    for (auto it = range.first; it != range.second; ++it) {
        results.push_back(byId.at(it->second));
    }
    return results;
}

std::vector<PatternCall> PatternCallManager::getByPath(const std::string& path) const {
    std::vector<PatternCall> results;
    auto range = pathIndex.equal_range(path);
    for (auto it = range.first; it != range.second; ++it) {
        results.push_back(byId.at(it->second));
    }
    return results;
}

std::vector<PatternCall> PatternCallManager::getSkipped() const {
    std::vector<PatternCall> results;
    for (int id : skipped) {
        results.push_back(byId.at(id));
    }
    return results;
}

std::vector<PatternCall> PatternCallManager::getCalled() const {
    std::vector<PatternCall> results;
    for (int id : called) {
        results.push_back(byId.at(id));
    }
    return results;
}
