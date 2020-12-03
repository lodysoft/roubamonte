// card.cpp

#include "card.h"

card::card(int iFig, int iSt):																						// Constructor definition.
	iFigure((iFig < JOKER || iFig > KING) ? throw std::out_of_range("*** Bad card *** - Bad figure!") : iFig),
	iSuit((iSt < SUITLESS || iSt > CLUBS) ? throw std::out_of_range("*** Bad card *** - Bad suit!") : iSt) {}

card::card(const card& crdOther): iFigure(crdOther.iFigure), iSuit(crdOther.iSuit) {}										// Copy constructor.

card& card::operator=(const card& crdOther) {iFigure = crdOther.iFigure; iSuit = crdOther.iSuit; return *this;}			// Assignment operator.

const int card::figure() const {return iFigure;}																	// Getters definitions.
const int card::suit() const {return iSuit;}

