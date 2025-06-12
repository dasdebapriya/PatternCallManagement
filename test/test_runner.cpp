#include <iostream>
#include <string>
#include <fstream>
#include "pattern_call.h"
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

    PatternCall p = PatternCall::fromString("42,myPattern,src/patterns/Functional.pat,false");
    ASSERT(p.getId() == 42);
    ASSERT(p.getName() == "myPattern");
    ASSERT(p.getPath() == "src/patterns/Functional.pat");
    ASSERT(p.getFlag() == false);
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
    auto pattern = mgr.getById(102);
    ASSERT(pattern != nullptr);
    ASSERT(pattern->getName() == "Init");
    ASSERT(pattern->getPath() == "src/patterns/Init_1.pat");
    ASSERT(pattern->getFlag() == true);

    auto pattern_list = mgr.getByName("SleepSeq");
    ASSERT(pattern_list.size() == 1);
    ASSERT(pattern_list[0].getId() == 302);
    ASSERT(pattern_list[0].getPath() == "src/patterns/Shutdown_1.pat");
    ASSERT(pattern_list[0].getFlag() == false);
    ++tests_passed;
}

void test_PatternCallManager_writeToFile() {
    
    // create and load pattern
    PatternCallManager mgr;
    PatternCall p(1, "name", "path", true);
    mgr.addPatternCall(p);

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

    PatternCallManager mgr;
    PatternCall p1(0, "name1", "path1", true);
    mgr.addPatternCall(p1);
    PatternCall p2(1, "name2", "path2", false);
    mgr.addPatternCall(p2);
    PatternCall p3(2, "name1", "path1", false);
    mgr.addPatternCall(p3);
    PatternCall p4(3, "name2", "path2", true);
    mgr.addPatternCall(p4);

    for(auto i = 0; i < 4; i++) {
        auto pattern = mgr.getById(i);
        switch(i){
            case 0:
            ASSERT(pattern->getName() == "name1");
            ASSERT(pattern->getPath() == "path1");
            ASSERT(pattern->getFlag() == true);
            break;

            case 1:
            ASSERT(pattern->getName() == "name2");
            ASSERT(pattern->getPath() == "path2");
            ASSERT(pattern->getFlag() == false);
            break;

            case 2:
            ASSERT(pattern->getName() == "name1");
            ASSERT(pattern->getPath() == "path1");
            ASSERT(pattern->getFlag() == false);
            break;

            case 3:
            ASSERT(pattern->getName() == "name2");
            ASSERT(pattern->getPath() == "path2");
            ASSERT(pattern->getFlag() == true);
            break;

            default:
            break;
        }        
    }
    ++tests_passed;
}

void test_PatternCallManager_getById(){
    PatternCallManager mgr;
    PatternCall p1(0, "name1", "path1", true);
    mgr.addPatternCall(p1);

    auto pattern = mgr.getById(0);
    ASSERT(pattern->getName() == "name1");
    ASSERT(pattern->getPath() == "path1");
    ASSERT(pattern->getFlag() == true);

    ++tests_passed;
}

void test_PatternCallManager_getByName(){
    PatternCallManager mgr;
    PatternCall p1(0, "name1", "path1", true);
    mgr.addPatternCall(p1);
    PatternCall p2(1, "name2", "path2", false);
    mgr.addPatternCall(p2);
    PatternCall p3(2, "name1", "path1", false);
    mgr.addPatternCall(p3);
    PatternCall p4(3, "name2", "path2", true);
    mgr.addPatternCall(p4);

    auto pattern = mgr.getByName("name1");
    ASSERT(pattern.size() == 2);
    ASSERT(pattern[0].getId() == 0);
    ASSERT(pattern[0].getPath() == "path1");
    ASSERT(pattern[0].getFlag() == true);

    ASSERT(pattern[1].getId() == 2);
    ASSERT(pattern[1].getPath() == "path1");
    ASSERT(pattern[1].getFlag() == false);

    ++tests_passed;
}

void test_PatternCallManager_getByPath(){

    PatternCallManager mgr;
    PatternCall p1(0, "name1", "path1", true);
    mgr.addPatternCall(p1);
    PatternCall p2(1, "name2", "path2", false);
    mgr.addPatternCall(p2);
    PatternCall p3(2, "name1", "path1", false);
    mgr.addPatternCall(p3);
    PatternCall p4(3, "name2", "path2", true);
    mgr.addPatternCall(p4);

    auto pattern = mgr.getByPath("path2");
    ASSERT(pattern.size() == 2);
    ASSERT(pattern[0].getId() == 1);
    ASSERT(pattern[0].getName() == "name2");
    ASSERT(pattern[0].getFlag() == false);

    ASSERT(pattern[1].getId() == 3);
    ASSERT(pattern[1].getName() == "name2");
    ASSERT(pattern[1].getFlag() == true);

    ++tests_passed;
}


void test_PatternCallManager_getSkipped(){
    PatternCallManager mgr;
    PatternCall p1(0, "name1", "path1", true);
    mgr.addPatternCall(p1);
    PatternCall p2(1, "name2", "path2", false);
    mgr.addPatternCall(p2);
    PatternCall p3(2, "name1", "path1", false);
    mgr.addPatternCall(p3);
    PatternCall p4(3, "name2", "path2", true);
    mgr.addPatternCall(p4);

    auto pattern = mgr.getSkipped();
    ASSERT(pattern.size() == 2);
    ASSERT(pattern[0].getId() == 1);
    ASSERT(pattern[0].getName() == "name2");
    ASSERT(pattern[0].getPath() == "path2");

    ASSERT(pattern[1].getId() == 2);
    ASSERT(pattern[1].getName() == "name1");
    ASSERT(pattern[1].getPath() == "path1");

    ++tests_passed;
}

void test_PatternCallManager_getCalled(){
    PatternCallManager mgr;
    PatternCall p1(0, "name1", "path1", true);
    mgr.addPatternCall(p1);
    PatternCall p2(1, "name2", "path2", false);
    mgr.addPatternCall(p2);
    PatternCall p3(2, "name1", "path1", false);
    mgr.addPatternCall(p3);
    PatternCall p4(3, "name2", "path2", true);
    mgr.addPatternCall(p4);

    auto pattern = mgr.getCalled();
    ASSERT(pattern.size() == 2);
    ASSERT(pattern[0].getId() == 0);
    ASSERT(pattern[0].getName() == "name1");
    ASSERT(pattern[0].getPath() == "path1");

    ASSERT(pattern[1].getId() == 3);
    ASSERT(pattern[1].getName() == "name2");
    ASSERT(pattern[1].getPath() == "path2");

    ++tests_passed;
}

int main() {
    test_PatternCall_fromString();
    test_PatternCall_operator_output();
    test_PatternCallManager_loadFromFile();
    test_PatternCallManager_writeToFile();
    test_PatternCallManager_addPatternCall();
    test_PatternCallManager_getById();
    test_PatternCallManager_getByName();
    test_PatternCallManager_getByPath();
    test_PatternCallManager_getSkipped();
    test_PatternCallManager_getCalled();

    std::cout << "\nTests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";

    return tests_failed == 0 ? 0 : 1;
}
