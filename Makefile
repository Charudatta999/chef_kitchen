# Compiler and flags
CXX = g++
CXXFLAGS = -g -fprofile-arcs -ftest-coverage -std=c++17 -Wall -Iinc -O0 --coverage
LDFLAGS = -lgtest -lgtest_main -pthread

# Directories
SRC_DIR = src
STRUCT_SRC_DIR= $(SRC_DIR)/structures
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

# Source files
STRUCT_SRC = $(STRUCT_DIR)/DoubleLL.cpp $(STRUCT_DIR)/DoublelyLinkedList.cpp $(STRUCT_DIR)/Lru.cpp
TEST_SRCS = $(TEST_DIR)/maintest.cpp $(TEST_DIR)/DoublelyLinkedListTest.cpp $(TEST_DIR)/LruTests.cpp

SRCS = $(STRUCT_SRC)
# Object files
OBJS = $(patsubst $(STRUCT_SRC)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

# Executable
TEST_EXEC = $(BIN_DIR)/run_tests

# Default target
all: $(TEST_EXEC)

# Link test executable
$(TEST_EXEC): $(OBJS) $(TEST_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files with explicit dependencies
$(OBJ_DIR)/DoubleLL.o: $(SRC_DIR)/DoubleLL.cpp $(INC_DIR)/DoubleLL.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/DoublelyLinkedList.o: $(SRC_DIR)/DoublelyLinkedList.cpp $(INC_DIR)/DoublelyLinkedList.hpp $(INC_DIR)/DoubleLL.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/Lru.o: $(SRC_DIR)/Lru.cpp $(INC_DIR)/Lru.hpp $(INC_DIR)/DoublelyLinkedList.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test files to object files with explicit dependencies
$(OBJ_DIR)/maintest.o: $(TEST_DIR)/maintest.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/DoublelyLinkedListTest.o: $(TEST_DIR)/DoublelyLinkedListTest.cpp $(INC_DIR)/DoublelyLinkedList.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/LruTests.o: $(TEST_DIR)/LruTests.cpp $(INC_DIR)/Lru.hpp | $(OBJ_DIR)
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
	mkdir -p gcovr_output
	$(CXX) $(CXXFLAGS) --coverage -o $(BIN_DIR)/coverage_test $(OBJS) $(TEST_OBJS) $(LDFLAGS)
	./$(BIN_DIR)/coverage_test
	gcov $(OBJS)
	gcovr --html --output ./gcovr_output/coverage_report.html
	mv *.gcov ./gcovr_output

# Generate lcov report
lcov_report: test
	lcov --capture --directory . --output-file ./gcovr_output/coverage.info
	genhtml ./gcovr_output/coverage.info --output-directory ./gcovr_output/

.PHONY: all test clean coverage lcov_report