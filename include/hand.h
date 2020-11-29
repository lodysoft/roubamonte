// hand.h

#ifndef HAND_H
#define HAND_H

#include <list>

#include "card.h"

class hand
{
public:
	hand();		// Default constructor.

private:
	std::list<card> crdList;

};

#endif

