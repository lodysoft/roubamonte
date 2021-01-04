// test_table.cpp

#include <iostream>														// std::cout

#include "../include/deck.h"
#include "../include/table.h"
#include "include/output.h"

int main()
{
	int iCount = 0;

	table tblTable;														// Calls the default constructor.

	std::cout << std::endl												// Shows the table contents.
				<< "Cards on the table:"
				<< std::endl << std::endl << "\t"
				<< tblTable
				<< std::endl << std::endl;

	for(player plyPlayer: tblTable.getPlayers())
	{
		std::cout << "<Player {"
					<< iCount++
					<< "}>"
					<< plyPlayer
					<< std::endl
					<< std::endl;
	}

	return 0;
}

