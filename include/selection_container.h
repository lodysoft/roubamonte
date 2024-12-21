// selection_container.h

/**
 * @brief Abstract base class for card containers that support selection
 * 
 * Provides common functionality for managing a collection of cards where
 * individual cards can be selected and manipulated. Used as base class
 * for both player hands and the central tray.
 */

#ifndef SELECTION_CONTAINER_H
#define SELECTION_CONTAINER_H

#include <set>
#include <map>

#include "card.h"
#include "deck.h"

class selection_container
{
public:
    /**
     * @brief Constructs container with initial cards from deck
     * @param dckDeck Source deck to draw cards from
     * @param iInitial Number of cards to initially draw
     */
    selection_container(deck& dckDeck, const int iInitial);
    virtual ~selection_container() = default;
    
    const bool isEmpty() const;                                     // Informs whether we became out of cards.
    const int count() const;                                        // Returns the current number of cards.
    /**
     * @brief Selects a card at given index
     * @param iIndex Index of card to select
     * @throws std::out_of_range if index invalid
     */
    void select(const int iIndex);
    /**
     * @brief Access card at given index
     * @param iIndex Index of card to access
     * @returns Reference to card at index
     * @throws std::out_of_range if index invalid
     */
    const card& operator[](const int iIndex);
    void refill(deck& dckDeck);                                     // Takes cards from the pile.
    
protected:
    const int iInitialCards;                                        ///< Initial card count for this container
    int iSelected;                                                  ///< Index of currently selected card
    std::map<int, card> mapCards;                                   ///< Storage for cards indexed by position
    const int getInitialCards() const;                              ///< Returns initial card count for derived class use

};

#endif

