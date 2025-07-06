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
    for (const auto& pair : m_idIndex) {
        outFile << *pair.second << "\n";
    }
}

void PatternCallManager::addPatternCall(std::shared_ptr<const PatternCall> spPc) {
    m_idIndex.emplace(spPc->getId(), spPc);
    m_nameIndex.emplace(spPc->getName(), spPc);
    m_pathIndex.emplace(spPc->getPath(), spPc);
    m_flagIndex.emplace(spPc->getFlag(), spPc);
}

const std::multimap<std::string, std::shared_ptr<const PatternCall>>& PatternCallManager::getNameMmap() const{
    return m_nameIndex;
}

const std::multimap<std::string, std::shared_ptr<const PatternCall>>& PatternCallManager::getPathMmap() const{
    return m_pathIndex;
}

const std::multimap<int, std::shared_ptr<const PatternCall>>& PatternCallManager::getIdMmap() const{
    return m_idIndex;
}

const std::multimap<bool, std::shared_ptr<const PatternCall>>& PatternCallManager::getFlagMmap() const{
    return m_flagIndex;
}