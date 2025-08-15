# Roubamonte - Object-Oriented Card Game Engine

A sophisticated C++20 implementation of the traditional Brazilian card game "Roubamonte" (Portuguese for "Steal the Pile"), currently under active development to demonstrate advanced object-oriented design patterns, modern C++ features, and mathematical game logic.

## 🎯 Project Overview

This project showcases enterprise-level C++ development practices through the implementation of a **reusable card game engine framework**. Rather than a single-purpose application, this represents a foundational library being designed for extensibility - with the goal of enabling rapid development of diverse card-based games (pirate adventures, alien encounters, fantasy realms, etc.) through inheritance and composition patterns.

The architecture emphasizes clean code principles, comprehensive testing, and extensible design patterns commonly used in complex software systems and game engine development.

## 🏗️ Architecture & Design

### Framework Design Philosophy

- **Extensibility First**: Core classes designed with `protected` access modifiers enabling inheritance-based customization
- **Pluggable Game Logic**: Abstract interfaces allowing easy implementation of different game rule sets
- **Theme Independence**: Card and game mechanics separated from visual/thematic representation
- **Modular Architecture**: Each component can be extended or replaced without affecting the entire system

### Core Design Principles

- **RAII (Resource Acquisition Is Initialization)**: All resources are properly managed through constructors and destructors
- **Single Responsibility Principle**: Each class has a focused, well-defined purpose
- **Inheritance & Polymorphism**: Leveraging object-oriented patterns for code reuse and extensibility
- **Exception Safety**: Robust error handling with appropriate exception types
- **Modern C++20 Features**: Utilizing contemporary C++ standards and best practices

### Class Hierarchy

```
selection_container (Abstract Base)
├── hand (Player's cards with selection capability)
└── tray (Central discard pile with selection capability)

stack (Card container)
└── deck (Shuffled card collection)

card (Fundamental game entity)
player (Game participant with hand and stack)
table (Game state manager)
```

### Key Components

#### **Card System**
- **`card`**: Immutable card entity with figure and suit properties
- **`stack`**: LIFO container for card collections using STL stack adapter
- **`deck`**: Auto-shuffled card collection inheriting from stack, implements Fisher-Yates shuffle

#### **Selection Framework**
- **`selection_container`**: Abstract base class providing selection and indexing capabilities
- **`hand`**: Player's personal cards with discard functionality
- **`tray`**: Shared card pool with dynamic growth through discards

#### **Game Logic**
- **`player`**: Encapsulates game participant with hand management and stealing mechanics
- **`table`**: Orchestrates overall game state and player interactions

## 🔧 Technical Features

### Modern C++20 Implementation
- **Smart Memory Management**: No raw pointers, leveraging RAII patterns
- **STL Integration**: Extensive use of standard containers (vector, map, set, stack, list)
- **Exception Safety**: Proper exception handling with standard library exceptions
- **Template Usage**: Generic programming patterns where appropriate
- **Const Correctness**: Immutable interfaces where data shouldn't be modified

### Advanced Data Structures
- **Hybrid Container Design**: Combining STL containers for optimal performance
- **Automatic Sorting**: Cards auto-sorted using custom comparison operators
- **Dynamic Index Management**: Efficient card removal with automatic reindexing
- **State Validation**: Comprehensive bounds checking and state validation

### Mathematical Operations
- **Card Comparison Logic**: Custom ordering algorithms for gameplay mechanics
- **Shuffling Algorithms**: Cryptographically sound randomization using time-based seeding
- **Game State Calculations**: Complex interaction between multiple game entities

## 🧪 Testing Framework

Professional multi-tier test suite with enterprise-grade testing standards:

### Test Categories
- **Interactive Tests** (`show_*`): Visual demonstration and manual validation with real-time output
- **QA Tests** (`qa_*`): Quality assurance validation using **Boost Test framework** for robust error reporting
- **TDD Tests** (`tdd_*`): Test-driven development with behavior specification before implementation
- **Automated Build System**: Advanced Makefile with intelligent target detection and execution control

### Professional Testing Standards
- **Boost Test Integration**: QA tests use industry-standard Boost Test framework for enhanced reliability
- **Silent Success Model**: Professional QA tests run silently, reporting only failures or success confirmation
- **Comprehensive Error Reporting**: Detailed assertion failures with context and expectations
- **Dynamic Test Discovery**: Build system automatically detects and incorporates new tests

### Test Structure
```
test_suite/
├── interactive_tests/     # Visual demos (show_*.cpp) with user interaction
├── unit_tests/
│   ├── qa/                # Professional QA tests (qa_*.cpp) using Boost Test
│   └── tdd/               # Specification tests (tdd_*.cpp) for new features
├── build/                 # Compilation artifacts  
└── bin/                   # Test executables
```

### Comprehensive Test Coverage

#### **Complete QA Test Suite (Boost Framework)**
All 8 core classes have dedicated professional QA test suites:
- **`qa_card.cpp`** - Card creation, comparison operators, boundary figures, joker handling (8 test cases)
- **`qa_deck.cpp`** - Deck construction, shuffle randomness, completeness validation, inheritance (6 test cases)
- **`qa_stack.cpp`** - LIFO behavior, push/pop operations, consistency checks (7 test cases)
- **`qa_hand.cpp`** - Hand management, discard operations, selection mechanics (6 test cases)
- **`qa_tray.cpp`** - Tray operations, dynamic growth, card reception (6 test cases)
- **`qa_player.cpp`** - Player interactions, stealing mechanics, state independence (7 test cases)
- **`qa_table.cpp`** - Game coordination, card distribution, multi-player scenarios (8 test cases)
- **`qa_selection_container.cpp`** - Abstract base functionality, polymorphic behavior (9 test cases)

#### **Interactive Demonstration Tests**
- **`show_card.cpp`** - Visual card representation
- **`show_deck.cpp`** - Shuffled deck display
- **`show_hand.cpp`** - **Interactive** hand selection with robust input validation
- **`show_player.cpp`** - Player state and stealing demonstrations
- **`show_stack.cpp`** - Stack operations visualization  
- **`show_table.cpp`** - Complete game state display
- **`show_tray.cpp`** - **Interactive** tray selection with robust input validation

#### **Test Categories Coverage**
- **Unit Testing**: 57+ individual test cases across all core classes
- **Integration Testing**: Multi-component interaction validation
- **Boundary Testing**: Edge cases, invalid inputs, resource limits
- **Behavioral Testing**: Game logic, stealing mechanics, card interactions
- **Exception Safety**: std::out_of_range handling, invalid operations
- **User Input Validation**: Fool-proof interactive test interfaces

## 🔧 Prerequisites & Dependencies

### System Requirements
- **C++20 Compatible Compiler** (GCC 10+, Clang 10+, MSVC 2019+)
- **GNU Make** or equivalent build system
- **Boost Test Library** for QA testing framework

### Dependency Installation

#### **Linux Distributions**

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential g++ make libboost-test-dev
```

**Fedora/RHEL/CentOS:**
```bash
sudo dnf install gcc-c++ make boost-devel
# Or for older versions:
sudo yum install gcc-c++ make boost-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel gcc make boost
```

**openSUSE:**
```bash
sudo zypper install gcc-c++ make boost-devel
```

**Alpine Linux:**
```bash
sudo apk add build-base g++ make boost-dev
```

#### **macOS**

**Using Homebrew (Recommended):**
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install gcc make boost
```

**Using MacPorts:**
```bash
sudo port install gcc10 +universal boost +universal
```

#### **Windows**

**Using MSYS2 (Recommended for Windows):**
```bash
# Install MSYS2 first from https://www.msys2.org/
# Then in MSYS2 terminal:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-boost

# Add the bin directory (e.g., C:\mingw-w64\bin) to your system PATH
# Add the bin directory (e.g., C:\msys64\usr\bin) to your system PATH
```

**Using Visual Studio:**
```bash
# Install Visual Studio 2019+ with C++ workload
# Install vcpkg package manager
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install boost-test:x64-windows
```

**Using Chocolatey:**
```powershell
# Install Chocolatey first, then:
choco install mingw make
# Boost installation varies, recommend MSYS2 approach
```

#### **Embedded Platforms**

**Raspberry Pi (Raspberry Pi OS):**
```bash
sudo apt update
sudo apt install build-essential g++ make libboost-test-dev
# For older Pi models, compilation may be slower but fully supported
```

**Cross-compilation setup (if targeting embedded ARM):**
```bash
sudo apt install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
# Modify Makefile CC variable for cross-compilation
```

#### **Container/Docker Setup**

**Ubuntu-based container:**
```dockerfile
FROM ubuntu:22.04
RUN apt update && apt install -y build-essential g++ make libboost-test-dev
WORKDIR /roubamonte
COPY . .
RUN make -C test_suite all
```

### Verification Commands

**Verify installation:**
```bash
# Check C++20 support
g++ --version
g++ -std=c++20 -E -x c++ - </dev/null >/dev/null && echo "C++20 supported" || echo "C++20 not supported"

# Check Make
make --version

# Check Boost Test (compile simple test)
echo '#include <boost/test/included/unit_test.hpp>' | g++ -x c++ -c - && echo "Boost Test available" || echo "Boost Test missing"
```

**Minimum version requirements:**
- **GCC**: 10.0+ (for full C++20 support)
- **Clang**: 10.0+ (for full C++20 support)  
- **MSVC**: 2019+ (Visual Studio 16.0+)
- **Boost**: 1.70+ (for modern test framework features)

## 🛠️ Build System

### Technical Requirements Summary
- **Compiler**: G++ with C++20 support
- **Build Tool**: GNU Make
- **Testing Framework**: Boost Test library for QA tests
- **Standards**: C++20, Wall, Pedantic flags enabled

### Smart Build Architecture
The build system features intelligent target management with separate compilation and execution phases:

#### Execution Targets (Compile + Run)
```bash
# Navigate to test suite
cd test_suite

# Comprehensive test execution
make test          # Build and run all tests (interactive + unit)
make interactive   # Build and run visual demonstration tests
make qa            # Build and run quality assurance tests  
make tdd           # Build and run test-driven development tests
make unit          # Build and run all unit tests (QA + TDD)

# Individual component testing (compile + run)
# Interactive demonstrations
make show_card     # Visual card representation
make show_deck     # Shuffled deck display
make show_hand     # Interactive hand selection (input validation)
make show_player   # Player state and stealing mechanics
make show_stack    # Stack operations visualization
make show_table    # Complete game state display
make show_tray     # Interactive tray selection (input validation)

# Professional QA validation tests
make qa_card       # Card class comprehensive testing
make qa_deck       # Deck shuffling and inheritance testing  
make qa_stack      # Stack LIFO behavior and operations
make qa_hand       # Hand management and discard testing
make qa_tray       # Tray dynamic growth and operations
make qa_player     # Player interactions and stealing logic
make qa_table      # Game coordination and card distribution
make qa_selection_container  # Abstract base class functionality
```

#### Build-Only Targets (Compile Without Execution)
```bash
make all               # Build all test executables
make build-interactive # Build interactive tests only
make build-qa          # Build QA tests only  
make build-tdd         # Build TDD tests only
```

#### Development Utilities
```bash
make clean         # Remove all build artifacts
make info          # Show detected test and class files
make deps-card     # Show dependencies for card component
make deps-deck     # Show dependencies for deck component
make deps-stack    # Show dependencies for stack component
make deps-hand     # Show dependencies for hand component
make deps-tray     # Show dependencies for tray component
make deps-player   # Show dependencies for player component
make deps-table    # Show dependencies for table component
make help          # Dynamic help with all available targets
```

### Dynamic Help System
The build system features intelligent help that automatically detects and categorizes available tests:
- **Automatic Test Discovery**: New tests are detected and included automatically
- **Categorized Display**: Tests organized by type (Interactive, QA, TDD)  
- **Valid Dependencies**: Shows all valid options for `deps-X` commands
- **Professional Formatting**: Clean, aligned output for easy reference

## 🎮 Game Mechanics

**Roubamonte** is a strategic card matching game where players:
1. Manage a hand of cards with selection capabilities
2. Match card figures to "steal" opponent's collected piles
3. Discard cards to a central tray for opponents to potentially use
4. Employ tactical thinking to maximize pile acquisition

The implementation captures the complete game logic while demonstrating sophisticated programming patterns applicable to any complex interactive system.

## 🚀 Framework Applications

This engine framework demonstrates patterns directly applicable to:

- **Game Engine Development**: Modular component systems for diverse game types
- **3D Scene Management**: Selection containers mirror 3D object hierarchies and asset management
- **Plugin Architecture Systems**: Extensible base classes enabling custom game implementations
- **Asset Pipeline Frameworks**: Card distribution patterns parallel complex asset loading systems
- **Interactive Application Development**: Selection and state management for user interface systems
- **Mathematical Computing Libraries**: Algorithmic frameworks for logical operations and data processing

### Potential Game Extensions

The framework's extensible design enables rapid development of:
- **Pirate Card Adventures**: Maritime-themed mechanics with treasure hunting
- **Sci-Fi Alien Encounters**: Space exploration with alien artifact collection
- **Fantasy Realm Quests**: Magic-based card interactions and spell combinations
- **Educational Mathematics Games**: Number theory and calculation-based gameplay
- **Strategy War Games**: Military unit management and tactical card play

## 📁 Project Structure

```
roubamonte/
├── include/                         # Core implementation files
│   ├── card.{h,cpp}                 # Card entity and operations
│   ├── deck.{h,cpp}                 # Shuffled card collection
│   ├── stack.{h,cpp}                # LIFO card container
│   ├── selection_container.{h,cpp}  # Base selection framework
│   ├── hand.{h,cpp}                 # Player card management
│   ├── tray.{h,cpp}                 # Central discard system
│   ├── player.{h,cpp}               # Game participant logic
│   └── table.{h,cpp}                # Game state orchestration
├── test_suite/                      # Professional testing framework
│   ├── interactive_tests/           # Visual demonstration tests
│   │   ├── show_*.cpp               # Interactive component demonstrations
│   │   └── include/output.h         # Testing utilities and formatters
│   ├── unit_tests/                  # Enterprise-grade unit testing
│   │   ├── qa/                      # Quality assurance with Boost Test
│   │   │   └── qa_*.cpp             # Professional validation tests
│   │   └── tdd/                     # Test-driven development
│   │       └── tdd_*.cpp            # Specification-first behavior tests
│   ├── Makefile                     # Intelligent build system with dynamic targets
│   ├── bin/                         # Test executables organized by category
│   └── build/                       # Compilation artifacts and object files
├── STYLE_GUIDE.md                   # Development guidelines and conventions
└── README.md                        # Project documentation
```

### Naming Conventions
- **Interactive Tests**: `show_*.cpp` - Visual demonstrations with user interaction
- **QA Tests**: `qa_*.cpp` - Professional validation using Boost Test framework  
- **TDD Tests**: `tdd_*.cpp` - Specification-driven development tests
- **Core Classes**: Lowercase names following Hungarian notation patterns
- **Build Targets**: Semantic naming reflecting test categories and build phases

## 🎯 Key Takeaways

This project demonstrates:
- **Framework Architecture Design**: Building extensible libraries rather than single-purpose applications
- **Professional C++ Development**: Modern C++20 standards, clean architecture, enterprise-grade testing
- **Advanced Build Systems**: Intelligent Makefile with dynamic target detection and execution control
- **Testing Excellence**: Professional Boost Test integration with categorized test methodologies
- **Mathematical Problem Solving**: Complex algorithmic thinking and logical operations  
- **System Design**: Scalable, maintainable object-oriented architecture enabling rapid iteration
- **Game Engine Patterns**: Core mechanics separation from theme implementation  
- **DevOps Automation**: Smart build targets, dynamic help systems, and developer-friendly tooling
- **Software Engineering Best Practices**: Documentation, testing, build automation, and future-proofing

### Technical Excellence Features
- **Complete Test Coverage**: 57+ comprehensive test cases covering all 8 core classes
- **Zero Execution Duplication**: Sophisticated build system preventing redundant test runs
- **Dynamic Discovery**: Automatic detection and integration of new tests and components
- **Professional Testing Standards**: Industry-standard Boost Test framework for QA reliability  
- **Fool-Proof User Interfaces**: Robust input validation in interactive components
- **Intelligent Help System**: Self-documenting build system with categorized target display
- **Semantic Naming**: Clear, consistent naming conventions for maintainability
- **Scalable Architecture**: Framework proven to handle extensive test suites efficiently

The skills demonstrated here directly translate to enterprise software development, particularly in domains requiring extensible frameworks, complex data management, mathematical operations, and interactive system design.

---

*This implementation represents a **framework-first approach** to software design, demonstrating deep C++ expertise and systems architecture thinking through the foundation of a reusable card game engine capable of supporting diverse gaming experiences.*