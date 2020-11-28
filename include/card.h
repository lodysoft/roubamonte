// card.h

// Card class for card games

#ifndef CARD_H
#define CARD_H

#include <stdexcept>										// For std::out_of_range().

enum {SPADES, HEARTS, DIAMONDS, CLUBS};						// Suits
enum {JOKER, ACE, JACK = 11, QUEEN = 12, KING = 13};		// Figures

class card
{
public:	
	card(int iNum, int iSt);								// Constructor
	const int number() const;								// Only getters because you will never need to change a card.
	const int suit() const;
	
private:
	const int iNumber;
	const int iSuit;

};

card::card(int iNum, int iSt):								// Constructor definition
	iNumber((iNum < JOKER || iNum > KING) ? throw std::out_of_range("*** Bad card *** - Bad number!") : iNum),
	iSuit((iSt < SPADES || iSt > CLUBS) ? throw std::out_of_range("*** Bad card *** - Bad suit!") : iSt) {}

inline const int card::number() const {return iNumber;}		// Getters definitions
inline const int card::suit() const {return iSuit;}

#endif

