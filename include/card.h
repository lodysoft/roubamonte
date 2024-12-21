// card.h

// Card class for card games

#ifndef CARD_H
#define CARD_H

#include <stdexcept>						// std::out_of_range()

enum {RED = -1, BLACK, SPADES, HEARTS, DIAMONDS, CLUBS};	// Now we have suits for jokers: red label and black label.
enum {JOKER, ACE, JACK = 11, QUEEN, KING};			// Figures.

class card
{
public:	
	card(int iFig, int iSt);				// Constructor.
	card(const card& crdOther);				// Copy constructor.

	card& operator=(const card& crdOther);			// Assignment operator.
	const bool operator<(const card& crdOther) const;	// Less than operator.

	const int figure() const;				// Only getters because you will never need to change a card.
	const int suit() const;
	
private:
	int iFigure;
	int iSuit;

};

#endif

