// pattern_call.cpp
#include "pattern_call.h"

std::ostream& operator<<(std::ostream& os, const PatternCall& pc) {
        os << pc.m_id << "," << pc.m_name << "," << pc.m_patternFile << "," << (pc.m_called ? "true" : "false");
        return os;
}

std::shared_ptr<const PatternCall> PatternCall::fromString(const std::string& line) {
    std::stringstream ss(line);
    int id = 0;
    std::string name;
    std::string path;
    std::string token;
    bool flag;

    // ID
    if (!std::getline(ss, token, ',')) {
        std::cout << "\nWARNING : Missing ID in the tuple : " << line << "\n";
        return nullptr;
    }
    else {
        try {
            id = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "\nWARNING : Non integer ID "<< token << " in the tuple : " << line << "\n";
            return nullptr;
        }
    }
    
    // Name
    if (!std::getline(ss, name, ',')) {
        std::cout << "\nWARNING : Missing name in the tuple : " << line << "\n";
        return nullptr;
    }
    
    // Pattern file
    if (!std::getline(ss, path, ',')) {
        std::cout << "\nWARNING : Missing path in line : " << line << "\n";
        return nullptr;
    }
    
    // Called flag
    if (!std::getline(ss, token, ',')) {
        std::cout << "\nWARNING : Missing flag in line : " << line << "\n";
        return nullptr;
    }
    else {
        if(token == "true"){
            flag = true;
        }
        else if(token == "false"){
            flag = false;
        }
        else {
            std::cout << "\nWARNING : Non boolean flag "<< token << " in the tuple : " << line << "\n";
            return nullptr;
        }
    }

    return std::make_shared<const PatternCall>(id, name, path, flag);
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