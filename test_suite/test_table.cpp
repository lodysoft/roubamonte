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
					<< std::endl << std::endl
					<< "\tHand:" << "\t\t"
					<< plyPlayer.getHand()					// Shows hand contents.
					<< std::endl
					<< "\tStack count:" << "\t"
					<< plyPlayer.getStack().count()			// Shows stack size.
					<< std::endl
					<< "\tStack top:" << "\t";
					
		try													// Shows top of stack, if available.
		{
			std::cout << plyPlayer.getStack().top();
		}
		catch(std::length_error& exLenght)
		{
			std::cout << "<empty>";
		}
		
		std::cout << std::endl << std::endl;
	}


	return 0;
}

