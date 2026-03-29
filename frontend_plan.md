# Roubamonte — Frontend Implementation Plan (SFML 2.6)

## Overview

Build a classic green-felt card game UI on top of the existing SFML 2.6 / C++20 backend. Cards are rendered programmatically (shapes + text), the layout adapts to N players (2–4+), and basic slide animations smooth out card movements. The frontend layer is kept fully separate from the existing game logic classes — **the plan is purely additive**.

---

## Architecture

Introduce five new classes, all in `include/` following project conventions (`.h` + `.cpp` pairs):

| New class | Purpose |
|-----------|---------|
| `card_sprite` | Draws a single card — rectangle + suit glyph + rank text. Face-up/down, hover, selected states. |
| `layout` | Computes positions for N-player arrangement (hands around table edges, tray in center, deck, stacks). |
| `animator` | Tweens card sprites from A→B over time (linear lerp, queue-based). |
| `hud` | Turn indicator, player labels, stack/deck counts, status messages. |
| `scene` | Top-level orchestrator — owns `table` + all rendering objects, drives the game state machine and input. |

Zero changes to existing game logic classes. The frontend is purely additive.

---

## Phases

### Phase 1 — Card Rendering (`card_sprite`)

**Goal**: A reusable drawable card that takes a `const card&` and renders it at a given position/size.

1. Create `include/card_sprite.h` and `include/card_sprite.cpp`
   - Class `card_sprite` (single word per style guide)
   - Data: `sf::RectangleShape rctBody`, `sf::Text txtRank`, `sf::Text txtSuit`, `bool bFaceUp`, `bool bSelected`
   - Method `draw(sf::RenderWindow&)` — renders card face or back
   - Method `set_card(const card&)` — maps `iRank`/`iSuit` to display strings and colors
   - Rank mapping: `JOKER→"★"`, `ACE→"A"`, `2–10→digit`, `JACK→"J"`, `QUEEN→"Q"`, `KING→"K"`
   - Suit mapping with Unicode glyphs:
     - `SPADES→"♠"` (black), `CLUBS→"♣"` (black)
     - `HEARTS→"♥"` (red), `DIAMONDS→"♦"` (red)
     - `RED→"★"` (red), `BLACK→"★"` (black)
   - Card size: ~80×120 px default, configurable
   - Face-down: dark red/maroon back with thin gold inner border and "RM" monogram
   - Selected state: gold border outline or slight vertical lift offset
   - Hover state: subtle brightness increase via color tint

### Phase 2 — Layout Engine (`layout`)

**Goal**: Dynamically position all game elements for 2–4+ players on an adaptable window.

2. Create `include/layout.h` and `include/layout.cpp`
   - Class `layout`
   - Input: player count, window dimensions
   - Output: computed `sf::Vector2f` positions for all game elements:
     - **Deck pile**: center-left area, single face-down card sprite + count badge
     - **Tray**: center of table, horizontal row with slight overlap (scrollable if >8 cards)
     - **Player hands**: arranged around table edges
       - 2 players: bottom (active) + top (opponent)
       - 3 players: bottom + top-left + top-right
       - 4 players: bottom + top + left + right
       - N > 4: evenly spaced around an ellipse
     - **Player stacks**: small pile icon near each hand with card count text
   - Methods:
     - `compute(int iPlayers, sf::Vector2u vWindowSize)` — recalculates all positions
     - `get_hand_positions(int iPlayer)` → `std::vector<sf::Vector2f>`
     - `get_tray_positions(int iCount)` → `std::vector<sf::Vector2f>`
     - `get_deck_position()` → `sf::Vector2f`
     - `get_stack_position(int iPlayer)` → `sf::Vector2f`

### Phase 3 — Animation System (`animator`)

**Goal**: Smooth card movements (deal, discard, steal) via simple linear interpolation.

3. Create `include/animator.h` and `include/animator.cpp`
   - Class `animator`
   - Stores a queue of `animation` structs:
     `{ card_sprite* pSprite, sf::Vector2f vFrom, sf::Vector2f vTo, float fDuration, float fElapsed }`
   - Methods:
     - `add(card_sprite*, sf::Vector2f vFrom, sf::Vector2f vTo, float fSeconds)`
     - `update(float fDeltaTime)` — advances all active animations, removes completed ones
     - `isAnimating()` → `bool` — returns true if queue is non-empty (blocks input during animations)
   - Easing: linear lerp for "basic" tier; upgrade to ease-in-out later if desired

### Phase 4 — HUD (`hud`)

**Goal**: Inform players of game state without cluttering the card area.

4. Create `include/hud.h` and `include/hud.cpp`
   - Class `hud`
   - Draws (using existing `consola.ttf` font):
     - Current player indicator (e.g., "Player 1's turn")
     - Stack card counts per player (number badge near stack icon)
     - Deck remaining count
     - Status messages (e.g., "Select a card from your hand", "Player 2 stole Player 1's stack!")
   - Methods:
     - `draw(sf::RenderWindow&)`
     - `set_status(const std::string& strMsg)`
     - `set_turn(int iPlayer)`

### Phase 5 — Scene Orchestration (`scene`) *(depends on 1–4)*

**Goal**: Wire everything together — game state, rendering, and input.

5. Create `include/scene.h` and `include/scene.cpp`
   - Class `scene`
   - Owns: `table tblGame`, `layout layTable`, `animator anmCards`, `hud hudDisplay`, `std::vector<card_sprite> vCardSprites`
   - **Game state machine** (enum):
     ```
     WAITING_HAND_SELECT → WAITING_TRAY_SELECT → ANIMATING → STEAL_RESOLUTION → ROUND_END → GAME_OVER
     ```
   - Input handling via mouse click hit-testing against card sprite bounds:
     - `WAITING_HAND_SELECT`: clicking a card in the current player's hand calls `select()`, highlights it, transitions to `WAITING_TRAY_SELECT`
     - `WAITING_TRAY_SELECT`: clicking a tray card checks for rank match (via `isMatch()` logic); if match → trigger steal animation + `player::steal()`; if no match → discard to tray
   - Methods:
     - `handle_event(sf::Event&)`
     - `update(float fDelta)` — advances animations, checks state transitions
     - `draw(sf::RenderWindow&)` — background (dark green `sf::Color(34, 100, 34)`), all card sprites via layout, HUD

6. Rewrite `main.cpp` to use `scene`:
   - Instantiate `scene` with player count (from start screen or command-line)
   - Game loop: `poll events → handle_event() → update(delta) → draw(window)`
   - Delta time via `sf::Clock`

### Phase 6 — Build System Update *(parallel with Phase 1)*

7. Update `CMakeLists.txt`:
   - Add all `include/*.cpp` files to `add_executable()` — both the 8 existing game logic files (currently not compiled into the executable) and the 5 new frontend files
   - Add `include/` to `include_directories()`

### Phase 7 — Turn Flow & Polish *(depends on 5, 6)*

8. Turn cycling in `scene`:
   - After a player's action resolves, advance to the next player
   - Current player's hand face-up, all others face-down
   - Call `hand::refill(deck&)` for each player when hands are empty and deck has cards

9. Steal visual feedback:
   - Animate opponent's stack cards flying to attacker's stack position
   - Flash status message "Player X stole Player Y's stack!"

10. End-of-game detection:
    - When deck is empty and all hands are empty, tally stack counts
    - Display winner overlay with final totals

---

## Files

### Modify

| File | Change |
|------|--------|
| `main.cpp` | Rewrite to instantiate `scene` and run game loop |
| `CMakeLists.txt` | Add `include/*.cpp` to `add_executable()`, add `include_directories(include/)` |

### Reference (read-only — no changes)

| File | Used for |
|------|---------|
| `include/card.h` | Rank/suit enums for rendering |
| `include/table.h` | `scene` owns a `table` instance |
| `include/player.h` | `steal()`, `getHand()`, `getStack()` |
| `include/hand.h` | `select()`, `discard()`, `refill()` |
| `include/tray.h` | `receive_discard()` |
| `include/selection_container.h` | `operator[]`, `count()`, `select()` |
| `STYLE_GUIDE.md` | Hungarian notation, lowercase class names, brace conventions |

### Create

```
include/card_sprite.h
include/card_sprite.cpp
include/layout.h
include/layout.cpp
include/animator.h
include/animator.cpp
include/hud.h
include/hud.cpp
include/scene.h
include/scene.cpp
```

---

## Verification Checklist

1. **Phase 1**: Render all 54 cards in a debug grid — verify every rank/suit combination, face-down, selected, and hover states
2. **Phase 2**: Render placeholder rectangles for 2, 3, and 4 players — verify adaptive positioning and no overlaps
3. **Phase 3**: Animate a card from deck position to a hand slot — verify smooth movement and input blocking
4. **Phase 4**: Display HUD with mock data — verify text readability on green background
5. **Phase 5**: Play a full 2-player game through the UI — verify turn cycling, discarding, stealing, and end-game detection
6. **Phase 7**: Test with 3 and 4 players — verify layout and turn cycling scale correctly
7. Run existing `test_suite/` QA tests to confirm all game logic classes remain unchanged and fully functional

---

## Decisions

- **Additive only** — no modifications to the 8 existing game logic classes
- **Programmatic card rendering** — SFML shapes + `consola.ttf`; no image assets required
- **SFML 2.6 only** — no additional library dependencies
- **Style guide compliant** — Hungarian notation, lowercase single-word class names, brace conventions per `STYLE_GUIDE.md`
- **Out of scope**: networking/online play, sound effects, main menu/settings screen, save/load state (all deferrable)

---

## Further Considerations

1. **Player count selection**: Add a simple start screen where number keys (2–4) select the player count, or accept a command-line argument. *Recommendation: simple SFML text-based start screen.*

2. **Window resolution**: 800×600 is tight for 4+ players with 4-card hands + 8+ tray cards. *Recommendation: bump to 1024×768 as the default and handle `sf::Event::Resized` to trigger `layout::compute()` for reflow.*

3. **Card back design**: Solid color vs. pattern. *Recommendation: dark red/maroon rectangle with a thin gold inner border and small "RM" monogram text — cheap to implement, looks classic.*
