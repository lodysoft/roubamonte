# Project Architecture Documentation

## UML Class Diagram

This directory contains the UML documentation for the Roubamonte card game framework.

### Files

- **`class-diagram.puml`** - PlantUML source file for the complete class diagram
- **`README.md`** - This documentation file

### Viewing the UML Diagram

To generate and view the UML diagram from the PlantUML source:

#### Online Viewers
1. **PlantUML Online Server**: https://www.plantuml.com/plantuml/uml/
   - Copy the contents of `class-diagram.puml` into the text area
   - The diagram will be generated automatically

2. **PlantText**: https://www.planttext.com/
   - Paste the PlantUML code and click "Refresh"

#### Local Tools
1. **VS Code Extension**: Install "PlantUML" extension
   - Open `class-diagram.puml` in VS Code
   - Use `Ctrl+Shift+P` → "PlantUML: Preview Current Diagram"

2. **Command Line** (requires Java and Graphviz):
   ```bash
   # Install PlantUML
   wget https://github.com/plantuml/plantuml/releases/latest/download/plantuml.jar
   
   # Generate SVG diagram
   java -jar plantuml.jar -tsvg class-diagram.puml
   
   # Generate PNG diagram  
   java -jar plantuml.jar -tpng class-diagram.puml
   ```

## Architecture Overview

The Roubamonte framework implements a sophisticated class hierarchy with proven design patterns:

### Core Design Patterns

- **Template Method Pattern** - `selection_container` abstract base with concrete implementations
- **Strategy Pattern** - Dual discard modes in `hand` class
- **Factory Pattern** - `deck` auto-generates complete card sets
- **RAII Pattern** - Exception-safe resource management throughout

### Class Categories

#### Core Entities
- **`card`** - Immutable game entity with figure/suit properties

#### Container Hierarchy
- **`stack`** - LIFO container using `std::stack<card>`
- **`deck`** - Inherits from `stack`, generates and shuffles complete card set
- **`selection_container`** - Abstract base for indexed card containers
- **`hand`** - Player's card management (inherits from `selection_container`)
- **`tray`** - Central game area (inherits from `selection_container`)

#### Game Logic
- **`player`** - Game participant with hand + personal stack
- **`table`** - Multi-player game coordinator

### Key Relationships

- **Inheritance**: `deck` → `stack`, `hand/tray` → `selection_container`
- **Composition**: `table` contains `deck`, `tray`, and collection of `player` objects
- **Dependencies**: Strategic use relationships for game mechanics

### Framework Extensibility

The architecture supports extension to other card games through:
- Polymorphic selection interfaces
- Configurable card counts and game rules  
- Template-based container patterns
- Separation of game logic from card mechanics

For detailed implementation specifications, see the main project documentation in `/README.md` and `/CLAUDE.md`.