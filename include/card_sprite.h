// card_sprite.h

// Renders a single card using SFML primitives and text.
// Supports face-up, face-down, selected, and hover states.
// Usage order: set_card() must be called before set_position().

#ifndef CARD_SPRITE_H
#define CARD_SPRITE_H

#include <SFML/Graphics.hpp>
#include <string>

#include "card.h"

const float CARD_WIDTH  = 80.0f;
const float CARD_HEIGHT = 120.0f;

class card_sprite
{
public:
    card_sprite();

    void set_card(const card& crdCard, const sf::Font& fntFont);    // Configure the card visual. Call before set_position.
    void set_position(sf::Vector2f vPos);                           // Place the card on screen.
    void set_face_up(bool bUp);
    void set_selected(bool bSel);
    void set_hover(bool bHov);

    sf::Vector2f get_position() const;
    bool contains(sf::Vector2f vPoint) const;                       // Hit test for mouse clicks.
    bool isFaceUp() const;
    bool isSelected() const;

    void draw(sf::RenderWindow& wndTarget) const;

private:
    sf::RectangleShape rctBody;         // Card outline and fill.
    sf::RectangleShape rctInner;        // Gold inner border shown on face-down back.
    sf::Text txtRankTop;                // Top-left rank label.
    sf::Text txtSuitTop;                // Top-left suit glyph.
    sf::Text txtRankBtm;                // Bottom-right rank label (rotated 180°).
    sf::Text txtSuitBtm;                // Bottom-right suit glyph (rotated 180°).
    sf::Text txtCenter;                 // Large central suit symbol.
    sf::Text txtMonogram;               // "RM" shown on face-down back.

    bool bFaceUp;
    bool bSelected;
    bool bHover;

    sf::Color clrSuit;

    void update_style();                // Recalculate fill/outline colours for current state.
    void update_layout();               // Recalculate text positions from rctBody position.

    static std::string rank_to_string(int iRank);
    static std::string suit_to_string(int iSuit);
    static sf::Color   suit_to_color(int iSuit);
};

#endif
