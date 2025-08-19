// show_player.cpp

// Runtime demonstration of player class operations

#include "include/output.h"																		// Header file containing overloaded insertion operators.

int main()
{
	deck dckPile;																				// Creates a deck.
	player plyPlayer(dckPile);																	// Invokes the constructor.
	player plyOther(dckPile);																	// Here comes a new challenger.

	for(int i = 0; i < 6; i++)																	// Moves some cards from the pile to each player's stack.
	{
		plyPlayer.getStack().push(dckPile.pop());												// Comment out any of these lines to get an empty stack.
		plyOther.getStack().push(dckPile.pop());
	}
	
	std::cout << std::endl << "Player 1:" << std::endl << plyPlayer << std::endl << std::endl;
	std::cout << std::endl << "Player 2:" << std::endl << plyOther << std::endl << std::endl;

	plyPlayer.getHand().select(2);																// Selects the third card in the hand.
	plyPlayer.steal(plyOther);																	// Player 1 steals from Player 2.

	std::cout << std::endl << "After Player 1 stole from Player 2:" << std::endl << std::endl;

	std::cout << std::endl << "Player 1:" << std::endl << plyPlayer << std::endl << std::endl;	// Outputs both players.
	std::cout << std::endl << "Player 2:" << std::endl << plyOther << std::endl << std::endl;

	// TODO: buy() and discard() methods (both should involve the table).

	return 0;
}

