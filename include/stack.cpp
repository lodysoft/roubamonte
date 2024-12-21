// stack.cpp

#include "card.h"
#include "stack.h"

card stack::pop()														// Takes a card from the stack.
{
	const card crdTemp = crdStack.top();											// Saves the top.

	crdStack.pop();														// Kills the top.

	return crdTemp;														// Returns the saved top.
}

void stack::push(const card crdCard)												// Puts a card on the top of the stack.
{
	crdStack.push(crdCard);													// Grows the stack	
}

const card& stack::top() const													// Returns the top card so we can steal this stack.
{
	if(crdStack.size()) return crdStack.top(); else throw std::length_error("*** Bad stack *** - Stack is empty!");
}

const int stack::count() const													// Returns the size of this stack.
{
	return crdStack.size();
}

const bool stack::isEmpty() const {return crdStack.empty();}									// Informs whether we became out of cards.

