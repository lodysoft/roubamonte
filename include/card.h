// card.h

// Card class for card games

#ifndef CARD_H
#define CARD_H

#include <stdexcept>										// std::out_of_range()

enum {SUITLESS, SPADES, HEARTS, DIAMONDS, CLUBS};			// Suits - because a joker has no suit, suit 0 now means no suit.
enum {JOKER, ACE, JACK = 11, QUEEN, KING};					// Figures.

class card
{
public:	
	card(int iFig, int iSt);								// Constructor.
	card(const card& crdOther);								// Copy constructor.

	card& operator=(const card& crdOther);					// Assignment operator.
	const bool operator<(const card& crdOther);				// Less than operator.

	const int figure() const;								// Only getters because you will never need to change a card.
	const int suit() const;
	
private:
	int iFigure;
	int iSuit;

};

#endif

