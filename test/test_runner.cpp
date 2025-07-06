#include <iostream>
#include <string>
#include <fstream>
//#include "pattern_call.h"
#include "pattern_call_manager.h"


int tests_passed = 0;
int tests_failed = 0;

#define ASSERT(cond) do { \
    if (!(cond)) { \
        std::cerr << "Assertion failed: " << #cond << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
        ++tests_failed; \
        return; \
    } \
} while (0)

void test_PatternCall_fromString() {

    std::shared_ptr<const PatternCall> spPc = PatternCall::fromString("42,myPattern,src/patterns/Functional.pat,false");
    ASSERT(spPc->getId() == 42);
    ASSERT(spPc->getName() == "myPattern");
    ASSERT(spPc->getPath() == "src/patterns/Functional.pat");
    ASSERT(spPc->getFlag() == false);
    ++tests_passed;
}


void test_PatternCall_operator_output() {
    PatternCall p(1, "name", "path", true);
    std::ostringstream oss;
    oss << p;
    ASSERT(oss.str() == "1,name,path,true");
    ++tests_passed;
}

void test_PatternCallManager_loadFromFile() {
    
    // create file with patterns
    const std::string testFilePath = "test/test_patterns_in.txt";
    std::ofstream os(testFilePath);
    os << "302,SleepSeq,src/patterns/Shutdown_1.pat,false\n";
    os << "102,Init,src/patterns/Init_1.pat,true\n";
    os.close();

    // load data from file
    PatternCallManager mgr;
    mgr.loadFromFile(testFilePath);

    // validate loaded pattern
    auto spPatternList = mgr.getByKey(mgr.getIdMmap() ,102);
    for(auto spPattern : *spPatternList) {
        ASSERT(spPatternList->size() == 1);
        ASSERT(spPattern->getName() == "Init");
        ASSERT(spPattern->getPath() == "src/patterns/Init_1.pat");
        ASSERT(spPattern->getFlag() == true);
    }
    std::string str = "SleepSeq";
    spPatternList = mgr.getByKey(mgr.getNameMmap(), str);
    for(auto spPattern : *spPatternList) {
        ASSERT(spPatternList->size() == 1);
        ASSERT(spPattern->getId() == 302);
        ASSERT(spPattern->getPath() == "src/patterns/Shutdown_1.pat");
        ASSERT(spPattern->getFlag() == false);
    }
    ++tests_passed;
}

void test_PatternCallManager_writeToFile() {
    
    // create and load pattern
    PatternCallManager mgr;
    
    std::shared_ptr<const PatternCall> spPc = std::make_shared<const PatternCall>(1, "name", "path", true);
    mgr.addPatternCall(spPc);

    // write to file
    const std::string testFilePath = "test/test_patterns_out.txt";
    mgr.writeToFile(testFilePath);

    // read pattern from file
    std::ifstream is(testFilePath);
    std::string line;
    std::getline(is, line);
    
    // validate
    ASSERT(line == "1,name,path,true");

    ++tests_passed;
}

void test_PatternCallManager_addPatternCall() {

    bool pass = true;
    PatternCallManager mgr;
    std::shared_ptr<const PatternCall> spP1 = std::make_shared<const PatternCall>(0, "name1", "path1", true);
    mgr.addPatternCall(spP1);
    std::shared_ptr<const PatternCall> spP2 = std::make_shared<const PatternCall>(1, "name2", "path2", false);
    mgr.addPatternCall(spP2);
    std::shared_ptr<const PatternCall> spP3 = std::make_shared<const PatternCall>(2, "name1", "path1", false);
    mgr.addPatternCall(spP3);
    std::shared_ptr<const PatternCall> spP4 = std::make_shared<const PatternCall>(3, "name2", "path2", true);
    mgr.addPatternCall(spP4);

    for(auto i = 0; i < 4; i++) {
        auto spPatternList = mgr.getByKey(mgr.getIdMmap(), i);
        switch(i){
            case 0:
            for(auto spPattern : *spPatternList) {
                ASSERT(spPattern->getName() == "name1");
                ASSERT(spPattern->getPath() == "path1");
                ASSERT(spPattern->getFlag() == true);
            }
            break;

            case 1:
            for(auto spPattern : *spPatternList) {
                ASSERT(spPattern->getName() == "name2");
                ASSERT(spPattern->getPath() == "path2");
                ASSERT(spPattern->getFlag() == false);
            }
            
            break;

            case 2:
            for(auto spPattern : *spPatternList) {
                ASSERT(spPattern->getName() == "name1");
                ASSERT(spPattern->getPath() == "path1");
                ASSERT(spPattern->getFlag() == false);
            }
            
            break;

            case 3:
            for(auto spPattern : *spPatternList) {
                ASSERT(spPattern->getName() == "name2");
                ASSERT(spPattern->getPath() == "path2");
                ASSERT(spPattern->getFlag() == true);
            }
            break;

            default:
                pass = false;
            break;
        }        
    }
    if(pass) {
        ++tests_passed;
    }
}


void test_PatternCallManager_getByKey(){
    PatternCallManager mgr;
    std::shared_ptr<const PatternCall> spP1 = std::make_shared<const PatternCall>(0, "name1", "path1", true);
    mgr.addPatternCall(spP1);

    // ID is valid
    auto spPcList = mgr.getByKey(mgr.getIdMmap(), 0);
     for (auto spPattern : *spPcList) {
        ASSERT(spPattern->getName() == "name1");
        ASSERT(spPattern->getPath() == "path1");
        ASSERT(spPattern->getFlag() == true);
     }

    // ID is invalid
    spPcList = mgr.getByKey(mgr.getIdMmap(), 1);
    ASSERT(spPcList->size() == 0);

    // Name is valid
    std::string str = "name1";
    spPcList = mgr.getByKey(mgr.getNameMmap(), str);
    for (auto spPattern : *spPcList) {
        ASSERT(spPattern->getId() == 0);
        ASSERT(spPattern->getPath() == "path1");
        ASSERT(spPattern->getFlag() == true);
    }

    // Name is invalid
    str = "name";
    spPcList = mgr.getByKey(mgr.getNameMmap(), str);
    ASSERT(spPcList->size() == 0);

    // Path is valid
    str = "path1";
    spPcList = mgr.getByKey(mgr.getPathMmap(),str);
    for (auto spPattern : *spPcList) {
        ASSERT(spPattern->getId() == 0);
        ASSERT(spPattern->getName() == "name1");
        ASSERT(spPattern->getFlag() == true);
    }

    // Path is invalid
    str = "path";
    spPcList = mgr.getByKey(mgr.getPathMmap(), str);
    ASSERT(spPcList->size() == 0);

    // Flag is valid 
    spPcList = mgr.getByKey(mgr.getFlagMmap(),true);
    for (auto spPattern : *spPcList) {
        ASSERT(spPattern->getId() == 0);
        ASSERT(spPattern->getPath() == "path1");
        ASSERT(spPattern->getName() == "name1");
    }

    // Flag is invalid 
    spPcList = mgr.getByKey(mgr.getFlagMmap(), false);
    ASSERT(spPcList->size() == 0);

    ++tests_passed;
}


int main() {
    test_PatternCall_fromString();
    test_PatternCall_operator_output();
    test_PatternCallManager_loadFromFile();
    test_PatternCallManager_writeToFile();
    test_PatternCallManager_addPatternCall();
    test_PatternCallManager_getByKey();

    std::cout << "\nTests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";

    return tests_failed == 0 ? 0 : 1;
}
