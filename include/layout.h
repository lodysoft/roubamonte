// layout.h

// Computes screen positions for all game elements based on player count and window size.
// Positions are top-left corners of card-sized slots, matching card_sprite expectations.

#ifndef LAYOUT_H
#define LAYOUT_H

#include <SFML/Graphics.hpp>
#include <vector>

class layout
{
public:
    layout();

    // Recompute all positions for the given player count and window size.
    // Must be called before any get_* method.
    void compute(int iPlayers, sf::Vector2u vWindowSize);

    // Returns HAND_INITIAL_CARDS top-left positions for the i-th player's hand.
    // Spread is horizontal for top/bottom players, vertical for left/right players.
    std::vector<sf::Vector2f> get_hand_positions(int iPlayer) const;

    // Returns iCount top-left positions for tray cards, centred on the table.
    // Gap shrinks (and becomes negative overlap) if many cards are present.
    std::vector<sf::Vector2f> get_tray_positions(int iCount) const;

    // Top-left position of the deck pile indicator.
    sf::Vector2f get_deck_position() const;

    // Top-left position of the stack pile indicator for the i-th player.
    sf::Vector2f get_stack_position(int iPlayer) const;

    int get_player_count() const;

private:
    struct player_anchor
    {
        sf::Vector2f vHandCenter;   // Centre of the hand spread area.
        sf::Vector2f vStackPos;     // Top-left of the stack indicator.
        bool         bVertical;     // Cards spread vertically instead of horizontally.
    };

    int                        iPlayerCount;
    sf::Vector2u               vWindowSize;
    std::vector<player_anchor> vAnchors;
    sf::Vector2f               vDeckPos;
    sf::Vector2f               vTrayCenter;

    void compute_anchors(float fW, float fH);
};

#endif
