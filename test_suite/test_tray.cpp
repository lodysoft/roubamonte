// test_tray.cpp

#include <cassert>													// assert
#include <stdexcept>													// std::out_of_range
#include <iostream>

#include "../include/deck.h"
#include "../include/tray.h"
#include "include/output.h"

/**
 * Tests whether a tray is properly constructed with the initial amount of cards.
 *
 * Checks the tray's size and whether it is empty.
 */
void test_tray_construction()
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    assert(tryTray.count() == TRAY_INITIAL_CARDS);
    assert(!tryTray.isEmpty());
}

/**
 * Tests whether the refill behavior of a tray works correctly.
 *
 * Verifies that when a tray is refilled, the cards currently in the tray
 * are not changed.
 */
void test_tray_refill_behavior() 
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    // Remember initial cards
    std::set<card> initialCards;
    for(int i = 0; i < TRAY_INITIAL_CARDS; i++) 
	{
        initialCards.insert(tryTray[i]);
    }
    
    // Refill shouldn't change cards
    tryTray.refill(dckDeck);
    
    // Verify same cards remain
    for(int i = 0; i < TRAY_INITIAL_CARDS; i++)
	{
        assert(initialCards.find(tryTray[i]) != initialCards.end());
    }
}

/**
 * Tests whether a tray can be properly selected with valid and invalid indices.
 *
 * Checks that selecting a card with a valid index works and that selecting a card 
 * with an invalid index throws an out_of_range exception.
 */

void test_tray_selection()
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    // Valid selection
    tryTray.select(0);
    tryTray.select(TRAY_INITIAL_CARDS - 1);
    
    // Invalid selection
    bool caught = false;
    try
	{
        tryTray.select(TRAY_INITIAL_CARDS);
    }
	catch(const std::out_of_range&)
	{
        caught = true;
    }
    assert(caught && "Expected out_of_range exception");
}

/**
 * Runs all tests for the tray class.
 *
 * Outputs to the console the name of the test being run, and whether all tests
 * passed or not.
 */

int main()
{
    std::cout << "Running tray tests...\n";
    
    test_tray_construction();
    test_tray_refill_behavior();
    test_tray_selection();
    
    std::cout << "All tray tests passed!\n";

    // Deprecated test: user interaction

	int iChoice = 0;

	deck dckDeck;													// Creates a deck.

	tray tryTray(dckDeck);												// Takes four cards from it.

	std::cout << std::endl << "\t" << tryTray << std::endl << std::endl;						// Shows the tray contents.

	std::cout << "\tPlease choose a card (0 to 7):\t";

	std::cin >> iChoice;

	std::cout << std::endl << std::endl << "\tYou've chosen:\t" << tryTray[iChoice] << std::endl << std::endl;
 
    return 0;
}

