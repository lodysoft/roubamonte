// tray.cpp

/**
 * Implementation of central game tray functionality.
 * Manages shared cards available for all players.
 */

#include "tray.h"

/**
 * Creates new tray with TRAY_INITIAL_CARDS cards.
 * Immediately fills tray from deck.
 */
tray::tray(deck& dckDeck): selection_container(dckDeck, TRAY_INITIAL_CARDS) {refill(dckDeck);}		// Default constructor.

