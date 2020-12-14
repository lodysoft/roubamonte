// test_table.cpp

#include <iostream>														// std::cout

#include "../include/deck.h"
#include "../include/table.h"
#include "include/output.h"

int main()
{
	table tblTable;														// Calls the default constructor.

	std::cout << std::endl												// Shows the table contents.
				<< "Cards on the table:"
				<< std::endl << std::endl << "\t"
				<< tblTable
				<< std::endl << std::endl;

	return 0;
}

