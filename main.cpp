// main.cpp — Phase 2 debug scene: shows adaptive layout for N players.
// Press 2 / 3 / 4 to switch player count. ESC to exit.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "card.h"
#include "deck.h"
#include "card_sprite.h"
#include "layout.h"

// ── Build all card sprites for the current layout ─────────────────────────────
static void build_scene(
    const layout&                   lay,
    const sf::Font&                 fntFont,
    std::vector<card_sprite>&       vHandCards,
    std::vector<card_sprite>&       vTrayCards,
    card_sprite&                    sprDeck,
    std::vector<sf::RectangleShape>& vStackBoxes,
    std::vector<sf::Text>&          vPlayerLabels,
    std::vector<sf::Text>&          vStackLabels,
    sf::Text&                       txtDeckLabel)
{
    vHandCards.clear();
    vTrayCards.clear();
    vStackBoxes.clear();
    vPlayerLabels.clear();
    vStackLabels.clear();

    deck dckDeck;

    // ── Tray: 8 face-up cards ─────────────────────────────────────────────────
    const int iTrayCount = 8;
    std::vector<sf::Vector2f> vTrayPos = lay.get_tray_positions(iTrayCount);
    for (int i = 0; i < iTrayCount; ++i)
    {
        card_sprite spr;
        spr.set_card(dckDeck.pop(), fntFont);
        spr.set_face_up(true);
        spr.set_position(vTrayPos[i]);
        vTrayCards.push_back(spr);
    }

    // ── Deck pile ─────────────────────────────────────────────────────────────
    sprDeck.set_card(card(ACE, SPADES), fntFont);
    sprDeck.set_face_up(false);
    sprDeck.set_position(lay.get_deck_position());

    txtDeckLabel.setString("Deck");
    txtDeckLabel.setPosition(sf::Vector2f(
        lay.get_deck_position().x,
        lay.get_deck_position().y - 18.0f
    ));

    // ── Per-player: hand cards + stack indicator + labels ─────────────────────
    for (int p = 0; p < lay.get_player_count(); ++p)
    {
        std::vector<sf::Vector2f> vHandPos = lay.get_hand_positions(p);

        // Face-down hand cards
        for (const sf::Vector2f& vPos : vHandPos)
        {
            card_sprite spr;
            spr.set_card(dckDeck.pop(), fntFont);
            spr.set_face_up(false);
            spr.set_position(vPos);
            vHandCards.push_back(spr);
        }

        // Player label — above hand for bottom players, below for top players
        sf::Text lblPlayer;
        lblPlayer.setFont(fntFont);
        lblPlayer.setString("Player " + std::to_string(p + 1));
        lblPlayer.setCharacterSize(13);
        lblPlayer.setFillColor(sf::Color(220, 220, 100));
        if (!vHandPos.empty())
        {
            float fLabelY = (vHandPos[0].y < 80.0f)
                ? vHandPos[0].y + CARD_HEIGHT + 4.0f
                : vHandPos[0].y - 18.0f;
            lblPlayer.setPosition(sf::Vector2f(vHandPos[0].x, fLabelY));
        }
        vPlayerLabels.push_back(lblPlayer);

        // Stack indicator: semi-transparent rectangle with gold border
        sf::RectangleShape rctStack(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
        rctStack.setPosition(lay.get_stack_position(p));
        rctStack.setFillColor(sf::Color(0, 0, 0, 70));
        rctStack.setOutlineColor(sf::Color(180, 150, 60, 200));
        rctStack.setOutlineThickness(1.5f);
        vStackBoxes.push_back(rctStack);

        sf::Text lblStack;
        lblStack.setFont(fntFont);
        lblStack.setString("Stack P" + std::to_string(p + 1));
        lblStack.setCharacterSize(11);
        lblStack.setFillColor(sf::Color(180, 150, 60));
        lblStack.setPosition(sf::Vector2f(
            lay.get_stack_position(p).x,
            lay.get_stack_position(p).y + CARD_HEIGHT / 2.0f - 7.0f
        ));
        vStackLabels.push_back(lblStack);
    }
}

// ── Main ──────────────────────────────────────────────────────────────────────
int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Roubamonte - Phase 2 Layout Test");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/consola.ttf"))
    {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Labels that persist across rebuilds
    sf::Text txtHint;
    txtHint.setFont(font);
    txtHint.setCharacterSize(13);
    txtHint.setFillColor(sf::Color(180, 180, 180));

    sf::Text txtTrayLabel;
    txtTrayLabel.setFont(font);
    txtTrayLabel.setString("Tray");
    txtTrayLabel.setCharacterSize(13);
    txtTrayLabel.setFillColor(sf::Color(180, 220, 180));

    sf::Text txtDeckLabel;
    txtDeckLabel.setFont(font);
    txtDeckLabel.setCharacterSize(13);
    txtDeckLabel.setFillColor(sf::Color(180, 220, 180));

    // Scene state
    int                         iPlayerCount = 2;
    layout                      lay;
    std::vector<card_sprite>    vHandCards;
    std::vector<card_sprite>    vTrayCards;
    card_sprite                 sprDeck;
    std::vector<sf::RectangleShape> vStackBoxes;
    std::vector<sf::Text>       vPlayerLabels;
    std::vector<sf::Text>       vStackLabels;

    auto rebuild = [&]()
    {
        lay.compute(iPlayerCount, window.getSize());
        build_scene(lay, font, vHandCards, vTrayCards, sprDeck,
                    vStackBoxes, vPlayerLabels, vStackLabels, txtDeckLabel);

        // Position tray label above the first tray card
        std::vector<sf::Vector2f> vTrayPos = lay.get_tray_positions(8);
        if (!vTrayPos.empty())
            txtTrayLabel.setPosition(sf::Vector2f(vTrayPos[0].x, vTrayPos[0].y - 18.0f));

        txtHint.setString(
            "Press 2 / 3 / 4 to switch player count  |  ESC to exit  |  Players: "
            + std::to_string(iPlayerCount));
        txtHint.setPosition(5.0f, (float)window.getSize().y - 22.0f);
    };

    rebuild();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::Num2)   { iPlayerCount = 2; rebuild(); }
                if (event.key.code == sf::Keyboard::Num3)   { iPlayerCount = 3; rebuild(); }
                if (event.key.code == sf::Keyboard::Num4)   { iPlayerCount = 4; rebuild(); }
            }
        }

        window.clear(sf::Color(34, 100, 34));

        for (auto& spr : vTrayCards)    spr.draw(window);
        sprDeck.draw(window);
        for (auto& rct : vStackBoxes)   window.draw(rct);
        for (auto& spr : vHandCards)    spr.draw(window);
        for (auto& lbl : vPlayerLabels) window.draw(lbl);
        for (auto& lbl : vStackLabels)  window.draw(lbl);
        window.draw(txtTrayLabel);
        window.draw(txtDeckLabel);
        window.draw(txtHint);

        window.display();
    }

    return 0;
}
