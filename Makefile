CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -Iinclude


SRC =  source/pattern_call_manager.cpp source/pattern_call.cpp
TEST_SRC = test/test_runner.cpp
MAIN_SRC = source/main.cpp

# Targets
all: test_runner demo_app

test_runner: clean_test $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o test_runner $(SRC) $(TEST_SRC)

demo_app: clean_demo $(SRC) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o demo_app $(SRC) $(MAIN_SRC)

clean_demo:
	rm -f demo_app

clean_test:
	rm -f test_runner test/test_patterns_in.txt test/test_patterns_out.txt

clean:
	rm -f demo_app test_runner