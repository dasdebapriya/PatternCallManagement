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
    for (const auto& pair : m_byId) {
        outFile << pair.second << "\n";
    }
}

void PatternCallManager::addPatternCall(const PatternCall& pc) {
    m_byId[pc.getId()] = pc;
    m_nameIndex.emplace(pc.getName(), pc.getId());
    m_pathIndex.emplace(pc.getPath(), pc.getId());
    if (pc.getFlag()) {
        m_called.insert(pc.getId());
    } else {
        m_skipped.insert(pc.getId());
    }
}

const PatternCall* PatternCallManager::getById(int id) const { // total time complexity : O(log n)
    auto it = m_byId.find(id); // O(log n)
    if (it != m_byId.end()) return &it->second;
    return nullptr;
}

std::vector<PatternCall> PatternCallManager::getByName(const std::string& name) const { // total time complexity : O(log n) + k * [O(log n) + O(1)]
    std::vector<PatternCall> results;
    auto range = m_nameIndex.equal_range(name); // complexity O(log n), n is the number of items in m_nameIndex
    for (auto it = range.first; it != range.second; ++it) { // k is the number of items in range
        results.push_back(m_byId.at(it->second)); // complexity O(log n) for look up in m_byId, O(1) for results.push_back
    }
    return results;
}

std::vector<PatternCall> PatternCallManager::getByPath(const std::string& path) const { // total time complexity : O(log n) + k * [O(log n) + O(1)]
    std::vector<PatternCall> results;

    auto range = m_pathIndex.equal_range(path); // complexity O(log n), n is the number of items in m_pathIndex
    for (auto it = range.first; it != range.second; ++it) { // k is the number of items in range
        results.push_back(m_byId.at(it->second)); // complexity O(log n) for look up in m_byId, O(1) for results.push_back
    }
    return results;
}

std::vector<PatternCall> PatternCallManager::getSkipped() const { // total time complexity : k * [O(log n) + O(1)]
    std::vector<PatternCall> results;
    for (int id : m_skipped) { // k is the number of items in the skipped
        results.push_back(m_byId.at(id)); // complexity O(log n) for look up in m_byId, O(1) for results.push_back
    }
    return results;
}

std::vector<PatternCall> PatternCallManager::getCalled() const { // total time complexity : k * [O(log n) + O(1)]
    std::vector<PatternCall> results;
    for (int id : m_called) { // k is the number of items in the m_called
        results.push_back(m_byId.at(id)); // O(log n) for look up in m_byId, O(1) for results.push_back
    }
    return results;
}
