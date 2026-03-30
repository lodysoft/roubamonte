// scene.h

// Top-level game orchestrator.
// Owns the table (game logic), layout, animator, hud, and all card sprites.
// Call init() once, then feed events via handle_event() and call update()/draw() each frame.

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "table.h"
#include "layout.h"
#include "animator.h"
#include "hud.h"
#include "card_sprite.h"

class scene
{
public:
    scene();

    // Set up a fresh game.  Must be called before any other method.
    void init(const sf::Font& fntFont, int iPlayers, sf::Vector2u vWinSize);

    // Forward a polled SFML event (mouse, keyboard, resize).
    void handle_event(const sf::Event& evtEvent);

    // Advance animations and check state transitions.
    void update(float fDelta);

    // Render everything to the window.
    void draw(sf::RenderWindow& wndTarget);

private:

    // ── Game state machine ────────────────────────────────────────────────────

    enum class estate { HAND_SELECT, TRAY_SELECT, ANIMATING, GAME_OVER };

    estate eState;

    // ── Core objects ──────────────────────────────────────────────────────────

    std::unique_ptr<table> pTable;
    layout   layTable;
    animator anmCards;
    hud      hudDisplay;

    // ── Sprites ───────────────────────────────────────────────────────────────

    std::vector<std::vector<card_sprite>> vvHandSprites;    // [player][card slot]
    std::vector<card_sprite>              vTraySprites;
    card_sprite                           sprDeck;
    std::vector<card_sprite>              vStackSprites;    // [player] — one face-down pile per player

    // ── Interaction state ─────────────────────────────────────────────────────

    int          iCurrentPlayer;
    int          iSelectedHandSlot;     // -1 = nothing selected

    // ── Context ───────────────────────────────────────────────────────────────

    const sf::Font* pFont;
    int             iPlayerCount;
    sf::Vector2u    vWinSize;

    // ── Internal helpers ──────────────────────────────────────────────────────

    // Rebuild all card sprites and HUD counts from current game state.
    // Safe to call only when no animations are in flight.
    void sync_sprites();

    // Re-apply the selected highlight after a sync (called when eState == TRAY_SELECT).
    void restore_selection_visual();

    // Click handlers.
    void on_hand_click(int iSlot);
    void on_tray_click(int iTraySlot);
    void on_mouse_move(sf::Vector2f vPos);

    // Called after animator queue empties in ANIMATING state.
    void on_animation_done();

    // Refill empty hands from the deck; transition to GAME_OVER if applicable.
    void try_refill_and_check_end();

    // Rotate iCurrentPlayer, update HUD, flip face-up/down hands.
    void advance_turn();

    // Handle window resize: recomputes layout and resyncs sprites.
    void on_window_resize(sf::Vector2u vNewSize);

    // Returns the 0-based index of the player to steal from.
    int find_steal_target() const;

    // True when deck and all hands are empty.
    bool check_game_over() const;
};

#endif
