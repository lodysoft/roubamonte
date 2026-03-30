// hud.cpp

#include <string>

#include "hud.h"
#include "card_sprite.h"    // CARD_WIDTH, CARD_HEIGHT

static const unsigned int FONT_SIZE_TURN   = 22u;
static const unsigned int FONT_SIZE_STATUS = 17u;
static const unsigned int FONT_SIZE_BADGE  = 14u;
static const unsigned int FONT_SIZE_LABEL  = 14u;

static const sf::Color CLR_GOLD    = sf::Color(255, 215,   0);
static const sf::Color CLR_WHITE   = sf::Color(255, 255, 255);
static const sf::Color CLR_SHADOW  = sf::Color(  0,   0,   0, 180);
static const sf::Color CLR_STATUS  = sf::Color(220, 220, 220);
static const sf::Color CLR_LABEL   = sf::Color(200, 230, 200);
static const float     BADGE_OUT   = 1.5f;     // Outline thickness for badges.
static const float     LABEL_OUT   = 1.0f;

// ── Helpers ───────────────────────────────────────────────────────────────────

void hud::center_at(sf::Text& txt, float fCX, float fCY)
{
    sf::FloatRect rcBounds = txt.getLocalBounds();
    txt.setOrigin(rcBounds.left + rcBounds.width  / 2.0f,
                  rcBounds.top  + rcBounds.height / 2.0f);
    txt.setPosition(fCX, fCY);
}

void hud::apply_badge_style(sf::Text& txt, const sf::Font& fntFont)
{
    txt.setFont(fntFont);
    txt.setCharacterSize(FONT_SIZE_BADGE);
    txt.setFillColor(CLR_WHITE);
    txt.setOutlineColor(CLR_SHADOW);
    txt.setOutlineThickness(BADGE_OUT);
}

// ── Constructor ───────────────────────────────────────────────────────────────

hud::hud() : iPlayerCount(0) {}

// ── Public interface ──────────────────────────────────────────────────────────

void hud::init(const sf::Font& fntFont, int iPlayers, sf::Vector2u vWindowSize)
{
    iPlayerCount = iPlayers;
    vWinSize     = vWindowSize;

    float fW = (float)vWindowSize.x;
    float fH = (float)vWindowSize.y;

    // Turn indicator — top-center.
    txtTurn.setFont(fntFont);
    txtTurn.setCharacterSize(FONT_SIZE_TURN);
    txtTurn.setFillColor(CLR_GOLD);
    txtTurn.setOutlineColor(CLR_SHADOW);
    txtTurn.setOutlineThickness(2.0f);
    txtTurn.setString("Player 1's Turn");
    center_at(txtTurn, fW / 2.0f, 14.0f);

    // Status message — bottom-center.
    txtStatus.setFont(fntFont);
    txtStatus.setCharacterSize(FONT_SIZE_STATUS);
    txtStatus.setFillColor(CLR_STATUS);
    txtStatus.setOutlineColor(CLR_SHADOW);
    txtStatus.setOutlineThickness(1.5f);
    txtStatus.setString("");
    center_at(txtStatus, fW / 2.0f, fH - 14.0f);

    // Deck count badge — positioned by set_layout(), default off-screen.
    apply_badge_style(txtDeckCount, fntFont);
    txtDeckCount.setString("52");
    txtDeckCount.setPosition(-200.0f, -200.0f);

    // Per-player stack count badges and labels.
    vTxtStackCounts.clear();
    vTxtPlayerLabels.clear();
    vTxtStackCounts.resize(iPlayers);
    vTxtPlayerLabels.resize(iPlayers);

    for (int i = 0; i < iPlayers; ++i)
    {
        apply_badge_style(vTxtStackCounts[i], fntFont);
        vTxtStackCounts[i].setString("0");
        vTxtStackCounts[i].setPosition(-200.0f, -200.0f);

        vTxtPlayerLabels[i].setFont(fntFont);
        vTxtPlayerLabels[i].setCharacterSize(FONT_SIZE_LABEL);
        vTxtPlayerLabels[i].setFillColor(CLR_LABEL);
        vTxtPlayerLabels[i].setOutlineColor(CLR_SHADOW);
        vTxtPlayerLabels[i].setOutlineThickness(LABEL_OUT);
        vTxtPlayerLabels[i].setString("Player " + std::to_string(i + 1));
        vTxtPlayerLabels[i].setPosition(-200.0f, -200.0f);
    }
}

void hud::set_layout(const layout& layTable)
{
    int iPlayers = layTable.get_player_count();
    if (iPlayers != iPlayerCount) return;   // Guard: must match init() player count.

    sf::Vector2f vDeck = layTable.get_deck_position();
    // Place deck count badge centred below the deck pile.
    center_at(txtDeckCount,
              vDeck.x + CARD_WIDTH  / 2.0f,
              vDeck.y + CARD_HEIGHT + 10.0f);

    for (int i = 0; i < iPlayers; ++i)
    {
        sf::Vector2f vStack = layTable.get_stack_position(i);

        // Stack count badge centred below the stack indicator.
        center_at(vTxtStackCounts[i],
                  vStack.x + CARD_WIDTH  / 2.0f,
                  vStack.y + CARD_HEIGHT + 10.0f);

        // Player label centred above the stack indicator.
        center_at(vTxtPlayerLabels[i],
                  vStack.x + CARD_WIDTH  / 2.0f,
                  vStack.y - 10.0f);
    }
}

void hud::set_turn(int iPlayer)
{
    if (iPlayer < 0 || iPlayer >= iPlayerCount) return;
    std::string strLabel = "Player " + std::to_string(iPlayer + 1) + "'s Turn";
    txtTurn.setString(strLabel);
    center_at(txtTurn, (float)vWinSize.x / 2.0f, 14.0f);
}

void hud::set_status(const std::string& strMsg)
{
    txtStatus.setString(strMsg);
    center_at(txtStatus, (float)vWinSize.x / 2.0f, (float)vWinSize.y - 14.0f);
}

void hud::set_stack_count(int iPlayer, int iCount)
{
    if (iPlayer < 0 || iPlayer >= iPlayerCount) return;
    vTxtStackCounts[iPlayer].setString(std::to_string(iCount));
}

void hud::set_deck_count(int iCount)
{
    txtDeckCount.setString(std::to_string(iCount));
}

void hud::draw(sf::RenderWindow& wndTarget) const
{
    wndTarget.draw(txtTurn);

    if (!txtStatus.getString().isEmpty())
        wndTarget.draw(txtStatus);

    wndTarget.draw(txtDeckCount);

    for (int i = 0; i < iPlayerCount; ++i)
    {
        wndTarget.draw(vTxtPlayerLabels[i]);
        wndTarget.draw(vTxtStackCounts[i]);
    }
}
