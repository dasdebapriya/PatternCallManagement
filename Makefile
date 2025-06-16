CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -Iinclude


SRC =  source/pattern_call_manager.cpp source/pattern_call.cpp
TEST_SRC = test/test_runner.cpp
MAIN_SRC = source/main.cpp

# Targets
all: test_runner patternCall_app

test_runner: clean_test $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o test_runner $(SRC) $(TEST_SRC)

patternCall_app: clean_app $(SRC) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o patternCall_app $(SRC) $(MAIN_SRC)

clean_app:
	rm -f patternCall_app

clean_test:
	rm -f test_runner test/test_patterns_in.txt test/test_patterns_out.txt

clean:
	rm -f patternCall_app test_runner