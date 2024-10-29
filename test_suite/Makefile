# Compiler settings
CC = g++
COMPILER_FLAGS = -std=c++20 -Wall --pedantic -g

# Directory structure
SRC_DIR = .
INCLUDE_DIR = ../include
BUILD_DIR = build
BIN_DIR = bin

# Automatically find all test files (test_*.cpp)
TEST_SRCS := $(wildcard $(SRC_DIR)/test_*.cpp)
TESTS := $(patsubst $(SRC_DIR)/test_%.cpp,%,$(TEST_SRCS))

# Common source files
COMMON_SRCS = $(filter-out $(INCLUDE_DIR)/table.cpp,$(wildcard $(INCLUDE_DIR)/*.cpp))

# Create build and bin directories
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Generate object files list
COMMON_OBJS = $(COMMON_SRCS:$(INCLUDE_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
.PHONY: all clean help
all: $(TESTS)

# Pattern rule for common object files
$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/%.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Pattern rule for test object files
$(BUILD_DIR)/test_%.o: $(SRC_DIR)/test_%.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Pattern rule for test executables
.SECONDEXPANSION:
%: $(BUILD_DIR)/test_%.o $(COMMON_OBJS) $$(if $$(findstring table,$$@),$(BUILD_DIR)/table.o)
	$(CC) $(COMPILER_FLAGS) $^ -o $(BIN_DIR)/$@

# Special case for table.cpp
$(BUILD_DIR)/table.o: $(INCLUDE_DIR)/table.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Run all tests
.PHONY: test
test: all
	@echo "Running all tests..."
	@for test in $(TESTS); do \
		echo "\nRunning $$test test:"; \
		$(BIN_DIR)/$$test || exit 1; \
	done

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build all test executables"
	@echo "  clean   - Remove all build artifacts"
	@echo "  test    - Build and run all tests"
	@echo "  help    - Show this help message"
	@echo "\nAvailable test targets:"
	@for test in $(TESTS); do \
		echo "  $$test"; \
	done
