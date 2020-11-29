// card.h

// Card class for card games

#ifndef CARD_H
#define CARD_H

#include <stdexcept>										// For std::out_of_range().

enum {SUITLESS, SPADES, HEARTS, DIAMONDS, CLUBS};			// Suits - because a joker has no suit, suit 0 now means no suit.
enum {JOKER, ACE, JACK = 11, QUEEN, KING};					// Figures

class card
{
public:	
	card(int iNum, int iSt);								// Constructor
	const int figure() const;								// Only getters because you will never need to change a card.
	const int suit() const;
	
private:
	const int iFigure;
	const int iSuit;

};

card::card(int iNum, int iSt):								// Constructor definition
	iFigure((iNum < JOKER || iNum > KING) ? throw std::out_of_range("*** Bad card *** - Bad figure!") : iNum),
	iSuit((iSt < JOKER || iSt > CLUBS) ? throw std::out_of_range("*** Bad card *** - Bad suit!") : iSt) {}

inline const int card::figure() const {return iFigure;}		// Getters definitions
inline const int card::suit() const {return iSuit;}

#endif

