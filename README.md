# Roubamonte - Object-Oriented Card Game Engine

A sophisticated C++20 implementation of the traditional Brazilian card game "Roubamonte" (Portuguese for "Steal the Pile"), demonstrating advanced object-oriented design patterns, modern C++ features, and mathematical game logic.

## 🎯 Project Overview

This project showcases enterprise-level C++ development practices through the implementation of a complete card game engine. The architecture emphasizes clean code principles, comprehensive testing, and extensible design patterns commonly used in complex software systems.

## 🏗️ Architecture & Design

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

Comprehensive test suite covering:
- **Unit Tests**: Individual class functionality validation
- **Integration Tests**: Multi-class interaction verification  
- **Edge Case Testing**: Boundary conditions and error scenarios
- **Automated Build System**: Makefile-based compilation and testing

### Test Coverage
- Card creation and validation
- Deck shuffling and distribution
- Hand management and selection
- Player interactions and game mechanics
- Exception handling and error conditions

## 🛠️ Build System

### Requirements
- **Compiler**: G++ with C++20 support
- **Build Tool**: GNU Make
- **Standards**: C++20, Wall, Pedantic flags enabled

### Building
```bash
# Build all tests
make -C test_suite all

# Run comprehensive test suite
make -C test_suite test

# Build specific component
./build_card.sh    # Test card functionality
./build_deck.sh    # Test deck management
./build_hand.sh    # Test hand operations
```

## 🎮 Game Mechanics

**Roubamonte** is a strategic card matching game where players:
1. Manage a hand of cards with selection capabilities
2. Match card figures to "steal" opponent's collected piles
3. Discard cards to a central tray for opponents to potentially use
4. Employ tactical thinking to maximize pile acquisition

The implementation captures the complete game logic while demonstrating sophisticated programming patterns applicable to any complex interactive system.

## 🚀 Applications Beyond Gaming

This codebase demonstrates patterns directly applicable to:

- **3D Scene Management**: Selection containers mirror 3D object hierarchies
- **Asset Pipeline Systems**: Card distribution patterns parallel asset loading
- **UI/UX Frameworks**: Selection and interaction patterns for interface elements
- **Data Processing Pipelines**: Container management for complex data workflows
- **Mathematical Computing**: Algorithmic thinking and logical operations

## 📁 Project Structure

```
roubamonte/
├── include/                    # Core implementation files
│   ├── card.{h,cpp}           # Card entity and operations
│   ├── deck.{h,cpp}           # Shuffled card collection
│   ├── stack.{h,cpp}          # LIFO card container
│   ├── selection_container.{h,cpp}  # Base selection framework
│   ├── hand.{h,cpp}           # Player card management
│   ├── tray.{h,cpp}           # Central discard system
│   ├── player.{h,cpp}         # Game participant logic
│   └── table.{h,cpp}          # Game state orchestration
├── test_suite/                # Comprehensive testing framework
│   ├── test_*.cpp             # Individual component tests
│   ├── Makefile               # Automated build system
│   └── include/output.h       # Testing utilities and formatters
├── build_*.sh                 # Component-specific build scripts
└── .editorconfig              # Consistent coding standards
```

## 🎯 Key Takeaways

This project demonstrates:
- **Professional C++ Development**: Modern standards, clean architecture, comprehensive testing
- **Mathematical Problem Solving**: Complex algorithmic thinking and logical operations  
- **System Design**: Scalable, maintainable object-oriented architecture
- **Software Engineering Best Practices**: Documentation, testing, build automation

The skills demonstrated here directly translate to enterprise software development, particularly in domains requiring complex data management, mathematical operations, and interactive system design.

---

*This implementation represents a passion project demonstrating deep C++ expertise and software engineering principles through the engaging medium of traditional card game mechanics.*