// card.cpp

#include "card.h"

card::card(int iRank, int iSt):																									// Constructor definition.
	iRank((iRank < JOKER || iRank > KING)? throw std::out_of_range("*** Bad card *** - Bad rank!"): iRank),
	iSuit((iSt < RED || iSt > CLUBS)? throw std::out_of_range("*** Bad card *** - Bad suit!"): iSt) {}

card::card(const card& crdOther): iRank(crdOther.iRank), iSuit(crdOther.iSuit) {}											// Copy constructor.

card& card::operator=(const card& crdOther) {iRank = crdOther.iRank; iSuit = crdOther.iSuit; return *this;}					// Assignment operator.

const bool card::operator<(const card& crdOther) const																			// Less than operator.
{
	if(this->suit() == crdOther.suit()) return this->rank() < crdOther.rank();

	return this->suit() < crdOther.suit();
}

const bool card::operator==(const card& crdOther) const {return this->iSuit == crdOther.iSuit && this->iRank == crdOther.iRank;}		// Equality operator.

const int card::rank() const {return iRank;}																				// Getters definitions.
const int card::suit() const {return iSuit;}

