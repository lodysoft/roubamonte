// stack.h

// A stack of cards for card games

#ifndef STACK_H
#define STACK_H

#include <stack>

#include "card.h"

class stack
{
public:
	stack();							// Default constructor.
	const card pop();					// Takes a card from the stack.
	void push(const card crdCard);		// Puts a card on the top of the stack.

protected:
	std::stack<card> crdStack;
};

#endif

