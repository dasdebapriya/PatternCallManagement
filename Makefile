CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -Iinclude


SRC =  source/pattern_call_manager.cpp 
TEST_SRC = test/pattern_call_tests.cpp
MAIN_SRC = source/main.cpp

# Targets
all: test_runner demo_app

test_runner: $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o test_runner $(SRC) $(TEST_SRC)

demo_app: $(SRC) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o demo_app $(SRC) $(MAIN_SRC)

clean:
	rm -f test_runner demo_app
