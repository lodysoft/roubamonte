// tray.h

// The discard pile of a game.

#ifndef TRAY_H
#define TRAY_H

#include "selection_container.h"

const int TRAY_INITIAL_CARDS = 8;        // Initial amount of cards of the tray.

/**
 * @brief Represents the central discard tray
 * 
 * Manages face-up cards available for selection.
 * Initially contains TRAY_INITIAL_CARDS cards and can grow through player discards.
 */
class tray: public selection_container
{
public:
    /**
     * @brief Creates new tray with initial cards from deck
     * @param dckDeck Source deck to draw cards from
     */
    tray(deck& dckDeck);

    /**
     * @brief Adds a discarded card to the tray
     * @param crdDiscarded Card to add to tray
     */
    void receive_discard(const card& crdDiscarded);

};

#endif

