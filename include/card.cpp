// card.cpp

#include "card.h"

card::card(int iFig, int iSt):																									// Constructor definition.
	iFigure((iFig < JOKER || iFig > KING)? throw std::out_of_range("*** Bad card *** - Bad figure!"): iFig),
	iSuit((iSt < RED || iSt > CLUBS)? throw std::out_of_range("*** Bad card *** - Bad suit!"): iSt) {}

card::card(const card& crdOther): iFigure(crdOther.iFigure), iSuit(crdOther.iSuit) {}											// Copy constructor.

card& card::operator=(const card& crdOther) {iFigure = crdOther.iFigure; iSuit = crdOther.iSuit; return *this;}					// Assignment operator.

const bool card::operator<(const card& crdOther) const																			// Less than operator.
{
	if(this->suit() == crdOther.suit()) return this->figure() < crdOther.figure();

	return this->suit() < crdOther.suit();
}

const bool card::operator==(const card& crdOther) const {return this->iSuit == crdOther.iSuit && this->iFigure == crdOther.iFigure;}		// Equality operator.

const int card::figure() const {return iFigure;}																				// Getters definitions.
const int card::suit() const {return iSuit;}

