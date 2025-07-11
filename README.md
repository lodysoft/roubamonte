# Roubamonte - Object-Oriented Card Game Engine

A sophisticated C++20 implementation of the traditional Brazilian card game "Roubamonte" (Portuguese for "Steal the Pile"), demonstrating advanced object-oriented design patterns, modern C++ features, and mathematical game logic.

## 🎯 Project Overview

This project showcases enterprise-level C++ development practices through the implementation of a **reusable card game engine framework**. Rather than a single-purpose application, this represents a foundational library designed for extensibility - enabling rapid development of diverse card-based games (pirate adventures, alien encounters, fantasy realms, etc.) through inheritance and composition patterns.

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
- **Framework Architecture Design**: Building extensible libraries rather than single-purpose applications
- **Professional C++ Development**: Modern standards, clean architecture, comprehensive testing
- **Mathematical Problem Solving**: Complex algorithmic thinking and logical operations  
- **System Design**: Scalable, maintainable object-oriented architecture enabling rapid iteration
- **Game Engine Patterns**: Core mechanics separation from theme implementation
- **Software Engineering Best Practices**: Documentation, testing, build automation, and future-proofing

The skills demonstrated here directly translate to enterprise software development, particularly in domains requiring extensible frameworks, complex data management, mathematical operations, and interactive system design.

---

*This implementation represents a **framework-first approach** to software design, demonstrating deep C++ expertise and systems architecture thinking through the foundation of a reusable card game engine capable of supporting diverse gaming experiences.*