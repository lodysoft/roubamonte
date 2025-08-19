// show_table.cpp

// Runtime demonstration of table class operations

#include "include/output.h"							// Header file containing overloaded insertion operators.
#include "../../include/table.h"					// Necessary here because output.h doesn't have it.

int main()
{
	int iCount = 0;									// Counts the number of players.

	table tblTable;									// Calls the default constructor.

	std::cout << std::endl							// Shows the tray contents.
				<< "Cards on the table:"
				<< std::endl << std::endl << "\t"
				<< tblTable.getTray()
				<< std::endl << std::endl;

	for(player plyPlayer: tblTable.getPlayers())	// Shows the players.
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

