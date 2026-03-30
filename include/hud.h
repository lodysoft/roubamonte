// hud.h

// Heads-up display: draws turn indicator, player labels, stack/deck counts,
// and a status message on top of the game scene.
// Call init() once after loading a font, then set_layout() whenever the window
// is resized.  Update the data setters as game state changes, then call draw()
// every frame.

#ifndef HUD_H
#define HUD_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "layout.h"

class hud
{
public:
    hud();

    // Must be called before draw().  Rebuilds all text objects.
    void init(const sf::Font& fntFont, int iPlayers, sf::Vector2u vWindowSize);

    // Grab stack- and deck-label anchor positions from an already-computed layout.
    // Call this again whenever layout::compute() is called.
    void set_layout(const layout& layTable);

    // ── Setters (call when game state changes) ────────────────────────────────

    // Set 0-based index of the player whose turn it is.
    void set_turn(int iPlayer);

    // Replace the status message shown at the bottom of the screen.
    // Pass an empty string to hide it.
    void set_status(const std::string& strMsg);

    // Update the stack card count badge for one player (0-based index).
    void set_stack_count(int iPlayer, int iCount);

    // Update the deck remaining count badge near the deck pile.
    void set_deck_count(int iCount);

    // ── Rendering ────────────────────────────────────────────────────────────

    void draw(sf::RenderWindow& wndTarget) const;

private:
    int          iPlayerCount;
    sf::Vector2u vWinSize;

    sf::Text              txtTurn;              // "Player X's Turn"  — top-center.
    sf::Text              txtStatus;            // Status message     — bottom-center.
    sf::Text              txtDeckCount;         // Deck count badge   — near deck pile.
    std::vector<sf::Text> vTxtStackCounts;      // Per-player stack count badges.
    std::vector<sf::Text> vTxtPlayerLabels;     // "Player 1" … "Player N" labels.

    // Re-centre txt so its visual centre is at (fCX, fCY).
    static void center_at(sf::Text& txt, float fCX, float fCY);

    // Apply the standard badge style (small, white, dark outline).
    static void apply_badge_style(sf::Text& txt, const sf::Font& fntFont);
};

#endif
