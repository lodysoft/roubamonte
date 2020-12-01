// stack.cpp

#include "card.h"
#include "stack.h"

card stack::pop()								// Takes a card from the stack.
{
	const card crdTemp = crdStack.top();		// Saves the top.

	crdStack.pop();								// Kills the top.

	return crdTemp;								// Returns the saved top.
}

void stack::push(const card crdCard)			// Puts a card on the top of the stack.
{
	crdStack.push(crdCard);						// Grows the stack	
}

