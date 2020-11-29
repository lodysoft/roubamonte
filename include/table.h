// table.h

#ifndef TABLE_H
#define TABLE_H

#include <list>

#include "card.h"

class table
{
public:
	table();		// Default constructor.

private:
	std::list<card> crdList;

};

#endif

