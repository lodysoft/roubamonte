#define BOOST_TEST_MODULE SelectionContainerTests
#include <boost/test/included/unit_test.hpp>

// Quality assurance tests for selection_container class functionality

#include <stdexcept>                                                                // std::out_of_range
#include <iostream>                                                                 // std::cout, std::cerr
#include <exception>                                                                // std::exception

#include "../../../include/deck.h"
#include "../../../include/hand.h"
#include "../../../include/tray.h"

// Note: selection_container is abstract, so we test it through its concrete derived classes (hand and tray)

BOOST_AUTO_TEST_CASE(test_selection_container_through_hand)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Test basic selection_container interface through hand
    BOOST_CHECK_EQUAL(hndHand.count(), 4);                                          // Hand starts with 4 cards
    BOOST_CHECK(!hndHand.isEmpty());
    
    // Test selection functionality
    BOOST_CHECK_NO_THROW(hndHand.select(0));                                        // Should be able to select first card
    BOOST_CHECK_NO_THROW(hndHand.select(3));                                        // Should be able to select last card
}

BOOST_AUTO_TEST_CASE(test_selection_container_through_tray)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    // Test basic selection_container interface through tray
    BOOST_CHECK_EQUAL(tryTray.count(), 8);                                          // Tray starts with 8 cards
    BOOST_CHECK(!tryTray.isEmpty());
    
    // Test selection functionality
    BOOST_CHECK_NO_THROW(tryTray.select(0));                                        // Should be able to select first card
    BOOST_CHECK_NO_THROW(tryTray.select(7));                                        // Should be able to select last card
}

BOOST_AUTO_TEST_CASE(test_selection_container_indexing)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Test indexing operator
    BOOST_CHECK_NO_THROW(hndHand[0]);                                               // Should be able to access first card
    BOOST_CHECK_NO_THROW(hndHand[3]);                                               // Should be able to access last card
    
    // Test that indexing returns actual cards
    card crdFirst = hndHand[0];
    
    BOOST_CHECK_EQUAL(crdFirst.figure(), hndHand[0].figure());                      // Should return consistent results
    BOOST_CHECK_EQUAL(crdFirst.suit(), hndHand[0].suit());
}

BOOST_AUTO_TEST_CASE(test_selection_container_boundary_conditions)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Test valid boundary conditions
    BOOST_CHECK_NO_THROW(hndHand.select(0));                                        // First valid index
    BOOST_CHECK_NO_THROW(hndHand.select(hndHand.count() - 1));                      // Last valid index
    
    // Test invalid boundary conditions
    BOOST_CHECK_THROW(hndHand.select(-1), std::out_of_range);                       // Negative index
    BOOST_CHECK_THROW(hndHand.select(hndHand.count()), std::out_of_range);          // Index == count
    BOOST_CHECK_THROW(hndHand.select(hndHand.count() + 1), std::out_of_range);      // Index > count
}

BOOST_AUTO_TEST_CASE(test_selection_container_indexing_boundaries)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    // Test valid indexing boundaries
    BOOST_CHECK_NO_THROW(tryTray[0]);                                               // First valid index
    BOOST_CHECK_NO_THROW(tryTray[tryTray.count() - 1]);                             // Last valid index
    
    // Test invalid indexing boundaries
    BOOST_CHECK_THROW(tryTray[-1], std::out_of_range);                              // Negative index
    BOOST_CHECK_THROW(tryTray[tryTray.count()], std::out_of_range);                 // Index == count
}

BOOST_AUTO_TEST_CASE(test_selection_container_refill_behavior)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Remove all cards from hand
    for(int i = 0; i < 4; i++)
    {
        hndHand.select(0);
        hndHand.discard();
    }
    
    BOOST_CHECK(hndHand.isEmpty());
    BOOST_CHECK_EQUAL(hndHand.count(), 0);
    
    // Test refill functionality
    hndHand.refill(dckDeck);
    
    BOOST_CHECK(!hndHand.isEmpty());
    BOOST_CHECK_EQUAL(hndHand.count(), 4);                                          // Should be back to initial count
}

BOOST_AUTO_TEST_CASE(test_selection_container_consistency)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Test that isEmpty() is consistent with count()
    BOOST_CHECK(hndHand.isEmpty() == (hndHand.count() == 0));
    
    // Test after removing cards
    hndHand.select(0);
    hndHand.discard();
    
    BOOST_CHECK(hndHand.isEmpty() == (hndHand.count() == 0));
    
    // Continue until empty
    while(!hndHand.isEmpty())
    {
        hndHand.select(0);
        hndHand.discard();
    }
    
    BOOST_CHECK(hndHand.isEmpty());
    BOOST_CHECK_EQUAL(hndHand.count(), 0);
}

BOOST_AUTO_TEST_CASE(test_selection_container_polymorphic_behavior)
{
    deck dckDeck;
    hand hndHand(dckDeck);
    tray tryTray(dckDeck);
    
    // Test that both derived classes implement the interface correctly
    selection_container* pselHand = &hndHand;
    selection_container* pselTray = &tryTray;
    
    BOOST_CHECK_NO_THROW(pselHand->count());
    BOOST_CHECK_NO_THROW(pselHand->isEmpty());
    BOOST_CHECK_NO_THROW(pselHand->select(0));
    BOOST_CHECK_NO_THROW((*pselHand)[0]);
    
    BOOST_CHECK_NO_THROW(pselTray->count());
    BOOST_CHECK_NO_THROW(pselTray->isEmpty());
    BOOST_CHECK_NO_THROW(pselTray->select(0));
    BOOST_CHECK_NO_THROW((*pselTray)[0]);
}

BOOST_AUTO_TEST_CASE(test_selection_container_different_initial_sizes)
{
    deck dckDeck;
    hand hndHand(dckDeck);                                                          // Should start with 4 cards
    tray tryTray(dckDeck);                                                          // Should start with 8 cards
    
    // Test that different derived classes have different initial sizes
    BOOST_CHECK_EQUAL(hndHand.count(), 4);
    BOOST_CHECK_EQUAL(tryTray.count(), 8);
    
    // Test that they maintain their respective sizes after refill
    hndHand.select(0);
    hndHand.discard();
    hndHand.refill(dckDeck);
    BOOST_CHECK_EQUAL(hndHand.count(), 4);                                          // Should return to 4
    
    // Note: tray doesn't lose cards through normal selection, it grows with receive_discard
}

// Boost Test framework automatically generates main() and manages test execution