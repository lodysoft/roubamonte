// test_hand.cpp

// Program to test the hand class.

#include <stdexcept>													    // std::out_of_range
#include <cassert>													        // assert
#include <iostream>													        // std::cout

#include "../include/deck.h"
#include "../include/hand.h"
#include "../include/tray.h"
#include "include/output.h"

/**
 * Tests whether a hand is properly constructed with four cards.
 *
 * Checks the hand's size and whether it is empty.
 */
void test_hand_construction()
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    assert(hndHand.count() == 4);
    assert(!hndHand.isEmpty());
}

/**
 * Tests whether a hand can be properly refilled with four new cards.
 *
 * Checks the hand's size before and after refilling.
 */
void test_hand_refill()
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    tray tryTray(dckDeck);                                                  // Discard all cards
    for(int i = 0; i < 4; i++)
{
        hndHand.select(0);
        hndHand.discard();
    }
    
    assert(hndHand.isEmpty());
    
    // Refill
    hndHand.refill(dckDeck);
    assert(hndHand.count() == 4);
}

/**
 * Tests whether a hand can be properly selected with a valid and invalid index.
 *
 * Checks that selecting a card with a valid index works and that selecting a card with an invalid index throws.
 */
void test_hand_selection()
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    hndHand.select(3);                                                      // Test valid selection
    
	bool caught = false;                                                    // Test invalid selection
    try
	{
        hndHand.select(4);							                        // Should throw
	}    
	catch(const std::out_of_range&)
	{
        caught = true;
    }
	assert(caught && "test_hand_selection: Expected out_of_range exception");
}

/**
 * Tests whether discarding a card to tray works correctly.
 * Verifies card movement from hand to tray.
 */
void test_hand_discard_to_tray()
{
    deck dckDeck;
    tray tryTray(dckDeck);
    hand hndHand(dckDeck);
    
    int initialTrayCount = tryTray.count();
    card expectedCard = hndHand[0];
    
    hndHand.select(0);
    hndHand.discard(tryTray);
    
    assert(hndHand.count() == HAND_INITIAL_CARDS - 1);
    assert(tryTray.count() == initialTrayCount + 1);
    assert(tryTray[tryTray.count() - 1] == expectedCard);
}

/**
 * Runs all tests for the hand class.
 *
 * Outputs to the console the name of the test being run, and whether all tests
 * passed or not.
 */
int main()
{
    std::cout << "Running hand tests...\n";
    
    test_hand_construction();
    test_hand_refill();
    test_hand_selection();
    test_hand_discard_to_tray();
    
    std::cout << "All hand tests passed!\n";

    // Deprecated test: user interaction
    int iChoice = 0;
    deck dckDeck;
    hand hndHand(dckDeck);

    std::cout << std::endl << "\t" << hndHand << std::endl << std::endl;
    std::cout << "\tPlease choose a card (0 to 3):\t";
    std::cin >> iChoice;

    hndHand.select(iChoice);
    std::cout << std::endl << std::endl << "\tYou've chosen:\t" << hndHand.discard() << std::endl << std::endl;
 
    return 0;
}

