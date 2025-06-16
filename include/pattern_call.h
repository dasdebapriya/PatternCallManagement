// pattern_call.h
#ifndef PATTERN_CALL_H
#define PATTERN_CALL_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

/**
 * @brief Represents a pattern call with ID, name, filepath, and call status.
 */
class PatternCall {
private : 
    int m_id;
    std::string m_name;
    std::string m_patternFile;
    bool m_called;

public : 
/**
    /**
     * @brief Constructs a PatternCall object.
     * 
     * @param id Unique identifier.
     * @param name Name of the pattern.
     * @param patternFile Path to the pattern file.
     * @param called Whether the pattern was called.
     */
    PatternCall(int id, std::string name, std::string patternFile, bool called)
    : m_id(id), m_name(name), m_patternFile(patternFile), m_called(called){}

    /// @brief Get the ID of the pattern.
    int getId() const;

    /// @brief Get the Name of the pattern.
    std::string getName() const;

    /// @brief Get the Path of the pattern.
    std::string getPath() const;

    /// @brief Get the Status (called or not) of the pattern.
    bool getFlag() const;

    /// @brief overloaded operator to write a pattern call to the output file.
    friend std::ostream& operator<<(std::ostream& os, const PatternCall& pc);
    
    /// @brief Parses a PatternCall from a delimited string.
    static std::shared_ptr<const PatternCall> fromString(const std::string& line); 
};



#endif