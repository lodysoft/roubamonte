# Roubamonte Class Diagram

```mermaid
classDiagram
    %% Core Card Entity
    class card {
        -int iRank
        -int iSuit
        +card(int iRank, int iSt)
        +card(const card& crdOther)
        +operator=(const card& crdOther) card&
        +operator<(const card& crdOther) const bool
        +operator==(const card& other) const bool
        +rank() const int
        +suit() const int
    }

    %% Stack Container
    class stack {
        #std::stack~card~ crdStack
        +pop() card
        +push(const card crdCard) void
        +top() const card&
        +count() const int
        +isEmpty() const bool
    }

    %% Deck inherits from Stack
    class deck {
        +deck()
    }

    %% Abstract Selection Container
    class selection_container {
        <<abstract>>
        #const int iInitialCards
        #int iSelected
        #std::map~int, card~ mapCards
        #selection_container(deck& dckDeck, const int iInitial)
        #getInitialCards() const int
        +isEmpty() const bool
        +count() const int
        +select(const int iIndex) void
        +operator[](const int iIndex) const card&
        +refill(deck& dckDeck) void
    }

    %% Hand inherits from Selection Container
    class hand {
        +hand(deck& dckDeck)
        +discard() card
        +discard(tray& trayTarget) void
    }

    %% Tray inherits from Selection Container
    class tray {
        +tray(deck& dckDeck)
        +receive_discard(const card& crdDiscarded) void
    }

    %% Player class
    class player {
        #stack stkStack
        #hand hndHand
        #isMatch(const card& crdTarget, const card& crdSource) const bool
        +player(deck& dckDeck)
        +getStack() stack&
        +getHand() hand&
        +steal(player& plyOther) void
    }

    %% Table orchestrates the game
    class table {
        #deck dckPile
        #tray tryTray
        #std::vector~player~ plyPlayers
        +table(int iPlayers = 2)
        +getTray() tray&
        +getPlayers() std::vector~player~&
        +getDeck() const deck&
    }

    %% Enumerations (anonymous enums from card.h)
    class SuitEnum {
        <<enumeration>>
        RED = -1
        BLACK = 0
        SPADES = 1
        HEARTS = 2
        DIAMONDS = 3
        CLUBS = 4
    }

    class RankEnum {
        <<enumeration>>
        JOKER = 0
        ACE = 1
        JACK = 11
        QUEEN = 12
        KING = 13
    }

    %% Constants (from various headers)
    class Constants {
        <<utility>>
        HAND_INITIAL_CARDS = 4
        TRAY_INITIAL_CARDS = 8
        TABLE_INITIAL_CARDS = 8
    }

    %% Inheritance relationships
    deck --|> stack : inherits
    hand --|> selection_container : inherits
    tray --|> selection_container : inherits

    %% Composition relationships
    stack *-- card : contains
    selection_container *-- card : contains
    player *-- stack : owns
    player *-- hand : owns
    table *-- deck : owns
    table *-- tray : owns
    table *-- player : contains

    %% Dependencies
    deck ..> card : uses
    hand ..> deck : uses
    hand ..> tray : uses
    tray ..> deck : uses
    player ..> deck : uses
    selection_container ..> deck : uses

    %% Associations with enums and constants
    card --> SuitEnum : uses
    card --> RankEnum : uses
    hand --> Constants : uses
    tray --> Constants : uses
    table --> Constants : uses

    %% Notes about key design patterns
    note for selection_container "Abstract base class implementing Template Method pattern"
    
    note for hand "Strategy Pattern: dual discard modes\n- discard() returns card\n- discard(tray&) discards to tray"
    
    note for deck "Factory Pattern: generates complete 54-card set\nwith Fisher-Yates shuffling"
    
    note for player "Encapsulates game participant with stealing mechanics\nbased on rank matching"
    
    note for table "Game state orchestrator managing players,\ndeck distribution and tray coordination"
```

## Design Patterns Implemented

- **Template Method Pattern** - `selection_container` abstract base with concrete implementations
- **Strategy Pattern** - Dual discard modes in `hand` class  
- **Factory Pattern** - `deck` auto-generates complete 54-card sets
- **RAII Pattern** - Exception-safe resource management throughout

## Architecture Notes

- **Core Entity**: `card` - Immutable game entity with rank/suit properties
- **Container Hierarchy**: LIFO stack, factory deck, polymorphic selection containers
- **Game Logic**: Player coordination and multi-player table management
- **Extensibility**: Framework supports diverse card-based games through inheritance patterns