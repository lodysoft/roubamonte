#define BOOST_TEST_MODULE TrayTests
#include <boost/test/included/unit_test.hpp>

// Quality assurance tests for tray class functionality

#include <stdexcept>                                                        // std::out_of_range
#include <iostream>                                                         // std::cout, std::cerr
#include <set>                                                              // std::set
#include <exception>                                                        // std::exception

#include "../../../include/deck.h"
#include "../../../include/tray.h"

BOOST_AUTO_TEST_CASE(test_tray_construction)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    BOOST_CHECK_EQUAL(tryTray.count(), 8);                                  // Standard tray initial size
    BOOST_CHECK(!tryTray.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_tray_refill_behavior)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    std::set<card> initialCards;                                            // Remember initial cards
    
    for(int i = 0; i < tryTray.count(); i++) 
	{
        initialCards.insert(tryTray[i]);
    }
    
    tryTray.refill(dckDeck);                                                // Refill shouldn't change cards
    
    for(int i = 0; i < tryTray.count(); i++)                                // Verify same cards remain
	{
        BOOST_CHECK(initialCards.find(tryTray[i]) != initialCards.end());
    }
}

BOOST_AUTO_TEST_CASE(test_tray_selection)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    BOOST_CHECK_NO_THROW(tryTray.select(0));                               // Valid selection
    BOOST_CHECK_NO_THROW(tryTray.select(tryTray.count() - 1));
    BOOST_CHECK_THROW(tryTray.select(tryTray.count()), std::out_of_range); // Invalid selection
}

BOOST_AUTO_TEST_CASE(test_tray_receive_discard)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    int initialCount = tryTray.count();
    card testCard(HEARTS, ACE);
    
    tryTray.receive_discard(testCard);
    
    BOOST_CHECK_EQUAL(tryTray.count(), initialCount + 1);
    BOOST_CHECK(tryTray[tryTray.count() - 1] == testCard);                  // Use boolean comparison instead
}

BOOST_AUTO_TEST_CASE(test_tray_boundary_conditions)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    // Test valid boundary selections
    BOOST_CHECK_NO_THROW(tryTray.select(0));                               // First card
    BOOST_CHECK_NO_THROW(tryTray.select(tryTray.count() - 1));             // Last card
    
    // Test invalid boundary selections
    BOOST_CHECK_THROW(tryTray.select(-1), std::out_of_range);              // Negative index
    BOOST_CHECK_THROW(tryTray.select(tryTray.count()), std::out_of_range); // Index == size
}

BOOST_AUTO_TEST_CASE(test_tray_dynamic_growth)
{
    deck dckDeck;
    tray tryTray(dckDeck);
    
    int initialCount = tryTray.count();
    
    // Add multiple cards to test growth
    card testCard1(ACE, CLUBS);
    card testCard2(KING, DIAMONDS);
    card testCard3(QUEEN, SPADES);
    
    tryTray.receive_discard(testCard1);
    tryTray.receive_discard(testCard2);
    tryTray.receive_discard(testCard3);
    
    BOOST_CHECK_EQUAL(tryTray.count(), initialCount + 3);
    BOOST_CHECK(!tryTray.isEmpty());
    
    // Verify we can still select from expanded tray
    BOOST_CHECK_NO_THROW(tryTray.select(tryTray.count() - 1));             // Should work with grown tray
}

// Boost Test framework automatically generates main() and manages test execution

