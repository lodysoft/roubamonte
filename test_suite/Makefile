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

# For each test_X.cpp, check if X.cpp exists in include dir and add it to the build
TEST_CLASSES := $(patsubst test_%.cpp,%.cpp,$(notdir $(TEST_SRCS)))
CLASS_SRCS := $(wildcard $(INCLUDE_DIR)/*.cpp)
TEST_CLASS_SRCS := $(filter $(addprefix $(INCLUDE_DIR)/,$(TEST_CLASSES)),$(CLASS_SRCS))

# Base classes that should always be included
BASE_CLASSES = player.cpp hand.cpp deck.cpp stack.cpp card.cpp
BASE_SRCS := $(addprefix $(INCLUDE_DIR)/,$(BASE_CLASSES))

# Combine all source files
COMMON_SRCS = $(sort $(BASE_SRCS) $(TEST_CLASS_SRCS))

# Create build and bin directories
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Generate object files list
COMMON_OBJS = $(COMMON_SRCS:$(INCLUDE_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
.PHONY: all clean help test
all: $(TESTS)

# Pattern rule for common object files
$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Pattern rule for test object files
$(BUILD_DIR)/test_%.o: $(SRC_DIR)/test_%.cpp
	@echo "Compiling test $<..."
	@$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Pattern rule for test executables
%: $(BUILD_DIR)/test_%.o $(COMMON_OBJS)
	@echo "Linking $@..."
	@$(CC) $(COMPILER_FLAGS) $^ -o $(BIN_DIR)/$@

# Clean build artifacts
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Run all tests
test: all
	@echo "Running all tests..."
	@for test in $(TESTS); do \
		echo "\nRunning $$test test:"; \
		$(BIN_DIR)/$$test || exit 1; \
	done

# Show dependency info for a specific test
.PHONY: deps-%
deps-%:
	@echo "Dependencies for $*:"
	@echo "  Test source: test_$*.cpp"
	@echo "  Class source: $(filter %/$*.cpp,$(CLASS_SRCS))"
	@echo "  Common sources: $(COMMON_SRCS)"

# Show build info
.PHONY: info
info:
	@echo "Detected test files:"
	@for test in $(TEST_SRCS); do \
		echo "  $$test"; \
	done
	@echo "\nDetected class files:"
	@for class in $(CLASS_SRCS); do \
		echo "  $$class"; \
	done

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build all test executables"
	@echo "  clean   - Remove all build artifacts"
	@echo "  test    - Build and run all tests"
	@echo "  info    - Show detected test and class files"
	@echo "  deps-X  - Show dependencies for test X"
	@echo "  help    - Show this help message"
	@echo "\nAvailable test targets:"
	@for test in $(TESTS); do \
		echo "  $$test"; \
	done
