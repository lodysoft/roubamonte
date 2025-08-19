#define BOOST_TEST_MODULE TableTests
#include <boost/test/included/unit_test.hpp>

// Quality assurance tests for table class functionality

#include <stdexcept>                                                        // std::out_of_range
#include <iostream>                                                         // std::cout, std::cerr
#include <exception>                                                        // std::exception

#include "../../../include/deck.h"
#include "../../../include/table.h"

BOOST_AUTO_TEST_CASE(test_table_default_construction)
{
    table tblTable;
    
    BOOST_CHECK_EQUAL(tblTable.getPlayers().size(), 2);                     // Default 2 players
    BOOST_CHECK_EQUAL(tblTable.getTray().count(), TABLE_INITIAL_CARDS);     // Tray should have 8 cards initially
    BOOST_CHECK(!tblTable.getTray().isEmpty());
}

BOOST_AUTO_TEST_CASE(test_table_custom_player_count)
{
    table tblTable3(3);
    table tblTable4(4);
    
    BOOST_CHECK_EQUAL(tblTable3.getPlayers().size(), 3);                    // Should have 3 players
    BOOST_CHECK_EQUAL(tblTable4.getPlayers().size(), 4);                    // Should have 4 players
    
    // All players should have proper hand size
    for(auto& plyPlayer : tblTable3.getPlayers())
    {
        BOOST_CHECK_EQUAL(plyPlayer.getHand().count(), 4);                  // Each player should have 4 cards
        BOOST_CHECK(plyPlayer.getStack().isEmpty());                        // Each player should start with empty stack
    }
}

BOOST_AUTO_TEST_CASE(test_table_tray_access)
{
    table tblTable;
    
    tray& tryTableTray = tblTable.getTray();
    
    BOOST_CHECK_EQUAL(tryTableTray.count(), TABLE_INITIAL_CARDS);
    BOOST_CHECK(!tryTableTray.isEmpty());
    
    // Test that we can use tray methods
    BOOST_CHECK_NO_THROW(tryTableTray.select(0));
    
    // Test adding card to tray
    card crdTestCard(ACE, SPADES);
    tryTableTray.receive_discard(crdTestCard);
    BOOST_CHECK_EQUAL(tryTableTray.count(), TABLE_INITIAL_CARDS + 1);
}

BOOST_AUTO_TEST_CASE(test_table_players_access)
{
    table tblTable(3);
    
    std::vector<player>& players = tblTable.getPlayers();
    
    BOOST_CHECK_EQUAL(players.size(), 3);
    
    // Test that all players are properly initialized
    for(size_t i = 0; i < players.size(); i++)
    {
        BOOST_CHECK_EQUAL(players[i].getHand().count(), 4);                 // Each player should have 4 cards in hand
        BOOST_CHECK(players[i].getStack().isEmpty());                       // Each player should have empty stack
    }
    
    // Test that players are independent
    players[0].getHand().select(0);
    players[0].getHand().discard();
    
    BOOST_CHECK_EQUAL(players[0].getHand().count(), 3);                     // Player 0 should have 3 cards
    BOOST_CHECK_EQUAL(players[1].getHand().count(), 4);                     // Player 1 should still have 4 cards
    BOOST_CHECK_EQUAL(players[2].getHand().count(), 4);                     // Player 2 should still have 4 cards
}

BOOST_AUTO_TEST_CASE(test_table_deck_access)
{
    table tblTable;
    
    const deck& dckTableDeck = tblTable.getDeck();
    
    // Deck should exist and have remaining cards after table initialization
    BOOST_CHECK(!dckTableDeck.isEmpty());
    
    // Calculate expected remaining cards: 54 total - (2 players * 4 cards) - 8 tray cards = 38
    int expectedRemainingCards = 54 - (2 * 4) - TABLE_INITIAL_CARDS;
    BOOST_CHECK_EQUAL(dckTableDeck.count(), expectedRemainingCards);
}

BOOST_AUTO_TEST_CASE(test_table_card_distribution)
{
    table tblTable(4);                                                      // 4 players
    
    // Check total card distribution
    int totalDistributedCards = 0;
    
    // Count cards in players' hands
    for(auto& plyPlayer : tblTable.getPlayers())
    {
        totalDistributedCards += plyPlayer.getHand().count();
    }
    
    // Count cards in tray
    totalDistributedCards += tblTable.getTray().count();
    
    // Count remaining cards in deck
    totalDistributedCards += tblTable.getDeck().count();
    
    BOOST_CHECK_EQUAL(totalDistributedCards, 54);                           // Should account for all 54 cards
}

BOOST_AUTO_TEST_CASE(test_table_initialization_consistency)
{
    table tblTable1(2);
    table tblTable2(2);
    
    // Both tables should have same structure but different card distributions
    BOOST_CHECK_EQUAL(tblTable1.getPlayers().size(), tblTable2.getPlayers().size());
    BOOST_CHECK_EQUAL(tblTable1.getTray().count(), tblTable2.getTray().count());
    
    // But cards should be shuffled differently (extremely unlikely to be identical)
    bool bSameTray = true;
    for(int i = 0; i < tblTable1.getTray().count() && bSameTray; i++)
    {
        if(!(tblTable1.getTray()[i] == tblTable2.getTray()[i]))
        {
            bSameTray = false;
        }
    }
    BOOST_CHECK(!bSameTray);                                                // Trays should have different card arrangements
}

BOOST_AUTO_TEST_CASE(test_table_player_interaction)
{
    table tblTable;
    
    std::vector<player>& players = tblTable.getPlayers();
    tray& tryTray = tblTable.getTray();
    
    // Test player discarding to tray
    players[0].getHand().select(0);
    card crdDiscarded = players[0].getHand().discard();
    
    int initialTrayCount = tryTray.count();
    tryTray.receive_discard(crdDiscarded);
    
    BOOST_CHECK_EQUAL(tryTray.count(), initialTrayCount + 1);
    BOOST_CHECK_EQUAL(players[0].getHand().count(), 3);                     // Player should have one less card
}

// Boost Test framework automatically generates main() and manages test execution