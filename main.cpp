// main.cpp — Phase 3 debug scene: animates cards dealing from the deck to
// all player hand slots. Press SPACE to restart the deal. ESC to exit.

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "card.h"
#include "deck.h"
#include "card_sprite.h"
#include "layout.h"
#include "animator.h"

static const int   N_PLAYERS   = 2;
static const float DEAL_DELAY  = 0.12f;
static const float SLIDE_TIME  = 0.35f;

// ── Deal sequence ─────────────────────────────────────────────────────────────
// Queues one slide animation per hand slot in round-robin deal order.
// A dummy wait animation on a scratch sprite spaces cards apart in time.
static void queue_deal(
    animator&                 anm,
    std::vector<card_sprite>& vHandCards,
    const layout&             lay,
    card_sprite&              sprScratch)
{
    anm.flush();

    const sf::Vector2f vDeckPos = lay.get_deck_position();
    const int          iPlayers = lay.get_player_count();
    const int          iEach    = (int)vHandCards.size() / iPlayers;

    // Round-robin destination order: P0s0, P1s0, P0s1, P1s1 …
    std::vector<sf::Vector2f> vDests;
    for (int slot = 0; slot < iEach; ++slot)
        for (int p = 0; p < iPlayers; ++p)
            vDests.push_back(lay.get_hand_positions(p)[slot]);

    std::vector<card_sprite*> vOrdered;
    for (int slot = 0; slot < iEach; ++slot)
        for (int p = 0; p < iPlayers; ++p)
            vOrdered.push_back(&vHandCards[p * iEach + slot]);

    for (auto& spr : vHandCards)
        spr.set_position(vDeckPos);

    const int iTotal = (int)vDests.size();

    struct deal_state
    {
        int                       iNext;
        std::vector<card_sprite*> vPtrs;
        std::vector<sf::Vector2f> vDests;
        sf::Vector2f              vDeckPos;
        animator*                 pAnm;
        card_sprite*              pScratch;
    };

    auto pSt = std::make_shared<deal_state>();
    pSt->iNext    = 0;
    pSt->vPtrs    = vOrdered;
    pSt->vDests   = vDests;
    pSt->vDeckPos = vDeckPos;
    pSt->pAnm     = &anm;
    pSt->pScratch = &sprScratch;

    // Recursive chain: each card queues a delay, then a slide, then the next card.
    // fnNext is stored in the shared state so lambdas can reference it safely.
    struct chain
    {
        std::function<void()> fn;
    };

    auto pChain = std::make_shared<chain>();
    pChain->fn = [pSt, pChain, iTotal]()
    {
        if (pSt->iNext >= iTotal) return;
        int i = pSt->iNext++;
        pSt->pAnm->add(
            pSt->pScratch, pSt->vDeckPos, pSt->vDeckPos, DEAL_DELAY,
            [pSt, pChain, i]()
            {
                pSt->pAnm->add(
                    pSt->vPtrs[i], pSt->vDeckPos, pSt->vDests[i], SLIDE_TIME,
                    pChain->fn);
            });
    };

    pChain->fn();
}

// ── Main ──────────────────────────────────────────────────────────────────────
int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Roubamonte - Phase 3 Animation Test");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/consola.ttf"))
        return -1;

    layout lay;
    lay.compute(N_PLAYERS, window.getSize());

    const sf::Vector2f vDeckPos = lay.get_deck_position();

    // Deck pile sprite
    card_sprite sprDeck;
    sprDeck.set_card(card(ACE, SPADES), font);
    sprDeck.set_face_up(false);
    sprDeck.set_position(vDeckPos);

    // Tray: 8 static face-up cards
    deck dckSeed;
    std::vector<card_sprite> vTrayCards;
    for (const sf::Vector2f& vPos : lay.get_tray_positions(8))
    {
        card_sprite spr;
        spr.set_card(dckSeed.pop(), font);
        spr.set_face_up(true);
        spr.set_position(vPos);
        vTrayCards.push_back(spr);
    }

    // Hand cards — start at deck, animated to slots
    const int iEach = 4;
    std::vector<card_sprite> vHandCards(N_PLAYERS * iEach);
    for (int p = 0; p < N_PLAYERS; ++p)
        for (int s = 0; s < iEach; ++s)
        {
            auto& spr = vHandCards[p * iEach + s];
            spr.set_card(dckSeed.pop(), font);
            spr.set_face_up(false);
            spr.set_position(vDeckPos);
        }

    // Stack placeholder boxes
    std::vector<sf::RectangleShape> vStackBoxes;
    for (int p = 0; p < N_PLAYERS; ++p)
    {
        sf::RectangleShape rct(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
        rct.setPosition(lay.get_stack_position(p));
        rct.setFillColor(sf::Color(0, 0, 0, 70));
        rct.setOutlineColor(sf::Color(180, 150, 60, 200));
        rct.setOutlineThickness(1.5f);
        vStackBoxes.push_back(rct);
    }

    // Animator + off-screen scratch sprite for inter-card delays
    animator    anm;
    card_sprite sprScratch;
    sprScratch.set_card(card(ACE, SPADES), font);
    sprScratch.set_position(sf::Vector2f(-200.0f, -200.0f));

    queue_deal(anm, vHandCards, lay, sprScratch);

    sf::Text txtHint;
    txtHint.setFont(font);
    txtHint.setCharacterSize(13);
    txtHint.setFillColor(sf::Color(180, 180, 180));
    txtHint.setString("SPACE = restart deal  |  ESC = exit");
    txtHint.setPosition(5.0f, (float)window.getSize().y - 22.0f);

    sf::Clock clkFrame;

    while (window.isOpen())
    {
        const float fDelta = clkFrame.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space && !anm.isAnimating())
                    queue_deal(anm, vHandCards, lay, sprScratch);
            }
        }

        anm.update(fDelta);

        window.clear(sf::Color(34, 100, 34));
        for (auto& spr : vTrayCards)  spr.draw(window);
        sprDeck.draw(window);
        for (auto& rct : vStackBoxes) window.draw(rct);
        for (auto& spr : vHandCards)  spr.draw(window);
        window.draw(txtHint);
        window.display();
    }

    return 0;
}

