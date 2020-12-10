// test_table.cpp

#include <iostream>

#include "../include/deck.h"
#include "../include/table.h"
#include "include/output.h"

int main()
{
	deck dckDeck;

	table tblTable(dckDeck);

	std::cout << tblTable << std::endl << std::endl;

	return 0;
}

