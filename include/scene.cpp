// scene.cpp

#include <string>
#include <algorithm>
#include <memory>

#include "scene.h"

static const float SLIDE_TIME  = 0.35f;    // Card movement duration in seconds.
static const float STEAL_TIME  = 0.40f;    // Stack-steal fly duration.

// ── Constructor ───────────────────────────────────────────────────────────────

scene::scene()
    : eState(estate::HAND_SELECT),
      iCurrentPlayer(0),
      iSelectedHandSlot(-1),
      pFont(nullptr),
      iPlayerCount(0)
{}

// ── Public interface ──────────────────────────────────────────────────────────

void scene::init(const sf::Font& fntFont, int iPlayers, sf::Vector2u vWinSz)
{
    pFont        = &fntFont;
    iPlayerCount = iPlayers;
    vWinSize     = vWinSz;

    // Reset game state — constructs a fresh table (deals cards, fills tray).
    pTable = std::make_unique<table>(iPlayers);

    layTable.compute(iPlayers, vWinSz);

    hudDisplay.init(fntFont, iPlayers, vWinSz);
    hudDisplay.set_layout(layTable);

    // Deck sprite (always face-down; card content irrelevant — never shown face-up).
    sprDeck.set_card(card(ACE, SPADES), fntFont);
    sprDeck.set_face_up(false);
    sprDeck.set_position(layTable.get_deck_position());

    vStackSprites.resize(iPlayers);

    iCurrentPlayer    = 0;
    iSelectedHandSlot = -1;
    eState            = estate::HAND_SELECT;

    sync_sprites();

    hudDisplay.set_turn(0);
    hudDisplay.set_status("Select a card from your hand");
}

// ── handle_event ─────────────────────────────────────────────────────────────

void scene::handle_event(const sf::Event& evtEvent)
{
    if (evtEvent.type == sf::Event::Resized)
    {
        on_window_resize(sf::Vector2u(evtEvent.size.width, evtEvent.size.height));
        return;
    }

    if (evtEvent.type == sf::Event::MouseMoved)
    {
        on_mouse_move(sf::Vector2f(
            (float)evtEvent.mouseMove.x,
            (float)evtEvent.mouseMove.y));
        return;
    }

    if (evtEvent.type != sf::Event::MouseButtonPressed) return;
    if (evtEvent.mouseButton.button != sf::Mouse::Left)  return;
    if (eState == estate::ANIMATING || eState == estate::GAME_OVER) return;

    sf::Vector2f vMouse(
        (float)evtEvent.mouseButton.x,
        (float)evtEvent.mouseButton.y);

    // Always allow re-selecting a hand card (also works to deselect / change).
    auto& vHand = vvHandSprites[iCurrentPlayer];
    for (int i = 0; i < (int)vHand.size(); ++i)
    {
        if (vHand[i].contains(vMouse))
        {
            on_hand_click(i);
            return;
        }
    }

    // Tray click is only meaningful after a hand card has been selected.
    if (eState == estate::TRAY_SELECT)
    {
        for (int i = 0; i < (int)vTraySprites.size(); ++i)
        {
            if (vTraySprites[i].contains(vMouse))
            {
                on_tray_click(i);
                return;
            }
        }
    }
}

// ── update ────────────────────────────────────────────────────────────────────

void scene::update(float fDelta)
{
    anmCards.update(fDelta);

    if (eState == estate::ANIMATING && !anmCards.isAnimating())
        on_animation_done();
}

// ── draw ──────────────────────────────────────────────────────────────────────

void scene::draw(sf::RenderWindow& wndTarget)
{
    // Stack sprites — draw only for players who own at least one card.
    for (int p = 0; p < iPlayerCount; ++p)
        if (!pTable->getPlayers()[p].getStack().isEmpty())
            vStackSprites[p].draw(wndTarget);

    // Deck — only draw while cards remain.
    if (!pTable->getDeck().isEmpty())
        sprDeck.draw(wndTarget);

    // Tray.
    for (auto& spr : vTraySprites)
        spr.draw(wndTarget);

    // Other players' hands (behind current player's hand).
    for (int p = 0; p < iPlayerCount; ++p)
        if (p != iCurrentPlayer)
            for (auto& spr : vvHandSprites[p])
                spr.draw(wndTarget);

    // Current player's hand on top.
    for (auto& spr : vvHandSprites[iCurrentPlayer])
        spr.draw(wndTarget);

    hudDisplay.draw(wndTarget);
}

// ── Internal helpers ──────────────────────────────────────────────────────────

void scene::sync_sprites()
{
    // ── Hand sprites ─────────────────────────────────────────────────────────
    vvHandSprites.resize(iPlayerCount);
    for (int p = 0; p < iPlayerCount; ++p)
    {
        hand& hnd    = pTable->getPlayers()[p].getHand();
        int   iCount = hnd.count();

        std::vector<sf::Vector2f> vPos = layTable.get_hand_positions(p);

        vvHandSprites[p].resize(iCount);
        for (int i = 0; i < iCount; ++i)
        {
            vvHandSprites[p][i].set_card(hnd[i], *pFont);
            vvHandSprites[p][i].set_face_up(p == iCurrentPlayer);
            vvHandSprites[p][i].set_selected(false);
            vvHandSprites[p][i].set_hover(false);
            if (i < (int)vPos.size())
                vvHandSprites[p][i].set_position(vPos[i]);
        }
    }

    // ── Tray sprites ──────────────────────────────────────────────────────────
    tray& tryTray   = pTable->getTray();
    int   iTrayCount = tryTray.count();

    std::vector<sf::Vector2f> vTrayPos = layTable.get_tray_positions(iTrayCount);

    vTraySprites.resize(iTrayCount);
    for (int i = 0; i < iTrayCount; ++i)
    {
        vTraySprites[i].set_card(tryTray[i], *pFont);
        vTraySprites[i].set_face_up(true);
        vTraySprites[i].set_selected(false);
        vTraySprites[i].set_hover(false);
        if (i < (int)vTrayPos.size())
            vTraySprites[i].set_position(vTrayPos[i]);
    }

    // ── Stack sprites ─────────────────────────────────────────────────────────
    vStackSprites.resize(iPlayerCount);
    for (int p = 0; p < iPlayerCount; ++p)
    {
        stack& stk = pTable->getPlayers()[p].getStack();
        if (!stk.isEmpty())
        {
            vStackSprites[p].set_card(stk.top(), *pFont);
            vStackSprites[p].set_face_up(false);
            vStackSprites[p].set_position(layTable.get_stack_position(p));
        }
    }

    // ── HUD counts ───────────────────────────────────────────────────────────
    hudDisplay.set_deck_count(pTable->getDeck().count());
    for (int p = 0; p < iPlayerCount; ++p)
        hudDisplay.set_stack_count(p, pTable->getPlayers()[p].getStack().count());

    hudDisplay.set_layout(layTable);
}

void scene::restore_selection_visual()
{
    if (eState != estate::TRAY_SELECT) return;
    if (iSelectedHandSlot < 0) return;
    auto& vHand = vvHandSprites[iCurrentPlayer];
    if (iSelectedHandSlot < (int)vHand.size())
        vHand[iSelectedHandSlot].set_selected(true);
}

void scene::on_hand_click(int iSlot)
{
    if (eState != estate::HAND_SELECT && eState != estate::TRAY_SELECT) return;

    // Deselect the previous card if any.
    if (iSelectedHandSlot >= 0 && iSelectedHandSlot < (int)vvHandSprites[iCurrentPlayer].size())
        vvHandSprites[iCurrentPlayer][iSelectedHandSlot].set_selected(false);

    // Register selection in game logic.
    pTable->getPlayers()[iCurrentPlayer].getHand().select(iSlot);
    iSelectedHandSlot = iSlot;

    vvHandSprites[iCurrentPlayer][iSlot].set_selected(true);
    eState = estate::TRAY_SELECT;

    hudDisplay.set_status("Select a tray card  (or click another hand card to change selection)");
}

void scene::on_tray_click(int iTraySlot)
{
    if (eState != estate::TRAY_SELECT) return;
    if (iSelectedHandSlot < 0) return;

    hand& hnd     = pTable->getPlayers()[iCurrentPlayer].getHand();
    tray& tryTray = pTable->getTray();

    int iHandRank = hnd[iSelectedHandSlot].rank();
    int iTrayRank = tryTray[iTraySlot].rank();
    bool bMatch   = (iHandRank == iTrayRank);

    // Save positions needed for animation before modifying game state.
    sf::Vector2f vOldHandPos  = vvHandSprites[iCurrentPlayer][iSelectedHandSlot].get_position();
    sf::Vector2f vCurStackPos = layTable.get_stack_position(iCurrentPlayer);

    if (bMatch)
    {
        // ── STEAL ────────────────────────────────────────────────────────────
        int iTarget = find_steal_target();
        sf::Vector2f vOldTargetStackPos = layTable.get_stack_position(iTarget);

        // iSelected is already set in hand from on_hand_click().
        iSelectedHandSlot = -1;
        pTable->getPlayers()[iCurrentPlayer].steal(pTable->getPlayers()[iTarget]);

        sync_sprites();

        // Animate: current player's stack sprite flies in from the old hand position.
        if (!pTable->getPlayers()[iCurrentPlayer].getStack().isEmpty())
            anmCards.add(&vStackSprites[iCurrentPlayer], vOldHandPos, vCurStackPos, STEAL_TIME);

        // Also animate the target's (now-empty) stack sprite fading away to current stack.
        // We draw it from its old position toward current player's stack.
        anmCards.add(&vStackSprites[iTarget], vOldTargetStackPos, vCurStackPos, STEAL_TIME);

        std::string strMsg = "Player " + std::to_string(iCurrentPlayer + 1) +
                             " steals Player "  + std::to_string(iTarget + 1) + "'s stack!";
        hudDisplay.set_status(strMsg);
        eState = estate::ANIMATING;
    }
    else
    {
        // ── DISCARD ──────────────────────────────────────────────────────────
        iSelectedHandSlot = -1;
        hnd.discard(tryTray);   // hnd.iSelected is already set.

        sync_sprites();

        // Animate the newly added tray card from where the hand card was.
        int iNewIdx = tryTray.count() - 1;
        if (iNewIdx >= 0 && iNewIdx < (int)vTraySprites.size())
        {
            sf::Vector2f vDest = vTraySprites[iNewIdx].get_position();
            anmCards.add(&vTraySprites[iNewIdx], vOldHandPos, vDest, SLIDE_TIME);
        }

        eState = estate::ANIMATING;
        hudDisplay.set_status("Card discarded to tray");
    }
}

void scene::on_mouse_move(sf::Vector2f vPos)
{
    if (eState == estate::ANIMATING || eState == estate::GAME_OVER) return;

    // Hover for current player's hand (always visible when it's their turn).
    if (eState == estate::HAND_SELECT || eState == estate::TRAY_SELECT)
    {
        for (auto& spr : vvHandSprites[iCurrentPlayer])
            spr.set_hover(spr.contains(vPos));
    }

    // Hover for tray cards only when a hand card is already selected.
    for (auto& spr : vTraySprites)
        spr.set_hover(eState == estate::TRAY_SELECT && spr.contains(vPos));
}

void scene::on_animation_done()
{
    try_refill_and_check_end();

    if (eState != estate::GAME_OVER)
    {
        advance_turn();
        eState = estate::HAND_SELECT;
    }
}

void scene::try_refill_and_check_end()
{
    // Refill any empty hands — getDeck() returns const& so we cast: underlying object is non-const.
    deck& dckMutable = const_cast<deck&>(pTable->getDeck());

    for (auto& ply : pTable->getPlayers())
        if (ply.getHand().isEmpty() && !dckMutable.isEmpty())
            ply.getHand().refill(dckMutable);

    sync_sprites();

    if (check_game_over())
    {
        eState = estate::GAME_OVER;

        int iWinner = 0;
        int iMax    = 0;
        for (int p = 0; p < iPlayerCount; ++p)
        {
            int iCount = pTable->getPlayers()[p].getStack().count();
            if (iCount > iMax)
            {
                iMax    = iCount;
                iWinner = p;
            }
        }

        hudDisplay.set_status("Game Over!  Player " + std::to_string(iWinner + 1) +
                              " wins with " + std::to_string(iMax) + " cards!");
    }
}

void scene::advance_turn()
{
    iCurrentPlayer    = (iCurrentPlayer + 1) % iPlayerCount;
    iSelectedHandSlot = -1;

    hudDisplay.set_turn(iCurrentPlayer);
    hudDisplay.set_status("Select a card from your hand");

    // Flip hands: only the current player sees their cards face-up.
    for (int p = 0; p < iPlayerCount; ++p)
        for (auto& spr : vvHandSprites[p])
            spr.set_face_up(p == iCurrentPlayer);
}

void scene::on_window_resize(sf::Vector2u vNewSize)
{
    anmCards.flush();   // Cancel in-flight animations to avoid dangling pointers after resize.

    vWinSize = vNewSize;
    layTable.compute(iPlayerCount, vNewSize);
    sync_sprites();

    hudDisplay.init(*pFont, iPlayerCount, vNewSize);
    hudDisplay.set_layout(layTable);
    hudDisplay.set_turn(iCurrentPlayer);
    hudDisplay.set_deck_count(pTable->getDeck().count());
    for (int p = 0; p < iPlayerCount; ++p)
        hudDisplay.set_stack_count(p, pTable->getPlayers()[p].getStack().count());

    if (eState == estate::TRAY_SELECT)
        hudDisplay.set_status("Select a tray card  (or click another hand card to change selection)");
    else if (eState == estate::HAND_SELECT)
        hudDisplay.set_status("Select a card from your hand");

    restore_selection_visual();

    if (eState == estate::ANIMATING)
        eState = estate::HAND_SELECT;   // Animation was flushed; safe to resume input.
}

int scene::find_steal_target() const
{
    // In a 2-player game this is always the opponent.
    // In N-player, steal from the player with the most cards (most rewarding target).
    int iBestPlayer = (iCurrentPlayer + 1) % iPlayerCount;
    int iBestCount  = pTable->getPlayers()[iBestPlayer].getStack().count();

    for (int p = 0; p < iPlayerCount; ++p)
    {
        if (p == iCurrentPlayer) continue;
        int iCount = pTable->getPlayers()[p].getStack().count();
        if (iCount > iBestCount)
        {
            iBestCount  = iCount;
            iBestPlayer = p;
        }
    }
    return iBestPlayer;
}

bool scene::check_game_over() const
{
    if (!pTable->getDeck().isEmpty()) return false;
    for (int p = 0; p < iPlayerCount; ++p)
        if (!pTable->getPlayers()[p].getHand().isEmpty()) return false;
    return true;
}
