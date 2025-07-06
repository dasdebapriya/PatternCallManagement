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
     * @brief Generic query PatternCall function for ID, Name, Path and Flag.
     * 
     * @param mMap The multimap with the key as ID/Name/Path/Flag which stores the PatternCall objects as values.     
     * @param key The key (ID, Name, Path and Flag) for which the PatternCall objects are queried.
     * @return The list of PatternCall pointers corresponding to the key.
     */
    template <typename T>
    std::shared_ptr<std::vector<std::shared_ptr<const PatternCall>>> getByKey(const std::multimap<T, std::shared_ptr<const PatternCall>>& mMap, const T& key) const { // total time complexity : O(log n) + k * O(1)

        std::shared_ptr<std::vector<std::shared_ptr<const PatternCall>>> spResults = std::make_shared<std::vector<std::shared_ptr<const PatternCall>>>();
        auto range = mMap.equal_range(key); // complexity O(log n), n is the number of items in m_nameIndex
    
        for (auto it = range.first; it != range.second; ++it) { // k is the number of items in range

            spResults->push_back(it->second); // complexity O(1) for results.push_back
        }
        return spResults;
    }

    /**
     * @brief get ID multimap
     * 
     * @return The ID multimap 
     */
    const std::multimap<int, std::shared_ptr<const PatternCall>>& getIdMmap() const;
    /**
     * @brief get name multimap .
     * 
     * @return The name multimap 
     */
    const std::multimap<std::string, std::shared_ptr<const PatternCall>>& getNameMmap() const;

    /**
     * @brief get path multimap .
     * 
     * @return The path multimap 
     */
    const std::multimap<std::string, std::shared_ptr<const PatternCall>>& getPathMmap() const;

    /**
     * @brief get flag multimap .
     * 
     * @return The flag multimap 
     */
    const std::multimap<bool, std::shared_ptr<const PatternCall>>& getFlagMmap() const;

    
private:
    std::multimap<int, std::shared_ptr<const PatternCall>> m_idIndex;
    std::multimap<std::string, std::shared_ptr<const PatternCall>> m_nameIndex;
    std::multimap<std::string, std::shared_ptr<const PatternCall>> m_pathIndex;
    std::multimap<bool, std::shared_ptr<const PatternCall>> m_flagIndex;
};


#endif
