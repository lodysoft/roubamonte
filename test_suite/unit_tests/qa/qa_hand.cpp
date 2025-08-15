#define BOOST_TEST_MODULE HandTests
#include <boost/test/included/unit_test.hpp>

// Quality assurance tests for hand class functionality

#include <stdexcept>                                                        // std::out_of_range
#include <iostream>                                                         // std::cout, std::cerr
#include <exception>                                                        // std::exception

#include "../../../include/deck.h"
#include "../../../include/hand.h"
#include "../../../include/tray.h"

BOOST_AUTO_TEST_CASE(test_hand_construction)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    BOOST_CHECK_EQUAL(hndHand.count(), 4);
    BOOST_CHECK(!hndHand.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_hand_refill)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    tray tryTray(dckDeck);                                                  // Discard all cards
    for(int i = 0; i < 4; i++)
{
        hndHand.select(0);
        hndHand.discard();
    }
    
    BOOST_CHECK(hndHand.isEmpty());
    
    // Refill
    hndHand.refill(dckDeck);
    BOOST_CHECK_EQUAL(hndHand.count(), 4);
}

BOOST_AUTO_TEST_CASE(test_hand_selection)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    BOOST_CHECK_NO_THROW(hndHand.select(3));                               // Test valid selection
    BOOST_CHECK_THROW(hndHand.select(4), std::out_of_range);               // Test invalid selection
}

BOOST_AUTO_TEST_CASE(test_hand_discard_to_tray)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    hand hndHand(dckDeck);
    
    int initialTrayCount = tryTray.count();
    card expectedCard = hndHand[0];
    
    hndHand.select(0);
    hndHand.discard(tryTray);
    
    BOOST_CHECK_EQUAL(hndHand.count(), 3);                                  // One card discarded from initial 4
    BOOST_CHECK_EQUAL(tryTray.count(), initialTrayCount + 1);
    BOOST_CHECK(tryTray[tryTray.count() - 1] == expectedCard);              // Use boolean comparison instead
}

BOOST_AUTO_TEST_CASE(test_hand_boundary_conditions)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Test valid boundary selections
    BOOST_CHECK_NO_THROW(hndHand.select(0));                               // First card
    BOOST_CHECK_NO_THROW(hndHand.select(hndHand.count() - 1));             // Last card
    
    // Test invalid boundary selections
    BOOST_CHECK_THROW(hndHand.select(-1), std::out_of_range);              // Negative index
    BOOST_CHECK_THROW(hndHand.select(hndHand.count()), std::out_of_range); // Index == size
}

BOOST_AUTO_TEST_CASE(test_hand_state_consistency)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Test that hand maintains consistent state
    int initialCount = hndHand.count();
    BOOST_CHECK_EQUAL(initialCount, 4);                                     // Standard hand size
    
    // Test that selecting and discarding reduces count correctly
    hndHand.select(1);
    hndHand.discard();
    BOOST_CHECK_EQUAL(hndHand.count(), initialCount - 1);
    
    // Test that we can continue operations on reduced hand
    BOOST_CHECK(!hndHand.isEmpty());
    BOOST_CHECK_NO_THROW(hndHand.select(0));                                // Should still work
}

// Boost Test framework automatically generates main() and manages test execution

