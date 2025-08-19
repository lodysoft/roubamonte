#define BOOST_TEST_MODULE DeckTests
#include <boost/test/included/unit_test.hpp>

// Quality assurance tests for deck class functionality

#include <stdexcept>                                                        // std::out_of_range
#include <iostream>                                                         // std::cout, std::cerr
#include <exception>                                                        // std::exception
#include <set>                                                              // std::set

#include "../../../include/deck.h"

BOOST_AUTO_TEST_CASE(test_deck_construction)
{
    deck dckDeck;
    
    BOOST_CHECK_EQUAL(dckDeck.count(), 54);                                 // Standard deck: 52 cards + 2 jokers
    BOOST_CHECK(!dckDeck.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_deck_shuffle_randomness)
{
    deck dckDeck1;
    deck dckDeck2;
    
    // Two shuffled decks should be different (extremely unlikely to be identical)
    // We'll compare the top cards since we can't peek at arbitrary positions
    BOOST_CHECK(!(dckDeck1.top() == dckDeck2.top()));                       // Top cards should be different
}

BOOST_AUTO_TEST_CASE(test_deck_completeness)
{
    deck dckDeck;
    std::set<std::pair<int, int>> cardSet;
    
    // Collect all cards from deck
    while(!dckDeck.isEmpty())
    {
        card crdCurrent = dckDeck.pop();
        std::pair<int, int> cardPair = std::make_pair(crdCurrent.figure(), crdCurrent.suit());
        cardSet.insert(cardPair);
    }
    
    BOOST_CHECK_EQUAL(cardSet.size(), 54);                                  // Should have exactly 54 unique cards
}

BOOST_AUTO_TEST_CASE(test_deck_inheritance_from_stack)
{
    deck dckDeck;
    
    BOOST_CHECK_NO_THROW(dckDeck.count());                                  // Should have stack methods
    BOOST_CHECK_NO_THROW(dckDeck.isEmpty());
    BOOST_CHECK_NO_THROW(dckDeck.top());
    
    int initialCount = dckDeck.count();
    card crdTop = dckDeck.pop();
    BOOST_CHECK_EQUAL(dckDeck.count(), initialCount - 1);                   // Pop should work
}

BOOST_AUTO_TEST_CASE(test_deck_standard_cards_present)
{
    deck dckDeck;
    std::set<std::pair<int, int>> foundCards;
    
    // Extract all cards and check for standard deck contents
    while(!dckDeck.isEmpty())
    {
        card crdCurrent = dckDeck.pop();
        foundCards.insert(std::make_pair(crdCurrent.figure(), crdCurrent.suit()));
    }
    
    // Check for jokers
    BOOST_CHECK(foundCards.count(std::make_pair(JOKER, RED)) == 1);         // Red joker present
    BOOST_CHECK(foundCards.count(std::make_pair(JOKER, BLACK)) == 1);       // Black joker present
    
    // Check for aces in all suits
    BOOST_CHECK(foundCards.count(std::make_pair(ACE, SPADES)) == 1);
    BOOST_CHECK(foundCards.count(std::make_pair(ACE, HEARTS)) == 1);
    BOOST_CHECK(foundCards.count(std::make_pair(ACE, DIAMONDS)) == 1);
    BOOST_CHECK(foundCards.count(std::make_pair(ACE, CLUBS)) == 1);
    
    // Check for kings in all suits
    BOOST_CHECK(foundCards.count(std::make_pair(KING, SPADES)) == 1);
    BOOST_CHECK(foundCards.count(std::make_pair(KING, HEARTS)) == 1);
    BOOST_CHECK(foundCards.count(std::make_pair(KING, DIAMONDS)) == 1);
    BOOST_CHECK(foundCards.count(std::make_pair(KING, CLUBS)) == 1);
}

BOOST_AUTO_TEST_CASE(test_deck_operations)
{
    deck dckDeck;
    
    // Test basic stack operations work correctly
    int initialCount = dckDeck.count();
    card crdFirst = dckDeck.top();
    card crdPopped = dckDeck.pop();
    
    BOOST_CHECK(crdFirst == crdPopped);                                     // top() and pop() should return same card
    BOOST_CHECK_EQUAL(dckDeck.count(), initialCount - 1);                   // Count should decrease
    
    // Test push operation
    dckDeck.push(crdPopped);
    BOOST_CHECK_EQUAL(dckDeck.count(), initialCount);                       // Count should be restored
    BOOST_CHECK(dckDeck.top() == crdPopped);                                // Top card should be the pushed card
}

// Boost Test framework automatically generates main() and manages test execution