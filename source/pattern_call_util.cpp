// pattern_call.cpp
#include "pattern_call.h"
#include <sstream>
#include <stdexcept>

std::ostream& operator<<(std::ostream& os, const PatternCall& pc) {
    os << pc.id << "," << pc.name << "," << pc.patternFile << "," << (pc.called ? "true" : "false");
    return os;
}

PatternCall PatternCall::fromString(const std::string& line) {
    std::istringstream ss(line);
    std::string token;
    PatternCall pc;

    // ID
    if (!std::getline(ss, token, ',')) throw std::runtime_error("Missing ID");
    pc.id = std::stoi(token);

    // Name
    if (!std::getline(ss, token, ',')) throw std::runtime_error("Missing name");
    pc.name = token;

    // Pattern file
    if (!std::getline(ss, token, ',')) throw std::runtime_error("Missing pattern file");
    pc.patternFile = token;

    // Called flag
    if (!std::getline(ss, token, ',')) throw std::runtime_error("Missing called flag");
    pc.called = (token == "true");

    return pc;
}
