// test_player.cpp

// Program to test the player class

#include <iostream>									// std::cout

#include "../include/deck.h"
#include "../include/player.h"
#include "include/output.h"

int main()
{
	deck dckPile;										// Creates a deck.
	player plyPlayer(dckPile);							// Invokes the constructor.

	for(int i = 0; i < 6; i++)							// Moves some cards from the pile to the stack.
		plyPlayer.getStack().push(dckPile.pop());		// Comment out these two lines to get an empty stack.
	
	std::cout << std::endl
				<< "Hand:" << "\t\t"
				<< plyPlayer.getHand()					// Shows hand contents.
				<< std::endl
				<< "Stack count:" << "\t"
				<< plyPlayer.getStack().count()			// Shows stack size.
				<< std::endl
				<< "Stack top:" << "\t[";
				
	try													// Shows top of stack, if available.
	{
		std::cout << plyPlayer.getStack().top();
	}
	catch(std::length_error& exLenght)
	{
		std::cout << "<empty>";
	}
	
	std::cout << "]" << std::endl << std::endl;

	return 0;
}

