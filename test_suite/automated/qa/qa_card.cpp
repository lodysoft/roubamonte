#define BOOST_TEST_MODULE CardTests
#include <boost/test/included/unit_test.hpp>

// Quality assurance tests for card class functionality

#include <stdexcept>                                                        // std::out_of_range
#include <iostream>                                                         // std::cout, std::cerr
#include <exception>                                                        // std::exception

#include "../../../include/card.h"

BOOST_AUTO_TEST_CASE(test_card_construction)
{
    card crdCard(ACE, SPADES);
    
    BOOST_CHECK_EQUAL(crdCard.figure(), ACE);
    BOOST_CHECK_EQUAL(crdCard.suit(), SPADES);
}

BOOST_AUTO_TEST_CASE(test_card_copy_constructor)
{
    card crdOriginal(KING, HEARTS);
    card crdCopy(crdOriginal);
    
    BOOST_CHECK_EQUAL(crdCopy.figure(), KING);
    BOOST_CHECK_EQUAL(crdCopy.suit(), HEARTS);
    BOOST_CHECK(crdCopy == crdOriginal);
}

BOOST_AUTO_TEST_CASE(test_card_assignment_operator)
{
    card crdCard1(QUEEN, DIAMONDS);
    card crdCard2(JACK, CLUBS);
    
    crdCard2 = crdCard1;
    
    BOOST_CHECK_EQUAL(crdCard2.figure(), QUEEN);
    BOOST_CHECK_EQUAL(crdCard2.suit(), DIAMONDS);
    BOOST_CHECK(crdCard2 == crdCard1);
}

BOOST_AUTO_TEST_CASE(test_card_equality_operator)
{
    card crdCard1(ACE, SPADES);
    card crdCard2(ACE, SPADES);
    card crdCard3(ACE, HEARTS);
    
    BOOST_CHECK(crdCard1 == crdCard2);                                      // Same figure and suit
    BOOST_CHECK(!(crdCard1 == crdCard3));                                   // Same figure, different suit
}

BOOST_AUTO_TEST_CASE(test_card_less_than_operator)
{
    card crdLow(2, SPADES);
    card crdHigh(KING, SPADES);
    card crdDifferentSuit(2, HEARTS);
    
    BOOST_CHECK(crdLow < crdHigh);                                          // Lower figure should be less than higher (same suit)
    BOOST_CHECK(!(crdHigh < crdLow));                                       // Higher should not be less than lower (same suit)
    
    // Test suit comparison (SPADES=0, HEARTS=1, DIAMONDS=2, CLUBS=3)
    BOOST_CHECK(crdLow < crdDifferentSuit);                                 // SPADES < HEARTS
}

BOOST_AUTO_TEST_CASE(test_card_jokers)
{
    card crdRedJoker(JOKER, RED);
    card crdBlackJoker(JOKER, BLACK);
    
    BOOST_CHECK_EQUAL(crdRedJoker.figure(), JOKER);
    BOOST_CHECK_EQUAL(crdRedJoker.suit(), RED);
    BOOST_CHECK_EQUAL(crdBlackJoker.figure(), JOKER);
    BOOST_CHECK_EQUAL(crdBlackJoker.suit(), BLACK);
    BOOST_CHECK(!(crdRedJoker == crdBlackJoker));                           // Different jokers should not be equal
}

BOOST_AUTO_TEST_CASE(test_card_boundary_figures)
{
    card crdJoker(JOKER, SPADES);
    card crdAce(ACE, SPADES);
    card crdJack(JACK, SPADES);
    card crdQueen(QUEEN, SPADES);
    card crdKing(KING, SPADES);
    
    BOOST_CHECK_EQUAL(crdJoker.figure(), JOKER);
    BOOST_CHECK_EQUAL(crdAce.figure(), ACE);
    BOOST_CHECK_EQUAL(crdJack.figure(), JACK);
    BOOST_CHECK_EQUAL(crdQueen.figure(), QUEEN);
    BOOST_CHECK_EQUAL(crdKing.figure(), KING);
}

BOOST_AUTO_TEST_CASE(test_card_all_suits)
{
    card crdSpades(ACE, SPADES);
    card crdHearts(ACE, HEARTS);
    card crdDiamonds(ACE, DIAMONDS);
    card crdClubs(ACE, CLUBS);
    
    BOOST_CHECK_EQUAL(crdSpades.suit(), SPADES);
    BOOST_CHECK_EQUAL(crdHearts.suit(), HEARTS);
    BOOST_CHECK_EQUAL(crdDiamonds.suit(), DIAMONDS);
    BOOST_CHECK_EQUAL(crdClubs.suit(), CLUBS);
}

// Boost Test framework automatically generates main() and manages test execution