// test_player.cpp

// Program to test the player class

#include <iostream>									// std::cout

#include "../include/deck.h"
#include "../include/player.h"
#include "include/output.h"

int main()
{
	deck dckPile;									// Creates a deck.
	player plyPlayer(dckPile);						// Invokes the constructor.
	player plyOther(dckPile);						// Here comes a new challenger.

	for(int i = 0; i < 6; i++)						// Moves some cards from the pile to each player's stack.
	{
		plyPlayer.getStack().push(dckPile.pop());	// Comment out any of these lines to get an empty stack.
		plyOther.getStack().push(dckPile.pop());
	}
	
	std::cout << std::endl << "Player 1:" << std::endl << plyPlayer << std::endl << std::endl;
	std::cout << std::endl << "Player 2:" << std::endl << plyOther << std::endl << std::endl;

	plyPlayer.getHand().select(2);
	plyPlayer.steal(plyOther);

	std::cout << std::endl << "After Player 1 had stolen Player 2:" << std::endl << std::endl;

	std::cout << std::endl << "Player 1:" << std::endl << plyPlayer << std::endl << std::endl;
	std::cout << std::endl << "Player 2:" << std::endl << plyOther << std::endl << std::endl;

	// TODO: buy() and discard() methods (both should involve the table).

	return 0;
}

