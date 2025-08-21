# Project Architecture Documentation

## UML Class Diagram

This directory contains the UML documentation for the Roubamonte card game framework.

### Files

- **`class-diagram.md`** - Mermaid UML class diagram with complete architecture
- **`README.md`** - This documentation file

### Viewing the UML Diagram

The UML diagram uses **Mermaid** syntax and renders automatically on GitHub. Simply view `class-diagram.md` to see the complete class diagram.

#### GitHub (Recommended)
- **Direct viewing**: Open `class-diagram.md` in GitHub interface
- **Automatic rendering**: No additional tools needed
- **Always up-to-date**: Diagram updates automatically with code changes

#### Alternative Viewers
1. **VS Code Extension**: Install "Mermaid Preview" extension
   - Open `class-diagram.md` in VS Code  
   - Use preview mode to render the diagram

2. **Online Mermaid Editors**:
   - **Mermaid Live Editor**: https://mermaid-js.github.io/mermaid-live-editor/
   - **Mermaid Chart**: https://www.mermaidchart.com/
   - Copy the mermaid code block and paste into the editor

3. **Local Mermaid CLI** (optional):
   ```bash
   # Install Mermaid CLI
   npm install -g @mermaid-js/mermaid-cli
   
   # Generate SVG diagram
   mmdc -i class-diagram.md -o class-diagram.svg
   
   # Generate PNG diagram  
   mmdc -i class-diagram.md -o class-diagram.png
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
- **Polymorphic selection interfaces** via `selection_container` abstract base
- **Configurable game rules** through `table` coordination and player management
- **Template Method patterns** for consistent container behavior
- **Strategy Pattern** implementation for flexible discard mechanisms
- **Clean separation** of card mechanics from game-specific logic

### Automated Documentation

This UML diagram is **automatically maintained** through GitHub Actions:
- **Triggers** on changes to `.h` and `.cpp` files
- **Updates** class count and modification timestamps  
- **Maintains accuracy** without manual intervention
- **Scales** with project growth automatically

For detailed implementation specifications, see the main project documentation in `/README.md` and `/CLAUDE.md`.