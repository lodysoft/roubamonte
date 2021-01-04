// test_stack.cpp

// Program to test the stack class

#include <iostream>								// std::cout

#include "../include/stack.h"
#include "include/output.h"

int main()
{
	stack stkStack;								// Invokes the implicit default constructor.
	
	stkStack.push(card(JOKER, BLACK));			// Adds a card to the stack.
	stkStack.push(card(QUEEN, HEARTS));			// Adds another card to the stack.	

	std::cout << std::endl						// Displays it.
				<< "Card count:\t"
				<< stkStack.count()
				<< std::endl
				<< "Top of pile:\t"
				<< stkStack.top()
				<< std::endl << std::endl;

	return 0;
}

