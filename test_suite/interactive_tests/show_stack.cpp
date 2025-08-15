// show_stack.cpp

// Runtime demonstration of stack class operations

#include "include/output.h"					// Header file containing overloaded insertion operators.

int main()
{
	stack stkStack;							// Invokes the implicit default constructor.
	
	stkStack.push(card(JOKER, BLACK));		// Adds some cards to the stack.
	stkStack.push(card(QUEEN, HEARTS));	

	std::cout << std::endl					// Displays it.
				<< "Card count:\t"
				<< stkStack.count()
				<< std::endl
				<< "Top of pile:\t"
				<< stkStack.top()
				<< std::endl << std::endl;

	return 0;
}

