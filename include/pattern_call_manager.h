// pattern_call_manager.h
#ifndef PATTERN_CALL_MANAGER_H
#define PATTERN_CALL_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "pattern_call.h"


/**
 * @brief Manages the pattern call objects.
 */
class PatternCallManager {
public:
    /**
     * @brief Read all the PatternCall tuples from an input file.
     * 
     * @param filePath The input file path.
     */
    void loadFromFile(const std::string& filePath);

    /**
     * @brief Write all the PatternCall objects to an output file.
     * 
     * @param filePath The output file path.
     */
    void writeToFile(const std::string& filePath) const;

    /**
     * @brief Add a new PatternCall to the manager.
     * 
     * @param pc The PatternCall to add.
     */
    void addPatternCall(std::shared_ptr<const PatternCall> scPc);

    /**
     * @brief Query PatternCall through an ID.
     * 
     * @param id The ID for which the PatternCall is queried.
     * @return The PatternCall corresponding to the id
     */
    std::shared_ptr<const PatternCall> getById(int id) const;

    /**
     * @brief Query PatternCall through a Name.
     * 
     * @param name The name for which the PatternCall objects are queried.
     * @return The list of PatternCall objects corresponding to the name
     */
    std::vector<std::shared_ptr<const PatternCall>> getByName(const std::string& name) const;

    /**
     * @brief Query PatternCall through a path.
     * 
     * @param path The path for which the PatternCall objects are queried.
     * @return The list of PatternCall objects corresponding to the path
     */
    std::vector<std::shared_ptr<const PatternCall>> getByPath(const std::string& path) const;

    /**
     * @brief Query PatternCall through the call status.
     * 
     * @return The list of PatternCall objects which are not called 
     */
    std::vector<std::shared_ptr<const PatternCall>> getSkipped() const;

    /**
     * @brief Query PatternCall through the call status.
     * 
     * @return The list of PatternCall objects which are called 
     */
    std::vector<std::shared_ptr<const PatternCall>> getCalled() const;
    
private:
    std::map<int, std::shared_ptr<const PatternCall>> m_byId; 
    std::multimap<std::string, int> m_nameIndex;
    std::multimap<std::string, int> m_pathIndex;
    std::set<int> m_skipped;
    std::set<int> m_called;
};

#endif
