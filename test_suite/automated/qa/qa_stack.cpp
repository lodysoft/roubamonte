#define BOOST_TEST_MODULE StackTests
#include <boost/test/included/unit_test.hpp>

// Quality assurance tests for stack class functionality

#include <stdexcept>                                                        // std::out_of_range
#include <iostream>                                                         // std::cout, std::cerr
#include <exception>                                                        // std::exception

#include "../../../include/stack.h"

BOOST_AUTO_TEST_CASE(test_stack_construction)
{
    stack stkStack;
    
    BOOST_CHECK_EQUAL(stkStack.count(), 0);
    BOOST_CHECK(stkStack.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_stack_push_operations)
{
    stack stkStack;
    card crdCard(ACE, SPADES);
    
    stkStack.push(crdCard);
    
    BOOST_CHECK_EQUAL(stkStack.count(), 1);
    BOOST_CHECK(!stkStack.isEmpty());
    BOOST_CHECK(stkStack.top() == crdCard);
}

BOOST_AUTO_TEST_CASE(test_stack_pop_operations)
{
    stack stkStack;
    card crdCard1(ACE, SPADES);
    card crdCard2(KING, HEARTS);
    
    stkStack.push(crdCard1);
    stkStack.push(crdCard2);
    
    BOOST_CHECK_EQUAL(stkStack.count(), 2);
    
    card crdPopped = stkStack.pop();
    BOOST_CHECK(crdPopped == crdCard2);                                     // LIFO - last in, first out
    BOOST_CHECK_EQUAL(stkStack.count(), 1);
    
    crdPopped = stkStack.pop();
    BOOST_CHECK(crdPopped == crdCard1);
    BOOST_CHECK_EQUAL(stkStack.count(), 0);
    BOOST_CHECK(stkStack.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_stack_top_method)
{
    stack stkStack;
    card crdCard1(QUEEN, DIAMONDS);
    card crdCard2(JACK, CLUBS);
    
    stkStack.push(crdCard1);
    stkStack.push(crdCard2);
    
    BOOST_CHECK(stkStack.top() == crdCard2);                                // top() should return last pushed card
    BOOST_CHECK_EQUAL(stkStack.count(), 2);                                 // top() should not modify the stack
}

BOOST_AUTO_TEST_CASE(test_stack_lifo_behavior)
{
    stack stkStack;
    card crdCards[5] = {
        card(ACE, SPADES),
        card(2, HEARTS),
        card(KING, DIAMONDS),
        card(QUEEN, CLUBS),
        card(JACK, SPADES)
    };
    
    // Push cards in order
    for(int i = 0; i < 5; i++)
    {
        stkStack.push(crdCards[i]);
    }
    
    BOOST_CHECK_EQUAL(stkStack.count(), 5);
    
    // Pop cards and verify LIFO order
    for(int i = 4; i >= 0; i--)
    {
        card crdPopped = stkStack.pop();
        BOOST_CHECK(crdPopped == crdCards[i]);                              // Should come out in reverse order
    }
    
    BOOST_CHECK(stkStack.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_stack_multiple_pushes_and_pops)
{
    stack stkStack;
    card crdCard1(ACE, SPADES);
    card crdCard2(KING, HEARTS);
    card crdCard3(QUEEN, DIAMONDS);
    
    // Test interleaved push/pop operations
    stkStack.push(crdCard1);
    BOOST_CHECK_EQUAL(stkStack.count(), 1);
    
    stkStack.push(crdCard2);
    BOOST_CHECK_EQUAL(stkStack.count(), 2);
    
    card crdPopped = stkStack.pop();
    BOOST_CHECK(crdPopped == crdCard2);
    BOOST_CHECK_EQUAL(stkStack.count(), 1);
    
    stkStack.push(crdCard3);
    BOOST_CHECK_EQUAL(stkStack.count(), 2);
    BOOST_CHECK(stkStack.top() == crdCard3);
}

BOOST_AUTO_TEST_CASE(test_stack_consistency)
{
    stack stkStack;
    
    // Test that isEmpty() is consistent with count()
    BOOST_CHECK(stkStack.isEmpty() == (stkStack.count() == 0));
    
    card crdCard(ACE, SPADES);
    stkStack.push(crdCard);
    
    BOOST_CHECK(stkStack.isEmpty() == (stkStack.count() == 0));
    BOOST_CHECK(!stkStack.isEmpty());
    BOOST_CHECK(stkStack.count() > 0);
}

// Boost Test framework automatically generates main() and manages test execution