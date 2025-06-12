// pattern_call.cpp
#include "pattern_call.h"

std::ostream& operator<<(std::ostream& os, const PatternCall& pc) {
        os << pc.m_id << "," << pc.m_name << "," << pc.m_patternFile << "," << (pc.m_called ? "true" : "false");
        return os;
}

PatternCall PatternCall::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    PatternCall pc;

    // ID
    if (!std::getline(ss, token, ',')) {   
        throw std::runtime_error("Missing ID");
    }
    else {
        pc.m_id = std::stoi(token);
    }
    
    // Name
    if (!std::getline(ss, token, ',')) {
        throw std::runtime_error("Missing name");
    }
    else {
        pc.m_name = token;
    }
    
    // Pattern file
    if (!std::getline(ss, token, ',')) {
        throw std::runtime_error("Missing pattern file");
    }
    else {
        pc.m_patternFile = token;
    }
    
    // Called flag
    if (!std::getline(ss, token, ',')) {
        throw std::runtime_error("Missing called flag");
    }
    else {
        pc.m_called = (token == "true");
    }
    return pc;
}

int PatternCall::getId() const{
    return m_id;
}

std::string PatternCall::getName() const {
    return m_name;
}

 std::string PatternCall::getPath() const{
    return m_patternFile;
}

bool PatternCall::getFlag() const{
    return m_called;
} 