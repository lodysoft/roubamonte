#define BOOST_TEST_MODULE PlayerTests
#include <boost/test/included/unit_test.hpp>

// Quality assurance tests for player class functionality

#include <stdexcept>                                                                // std::out_of_range
#include <iostream>                                                                 // std::cout, std::cerr
#include <exception>                                                                // std::exception

#include "../../../include/deck.h"
#include "../../../include/player.h"

BOOST_AUTO_TEST_CASE(test_player_construction)
{
    deck dckDeck;
    player plyPlayer(dckDeck);
    
    BOOST_CHECK_EQUAL(plyPlayer.getHand().count(), 4);                              // Player should start with 4 cards in hand
    BOOST_CHECK_EQUAL(plyPlayer.getStack().count(), 0);                             // Player should start with empty stack
    BOOST_CHECK(plyPlayer.getStack().isEmpty());
}

BOOST_AUTO_TEST_CASE(test_player_hand_access)
{
    deck dckDeck;
    player plyPlayer(dckDeck);
    
    hand& hndPlayerHand = plyPlayer.getHand();
    
    BOOST_CHECK_EQUAL(hndPlayerHand.count(), 4);                                    // Should have access to hand
    BOOST_CHECK(!hndPlayerHand.isEmpty());
    
    // Test that we can use hand methods
    BOOST_CHECK_NO_THROW(hndPlayerHand.select(0));
    BOOST_CHECK_NO_THROW(hndPlayerHand.discard());
    BOOST_CHECK_EQUAL(hndPlayerHand.count(), 3);                                    // Hand should have one less card
}

BOOST_AUTO_TEST_CASE(test_player_stack_access)
{
    deck dckDeck;
    player plyPlayer(dckDeck);
    
    stack& stkPlayerStack = plyPlayer.getStack();
    
    BOOST_CHECK(stkPlayerStack.isEmpty());
    BOOST_CHECK_EQUAL(stkPlayerStack.count(), 0);
    
    // Test adding card to stack
    card crdTestCard(ACE, SPADES);
    stkPlayerStack.push(crdTestCard);
    
    BOOST_CHECK(!stkPlayerStack.isEmpty());
    BOOST_CHECK_EQUAL(stkPlayerStack.count(), 1);
    BOOST_CHECK(stkPlayerStack.top() == crdTestCard);
}

BOOST_AUTO_TEST_CASE(test_player_steal_mechanism)
{
    deck dckDeck;
    player plyPlayer1(dckDeck);
    player plyPlayer2(dckDeck);
    
    // Add some cards to player2's stack
    card crdCard1(ACE, SPADES);
    card crdCard2(KING, HEARTS);
    card crdCard3(QUEEN, DIAMONDS);
    
    plyPlayer2.getStack().push(crdCard1);
    plyPlayer2.getStack().push(crdCard2);
    plyPlayer2.getStack().push(crdCard3);
    
    int player1InitialCount = plyPlayer1.getStack().count();
    int player2InitialCount = plyPlayer2.getStack().count();
    int player1InitialHandCount = plyPlayer1.getHand().count();
    
    // Player1 needs to select a card before stealing
    plyPlayer1.getHand().select(0);
    
    // Player1 steals from Player2
    plyPlayer1.steal(plyPlayer2);
    
    // steal() moves player2's stack + adds player1's selected card
    BOOST_CHECK_EQUAL(plyPlayer1.getStack().count(), player1InitialCount + player2InitialCount + 1);
    BOOST_CHECK_EQUAL(plyPlayer2.getStack().count(), 0);                            // Player2 should have empty stack
    BOOST_CHECK(plyPlayer2.getStack().isEmpty());
    BOOST_CHECK_EQUAL(plyPlayer1.getHand().count(), player1InitialHandCount - 1);   // Player1 should have one less card in hand
}

BOOST_AUTO_TEST_CASE(test_player_steal_empty_stack)
{
    deck dckDeck;
    player plyPlayer1(dckDeck);
    player plyPlayer2(dckDeck);
    
    // Both players start with empty stacks
    BOOST_CHECK(plyPlayer1.getStack().isEmpty());
    BOOST_CHECK(plyPlayer2.getStack().isEmpty());
    
    // Player1 needs to select a card before stealing
    plyPlayer1.getHand().select(0);
    
    // Stealing from empty stack should not cause problems
    BOOST_CHECK_NO_THROW(plyPlayer1.steal(plyPlayer2));
    
    BOOST_CHECK_EQUAL(plyPlayer1.getStack().count(), 1);                            // Player1 should have 1 card (the discarded one)
    BOOST_CHECK(plyPlayer2.getStack().isEmpty());                                   // Player2 should still have empty stack
}

BOOST_AUTO_TEST_CASE(test_player_independence)
{
    deck dckDeck;
    player plyPlayer1(dckDeck);
    player plyPlayer2(dckDeck);
    
    // Players should have independent hands and stacks
    card crdTestCard(JACK, CLUBS);
    plyPlayer1.getStack().push(crdTestCard);
    
    BOOST_CHECK_EQUAL(plyPlayer1.getStack().count(), 1);
    BOOST_CHECK_EQUAL(plyPlayer2.getStack().count(), 0);                            // Player2 should not be affected
    
    // Test hand independence
    plyPlayer1.getHand().select(0);
    plyPlayer1.getHand().discard();
    
    BOOST_CHECK_EQUAL(plyPlayer1.getHand().count(), 3);
    BOOST_CHECK_EQUAL(plyPlayer2.getHand().count(), 4);                             // Player2 hand should not be affected
}

BOOST_AUTO_TEST_CASE(test_player_state_consistency)
{
    deck dckDeck;
    player plyPlayer(dckDeck);
    
    // Test that player maintains consistent state
    int initialHandCount = plyPlayer.getHand().count();
    int initialStackCount = plyPlayer.getStack().count();
    
    BOOST_CHECK_EQUAL(initialHandCount, 4);                                         // Standard hand size
    BOOST_CHECK_EQUAL(initialStackCount, 0);                                        // Empty stack initially
    
    // After various operations, state should remain consistent
    plyPlayer.getHand().select(1);
    card crdDiscarded = plyPlayer.getHand().discard();
    plyPlayer.getStack().push(crdDiscarded);
    
    BOOST_CHECK_EQUAL(plyPlayer.getHand().count(), initialHandCount - 1);
    BOOST_CHECK_EQUAL(plyPlayer.getStack().count(), initialStackCount + 1);
}

// Boost Test framework automatically generates main() and manages test execution