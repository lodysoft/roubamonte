# Compiler settings
CC = g++
COMPILER_FLAGS = -std=c++20 -Wall --pedantic -g -DBOOST_TEST_DYN_LINK

# Directory structure
SRC_DIR = .
INCLUDE_DIR = ../include
BUILD_DIR = build
BIN_DIR = bin
INTERACTIVE_DIR = interactive_tests
UNIT_DIR = unit_tests

# Automatically find all test files (test_*.cpp) in all directories
INTERACTIVE_SRCS := $(wildcard $(INTERACTIVE_DIR)/show_*.cpp)
QA_SRCS := $(wildcard $(UNIT_DIR)/qa/qa_*.cpp)
TDD_SRCS := $(wildcard $(UNIT_DIR)/tdd/tdd_*.cpp)
UNIT_SRCS := $(QA_SRCS) $(TDD_SRCS)
TEST_SRCS := $(INTERACTIVE_SRCS) $(UNIT_SRCS)
TESTS := $(patsubst $(INTERACTIVE_DIR)/show_%.cpp,show_%,$(INTERACTIVE_SRCS)) $(patsubst $(UNIT_DIR)/qa/qa_%.cpp,qa_%,$(QA_SRCS)) $(patsubst $(UNIT_DIR)/tdd/tdd_%.cpp,tdd_%,$(TDD_SRCS))

# For each test_X.cpp, check if X.cpp exists in include dir and add it to the build
TEST_CLASSES := $(patsubst test_%.cpp,%.cpp,$(notdir $(TEST_SRCS)))
CLASS_SRCS := $(wildcard $(INCLUDE_DIR)/*.cpp)
TEST_CLASS_SRCS := $(filter $(addprefix $(INCLUDE_DIR)/,$(TEST_CLASSES)),$(CLASS_SRCS))

# Base classes that should always be included
BASE_CLASSES = selection_container.cpp player.cpp hand.cpp deck.cpp stack.cpp card.cpp tray.cpp table.cpp
BASE_SRCS := $(addprefix $(INCLUDE_DIR)/,$(BASE_CLASSES))

# Combine all source files
COMMON_SRCS = $(sort $(BASE_SRCS) $(TEST_CLASS_SRCS))

# Create build and bin directories
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Generate object files list
COMMON_OBJS = $(COMMON_SRCS:$(INCLUDE_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
.PHONY: all clean help test
all: build-interactive build-qa build-tdd

# Pattern rule for common object files
$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Pattern rule for QA test object files
$(BUILD_DIR)/qa_%.o: $(UNIT_DIR)/qa/qa_%.cpp
	@echo "Compiling QA test $<..."
	@$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Pattern rule for TDD test object files
$(BUILD_DIR)/tdd_%.o: $(UNIT_DIR)/tdd/tdd_%.cpp
	@echo "Compiling TDD test $<..."
	@$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Pattern rule for interactive show object files
$(BUILD_DIR)/show_%.o: $(INTERACTIVE_DIR)/show_%.cpp
	@echo "Compiling interactive show $<..."
	@$(CC) $(COMPILER_FLAGS) -I$(INTERACTIVE_DIR) -c $< -o $@

# Pattern rule for interactive show executables
show_%: $(BUILD_DIR)/show_%.o $(COMMON_OBJS)
	@echo "Linking $@..."
	@$(CC) $(COMPILER_FLAGS) $^ -o $(BIN_DIR)/$@
	@echo "Running $@..."
	@$(BIN_DIR)/$@

# Pattern rule for QA test executables  
qa_%: $(BUILD_DIR)/qa_%.o $(COMMON_OBJS)
	@echo "Linking $@..."
	@$(CC) $(COMPILER_FLAGS) $^ -o $(BIN_DIR)/$@
	@echo "Running $@..."
	@$(BIN_DIR)/$@

# Pattern rule for TDD test executables  
tdd_%: $(BUILD_DIR)/tdd_%.o $(COMMON_OBJS)
	@echo "Linking $@..."
	@$(CC) $(COMPILER_FLAGS) $^ -o $(BIN_DIR)/$@
	@echo "Running $@..."
	@$(BIN_DIR)/$@

# Clean build artifacts
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Pattern rule for building interactive executables only
$(BIN_DIR)/show_%: $(BUILD_DIR)/show_%.o $(COMMON_OBJS)
	@echo "Linking show_$*..."
	@$(CC) $(COMPILER_FLAGS) $^ -o $@

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
	@if [ -f "$(INTERACTIVE_DIR)/show_$*.cpp" ]; then \
		echo "  Test source: $(INTERACTIVE_DIR)/show_$*.cpp (interactive)"; \
	elif [ -f "$(UNIT_DIR)/qa/qa_$*.cpp" ]; then \
		echo "  Test source: $(UNIT_DIR)/qa/qa_$*.cpp (QA)"; \
	elif [ -f "$(UNIT_DIR)/tdd/tdd_$*.cpp" ]; then \
		echo "  Test source: $(UNIT_DIR)/tdd/tdd_$*.cpp (TDD)"; \
	else \
		echo "  Test source: NOT FOUND"; \
	fi
	@echo "  Class source: $(filter %/$*.cpp,$(CLASS_SRCS))"
	@echo "  Common sources: $(COMMON_SRCS)"

# Show build info
.PHONY: info
info:
	@echo "Detected interactive test files:"
	@for test in $(INTERACTIVE_SRCS); do \
		echo "  $$test"; \
	done
	@echo "\nDetected QA test files:"
	@for test in $(QA_SRCS); do \
		echo "  $$test"; \
	done
	@echo "\nDetected TDD test files:"
	@if [ -z "$(TDD_SRCS)" ]; then \
		echo "  (none yet)"; \
	else \
		for test in $(TDD_SRCS); do \
			echo "  $$test"; \
		done; \
	fi
	@echo "\nDetected class files:"
	@for class in $(CLASS_SRCS); do \
		echo "  $$class"; \
	done

# Build interactive test executables without running
.PHONY: build-interactive
build-interactive: $(addprefix $(BIN_DIR)/,$(patsubst $(INTERACTIVE_DIR)/show_%.cpp,show_%,$(INTERACTIVE_SRCS)))

# Run interactive tests only
.PHONY: interactive
interactive: build-interactive
	@echo "Running interactive tests..."
	@for test in $(patsubst $(INTERACTIVE_DIR)/show_%.cpp,show_%,$(INTERACTIVE_SRCS)); do \
		echo "\nRunning $$test (interactive):"; \
		$(BIN_DIR)/$$test || exit 1; \
	done

# Run unit tests only (both QA and TDD)
.PHONY: unit
unit: build-qa build-tdd
	@echo "Running unit tests..."
	@echo "QA tests:"
	@for test in $(patsubst $(UNIT_DIR)/qa/qa_%.cpp,qa_%,$(QA_SRCS)); do \
		echo "\nRunning $$test (QA):"; \
		$(BIN_DIR)/$$test || exit 1; \
	done
	@echo "\nTDD tests:"
	@if [ -z "$(TDD_SRCS)" ]; then \
		echo "No TDD tests found yet."; \
	else \
		for test in $(patsubst $(UNIT_DIR)/tdd/tdd_%.cpp,tdd_%,$(TDD_SRCS)); do \
			echo "\nRunning $$test (TDD):"; \
			$(BIN_DIR)/$$test || exit 1; \
		done; \
	fi

# Build QA test executables without running
.PHONY: build-qa
build-qa: $(addprefix $(BIN_DIR)/,$(patsubst $(UNIT_DIR)/qa/qa_%.cpp,qa_%,$(QA_SRCS)))

# Pattern rule for building QA executables only
$(BIN_DIR)/qa_%: $(BUILD_DIR)/qa_%.o $(COMMON_OBJS)
	@echo "Linking qa_$*..."
	@$(CC) $(COMPILER_FLAGS) $^ -o $@

# Run QA tests only
.PHONY: qa
qa: build-qa
	@echo "Running QA tests..."
	@for test in $(patsubst $(UNIT_DIR)/qa/qa_%.cpp,qa_%,$(QA_SRCS)); do \
		echo "\nRunning $$test (QA):"; \
		$(BIN_DIR)/$$test || exit 1; \
	done

# Build TDD test executables without running
.PHONY: build-tdd
build-tdd: $(addprefix $(BIN_DIR)/,$(patsubst $(UNIT_DIR)/tdd/tdd_%.cpp,tdd_%,$(TDD_SRCS)))

# Pattern rule for building TDD executables only
$(BIN_DIR)/tdd_%: $(BUILD_DIR)/tdd_%.o $(COMMON_OBJS)
	@echo "Linking tdd_$*..."
	@$(CC) $(COMPILER_FLAGS) $^ -o $@

# Run TDD tests only
.PHONY: tdd
tdd: build-tdd
	@echo "Running TDD tests..."
	@if [ -z "$(TDD_SRCS)" ]; then \
		echo "No TDD tests found yet."; \
	else \
		for test in $(patsubst $(UNIT_DIR)/tdd/tdd_%.cpp,tdd_%,$(TDD_SRCS)); do \
			echo "\nRunning $$test (TDD):"; \
			$(BIN_DIR)/$$test || exit 1; \
		done; \
	fi

# Show help
help:
	@echo "Available targets:"
	@echo "  all               - Build all test executables"
	@echo "  clean             - Remove all build artifacts"
	@echo "  test              - Build and run all tests"
	@echo "  interactive       - Build and run interactive tests only"
	@echo "  unit              - Build and run unit tests (QA + TDD)"
	@echo "  qa                - Build and run QA tests only"
	@echo "  tdd               - Build and run TDD tests only"
	@echo "  build-interactive - Build interactive test executables without running"
	@echo "  build-qa          - Build QA test executables without running"
	@echo "  build-tdd         - Build TDD test executables without running"
	@echo "  info              - Show detected test and class files"
	@echo "  deps-X            - Show dependencies for test X"
	@echo "    Valid X values:"
	@echo "$(patsubst $(INTERACTIVE_DIR)/show_%.cpp,%,$(INTERACTIVE_SRCS)) $(patsubst $(UNIT_DIR)/qa/qa_%.cpp,%,$(QA_SRCS)) $(patsubst $(UNIT_DIR)/tdd/tdd_%.cpp,%,$(TDD_SRCS))" | tr ' ' '\n' | sort -u | grep -v '^$$' | sed 's/^/      /'
	@echo "  help              - Show this help message"
	@echo "\nAvailable individual test targets (compile and run):"
	@echo "  Interactive tests (show_*):"
	@for test in $(patsubst $(INTERACTIVE_DIR)/show_%.cpp,show_%,$(INTERACTIVE_SRCS)); do \
		echo "    $$test"; \
	done
	@echo "  QA tests (qa_*):"
	@if [ -z "$(QA_SRCS)" ]; then \
		echo "    (none yet)"; \
	else \
		for test in $(patsubst $(UNIT_DIR)/qa/qa_%.cpp,qa_%,$(QA_SRCS)); do \
			echo "    $$test"; \
		done; \
	fi
	@echo "  TDD tests (tdd_*):"
	@if [ -z "$(TDD_SRCS)" ]; then \
		echo "    (none yet)"; \
	else \
		for test in $(patsubst $(UNIT_DIR)/tdd/tdd_%.cpp,tdd_%,$(TDD_SRCS)); do \
			echo "    $$test"; \
		done; \
	fi
