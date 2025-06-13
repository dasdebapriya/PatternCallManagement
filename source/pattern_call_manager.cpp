// pattern_call_manager.cpp
#include "pattern_call_manager.h"

void PatternCallManager::loadFromFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    std::string line;
    while (std::getline(inFile, line)) {
        std::shared_ptr<const PatternCall> spPc = PatternCall::fromString(line);
        if(spPc != nullptr) {
            addPatternCall(spPc);
        }
        else {
            continue;
        }
    }
}

void PatternCallManager::writeToFile(const std::string& filePath) const {
    std::ofstream outFile(filePath);
    for (const auto& pair : m_byId) {
        outFile << *pair.second << "\n";
    }
}

void PatternCallManager::addPatternCall(std::shared_ptr<const PatternCall> spPc) {
    m_byId[spPc->getId()] = spPc;
    m_nameIndex.emplace(spPc->getName(), spPc->getId());
    m_pathIndex.emplace(spPc->getPath(), spPc->getId());
    if (spPc->getFlag()) {
        m_called.insert(spPc->getId());
    } else {
        m_skipped.insert(spPc->getId());
    }
}

std::shared_ptr<const PatternCall> PatternCallManager::getById(int id) const { // total time complexity : O(log n)
    auto it = m_byId.find(id); // O(log n)
    if (it != m_byId.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<std::shared_ptr<const PatternCall>> PatternCallManager::getByName(const std::string& name) const { // total time complexity : O(log n) + k * [O(log n) + O(1)]
    
    std::vector<std::shared_ptr<const PatternCall>> results;
    auto range = m_nameIndex.equal_range(name); // complexity O(log n), n is the number of items in m_nameIndex
    
    for (auto it = range.first; it != range.second; ++it) { // k is the number of items in range
        auto iter = m_byId.find(it->second); // complexity O(log n) for look up in m_byId,
        if(iter != m_byId.end()) {
            results.push_back(iter->second); // complexity O(1) for results.push_back
        }
    }
    return results;
}

std::vector<std::shared_ptr<const PatternCall>> PatternCallManager::getByPath(const std::string& path) const { // total time complexity : O(log n) + k * [O(log n) + O(1)]
    
    std::vector<std::shared_ptr<const PatternCall>> results;
    auto range = m_pathIndex.equal_range(path); // complexity O(log n), n is the number of items in m_pathIndex
    
    for (auto it = range.first; it != range.second; ++it) { // k is the number of items in range
        auto iter = m_byId.find(it->second); // complexity O(log n) for look up in m_byId,
        if(iter != m_byId.end()) {
            results.push_back(iter->second); // complexity O(1) for results.push_back
        }
    }
    return results;
}

std::vector<std::shared_ptr<const PatternCall>> PatternCallManager::getSkipped() const { // total time complexity : k * [O(log n) + O(1)]
    std::vector<std::shared_ptr<const PatternCall>> results;
    
    for (int id : m_skipped) { // k is the number of items in the skipped
        auto iter = m_byId.find(id); // complexity O(log n) for look up in m_byId,
        if(iter != m_byId.end()) {    
            results.push_back(iter->second); // complexity O(1) for results.push_back
        }
    }
    return results;
}

std::vector<std::shared_ptr<const PatternCall>> PatternCallManager::getCalled() const { // total time complexity : k * [O(log n) + O(1)]
    std::vector<std::shared_ptr<const PatternCall>> results;
    for (int id : m_called) { // k is the number of items in the m_called
        auto iter = m_byId.find(id); // complexity O(log n) for look up in m_byId,
            if(iter != m_byId.end()) {    
                results.push_back(iter->second); // complexity O(1) for results.push_back
        }
    }
    return results;
}
