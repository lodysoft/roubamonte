// stack.h

// A stack of cards for card games

#ifndef STACK_H
#define STACK_H

#include <stack>

#include "card.h"

class stack
{
public:
	card pop();							// Takes a card from the stack.
	void push(const card crdCard);		// Puts a card on the top of the stack.
	const card& top() const;			// Returns the top card so we can steal this stack.
	const int count() const;			// Returns the size of this stack.
	const bool isEmpty() const;			// Tests whether the cards are over.

protected:
	std::stack<card> crdStack;
};

#endif

