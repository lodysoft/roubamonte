// hand.h

// A player's hand of cards

#ifndef HAND_H
#define HAND_H

#include "selection_container.h"

class tray;                             // Forward declaration to avoid circular dependency

const int HAND_INITIAL_CARDS = 4;       // Initial amount of cards a player receives.

/**
 * @brief Represents a player's hand of cards
 * 
 * Manages a player's current cards, allowing selection and discard operations.
 * Always maintains HAND_INITIAL_CARDS cards when possible through refills.
 */
class hand: public selection_container
{
public:
    /**
     * @brief Creates new hand with initial cards from deck
     * @param dckDeck Source deck to draw cards from
     */
    hand(deck& dckDeck);
    
    /**
     * @brief Discards currently selected card
     * @returns The discarded card
     * @throws std::out_of_range if no card selected
     */
    card discard();                     // Original version, returns the card
    
    /**
     * @brief Discards currently selected card to the tray
     * @param trayTarget Tray to discard card to
     * @throws std::out_of_range if no card selected
     */
    void discard(tray& trayTarget);     // New overloaded version: discards to tray instead of returning the card
};

#endif

