// layout.cpp

#include <cmath>

#include "layout.h"
#include "card_sprite.h"    // CARD_WIDTH, CARD_HEIGHT
#include "hand.h"           // HAND_INITIAL_CARDS

static const float HAND_GAP    = 10.0f;     // Gap between cards in a hand spread.
static const float STACK_OFF   = 18.0f;     // Gap between hand area edge and stack indicator.
static const float MARGIN      = 15.0f;     // Window-edge margin.
static const float TRAY_MAX_W  = 0.60f;     // Max fraction of window width used by the tray.

// ── Helpers ───────────────────────────────────────────────────────────────────

// Half-width and half-height of a fully spread hand.
static const float fHalfHW =
    (HAND_INITIAL_CARDS * CARD_WIDTH  + (HAND_INITIAL_CARDS - 1) * HAND_GAP) / 2.0f;

static const float fHalfVH =
    (HAND_INITIAL_CARDS * CARD_HEIGHT + (HAND_INITIAL_CARDS - 1) * HAND_GAP) / 2.0f;

// Stack positioned just to the right of a horizontal hand.
static sf::Vector2f h_stack(sf::Vector2f vCenter)
{
    return sf::Vector2f(
        vCenter.x + fHalfHW + STACK_OFF,
        vCenter.y - CARD_HEIGHT / 2.0f
    );
}

// Stack positioned just below a vertical hand.
static sf::Vector2f v_stack(sf::Vector2f vCenter)
{
    return sf::Vector2f(
        vCenter.x - CARD_WIDTH / 2.0f,
        vCenter.y + fHalfVH + STACK_OFF
    );
}

// ── Constructor ───────────────────────────────────────────────────────────────
layout::layout() : iPlayerCount(0) {}

// ── Public interface ──────────────────────────────────────────────────────────
void layout::compute(int iPlayers, sf::Vector2u vWinSize)
{
    iPlayerCount = iPlayers;
    vWindowSize  = vWinSize;
    vAnchors.clear();
    vAnchors.resize(iPlayers);
    compute_anchors((float)vWinSize.x, (float)vWinSize.y);
}

int layout::get_player_count() const
{
    return iPlayerCount;
}

sf::Vector2f layout::get_deck_position() const
{
    return vDeckPos;
}

sf::Vector2f layout::get_stack_position(int iPlayer) const
{
    if (iPlayer < 0 || iPlayer >= iPlayerCount)
        return sf::Vector2f(0.0f, 0.0f);
    return vAnchors[iPlayer].vStackPos;
}

std::vector<sf::Vector2f> layout::get_hand_positions(int iPlayer) const
{
    std::vector<sf::Vector2f> vPos;

    if (iPlayer < 0 || iPlayer >= iPlayerCount)
        return vPos;

    const player_anchor& anc = vAnchors[iPlayer];

    if (!anc.bVertical)
    {
        // Horizontal spread (bottom / top / corner players).
        float fStartX = anc.vHandCenter.x - fHalfHW;
        float fY      = anc.vHandCenter.y  - CARD_HEIGHT / 2.0f;
        for (int i = 0; i < HAND_INITIAL_CARDS; ++i)
            vPos.push_back(sf::Vector2f(fStartX + i * (CARD_WIDTH + HAND_GAP), fY));
    }
    else
    {
        // Vertical spread (left / right players).
        float fX      = anc.vHandCenter.x - CARD_WIDTH  / 2.0f;
        float fStartY = anc.vHandCenter.y  - fHalfVH;
        for (int i = 0; i < HAND_INITIAL_CARDS; ++i)
            vPos.push_back(sf::Vector2f(fX, fStartY + i * (CARD_HEIGHT + HAND_GAP)));
    }

    return vPos;
}

std::vector<sf::Vector2f> layout::get_tray_positions(int iCount) const
{
    std::vector<sf::Vector2f> vPos;
    if (iCount <= 0) return vPos;

    float fMaxWidth = (float)vWindowSize.x * TRAY_MAX_W;

    float fGap;
    if (iCount == 1)
        fGap = 0.0f;
    else
    {
        // Compute gap that fills the budget; clamp so cards never shrink below 30% visibility.
        fGap = (fMaxWidth - (float)iCount * CARD_WIDTH) / (float)(iCount - 1);
        if (fGap > HAND_GAP)             fGap = HAND_GAP;
        if (fGap < -CARD_WIDTH * 0.30f)  fGap = -CARD_WIDTH * 0.30f;
    }

    float fTotal  = (float)iCount * CARD_WIDTH + (float)(iCount - 1) * fGap;
    float fStartX = vTrayCenter.x - fTotal  / 2.0f;
    float fY      = vTrayCenter.y - CARD_HEIGHT / 2.0f;

    for (int i = 0; i < iCount; ++i)
        vPos.push_back(sf::Vector2f(fStartX + (float)i * (CARD_WIDTH + fGap), fY));

    return vPos;
}

// ── Anchor computation ────────────────────────────────────────────────────────
void layout::compute_anchors(float fW, float fH)
{
    const float fCX = fW / 2.0f;
    const float fCY = fH / 2.0f;

    vTrayCenter = sf::Vector2f(fCX, fCY);
    vDeckPos    = sf::Vector2f(MARGIN, fCY - CARD_HEIGHT / 2.0f);

    if (iPlayerCount == 1)
    {
        sf::Vector2f vC(fCX, fH - MARGIN - CARD_HEIGHT / 2.0f);
        vAnchors[0] = { vC, h_stack(vC), false };
        return;
    }

    if (iPlayerCount == 2)
    {
        sf::Vector2f vC0(fCX, fH - MARGIN - CARD_HEIGHT / 2.0f);
        sf::Vector2f vC1(fCX, MARGIN       + CARD_HEIGHT / 2.0f);
        vAnchors[0] = { vC0, h_stack(vC0), false };
        vAnchors[1] = { vC1, h_stack(vC1), false };
        return;
    }

    if (iPlayerCount == 3)
    {
        // P0 bottom-centre, P1 top-left quarter, P2 top-right quarter.
        sf::Vector2f vC0(fCX,      fH - MARGIN - CARD_HEIGHT / 2.0f);
        sf::Vector2f vC1(fW * 0.25f, MARGIN    + CARD_HEIGHT / 2.0f);
        sf::Vector2f vC2(fW * 0.75f, MARGIN    + CARD_HEIGHT / 2.0f);
        vAnchors[0] = { vC0, h_stack(vC0), false };
        vAnchors[1] = { vC1, h_stack(vC1), false };
        vAnchors[2] = { vC2, h_stack(vC2), false };
        return;
    }

    if (iPlayerCount == 4)
    {
        // P0 bottom, P1 top, P2 left (vertical), P3 right (vertical).
        sf::Vector2f vC0(fCX,                        fH - MARGIN - CARD_HEIGHT / 2.0f);
        sf::Vector2f vC1(fCX,                        MARGIN      + CARD_HEIGHT / 2.0f);
        sf::Vector2f vC2(MARGIN      + CARD_WIDTH / 2.0f,  fCY);
        sf::Vector2f vC3(fW - MARGIN - CARD_WIDTH / 2.0f,  fCY);
        vAnchors[0] = { vC0, h_stack(vC0), false };
        vAnchors[1] = { vC1, h_stack(vC1), false };
        vAnchors[2] = { vC2, v_stack(vC2), true  };
        vAnchors[3] = { vC3, v_stack(vC3), true  };
        return;
    }

    // General case: N > 4 players on an ellipse.
    // P0 anchored at the bottom (270° in screen coords = 3π/2 radians).
    const float fRX  = fW * 0.38f;
    const float fRY  = fH * 0.38f;
    const float fPI  = 3.14159265f;

    for (int i = 0; i < iPlayerCount; ++i)
    {
        float fAngle = fPI * 1.5f + (float)i * 2.0f * fPI / (float)iPlayerCount;
        sf::Vector2f vC(
            fCX + fRX * std::cos(fAngle),
            fCY + fRY * std::sin(fAngle)
        );
        // Treat as vertical if the player sits predominantly on the left/right arc.
        bool bVert = std::abs(std::cos(fAngle)) > std::abs(std::sin(fAngle));
        vAnchors[i] = { vC, bVert ? v_stack(vC) : h_stack(vC), bVert };
    }
}
