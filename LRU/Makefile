# Compiler and flags
CXX = g++
CXXFLAGS = -g -fprofile-arcs -ftest-coverage -std=c++17 -Wall -Iinc -O0 --coverage
LDFLAGS = -lgtest -lgtest_main -pthread

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

# Source files
SRCS = $(SRC_DIR)/DoubleLL.cpp $(SRC_DIR)/DoublelyLinkedList.cpp
TEST_SRC = $(TEST_DIR)/DoublelyLinkedListTest.cpp

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TEST_OBJ = $(OBJ_DIR)/DoublelyLinkedListTest.o

# Executable
TEST_EXEC = $(BIN_DIR)/run_tests

# Default target
all: $(TEST_EXEC)

# Link test executable
$(TEST_EXEC): $(OBJS) $(TEST_OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test file to object file
$(OBJ_DIR)/DoublelyLinkedListTest.o: $(TEST_DIR)/DoublelyLinkedListTest.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.gcov gcovr_output

# Code coverage with gcov
coverage: test
	mkdir gcovr_output
	$(CXX) $(CXXFLAGS) --coverage -o $(BIN_DIR)/coverage_test $(OBJS) $(TEST_OBJ) $(LDFLAGS)
	./$(BIN_DIR)/coverage_test
	gcov $(OBJ_DIR)/DoublelyLinkedList.o $(OBJ_DIR)/DoubleLL.o $(OBJ_DIR)/DoublelyLinkedListTest.o
	gcovr --html --output ./gcovr_output/coverage_report.html 
	mv *.gcov ./gcovr_output

# Generate lcov report
lcov_report: test
	lcov --capture --directory . --output-file ./gcovr_output/coverage.info
	genhtml ./gcovr_output/coverage.info --output-directory ./gcovr_output/ 

.PHONY: all test clean coverage lcov_report
