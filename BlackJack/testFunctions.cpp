//
//  testFunctions.cpp
//  BlackJack
//
//  Created by Leeran on 2016-03-18.
//  Copyright © 2016 Compulsive Gamblers inc. All rights reserved.
//

#include "testFunctions.hpp"

void testHands() {
    std::vector<Card> cardsforHand1 { {5, spades}, {10, hearts} };
    Hand hand(cardsforHand1);
    GamePlayer player;
    DealerPlayer dealer;
    Deck deck(1);
    
    player.addCardToHandFromDeck(cardsforHand1[0], 0);
    player.addCardToHandFromDeck(cardsforHand1[1], 0);
    //add hands to player
    std::cout << player;
}

void testPlayer() {
    
    std::cout << "Testing PLAYER V.2" << std::endl;
    
    Player *player = new Player(false); //playercount should be 0
    
    std::cout << "Player count after making new player:  " << Player::_playerCount << std::endl;
    
    GamePlayer gPlayer;  // playercount should be 1
    
    //player->setInSession(true);
    
    std::vector<Card> cards { {5, spades}, {8, diamonds}, {4, clubs}, {10, hearts} };
    std::cout << "<Player pre card assignment: " << std::endl << *player << std::endl;
    player->addCardToHandFromDeck(cards[0]);
    player->addCardToHandFromDeck(cards[1]);
    player->addCardToHandFromDeck(cards[2], 1);
    player->addCardToHandFromDeck(cards[3], 2);
    std::cout << "Now clearing players hands with clearHand(): " << std::endl;
    player->removeCardsFromHand(2, 0);
    std::cout << std::endl << *player << "!!!!!!!!!!End Player!!!!!!!!!! > " << std::endl << std::endl;
    
    std::cout << "gPlayer: " << gPlayer << std::endl;
    std::cout << "Players name:" << gPlayer.getName(false) << std::endl;
    gPlayer.addCardToHandFromDeck(cards[3]); //hand0
    gPlayer.addCardToHandFromDeck(cards[2]); //hand0
    gPlayer.addCardToHandFromDeck(cards[1], 1);
    gPlayer.addCardToHandFromDeck(cards[0], 2);
    std::cout  << gPlayer << "!!!!!!!!!!End gPlayer!!!!!!!!!! >" << std::endl;
    
    std::cout << "ASSIGNING player = &gplayer" << std::endl;
    player = nullptr;
    player = &gPlayer;
    std::cout << "<Player: " << *player << std::endl;
    std::cout << "Adding a card to players hand through *player: " << std::endl;
    player->addCardToHandFromDeck(cards[0], 2);
    std::cout << "After adding card[0]: " << cards[0] << " to hand2: " << std::endl;
    std::cout << *player << std::endl;
    std::cout << "Printing gPlayer after player=gplayer assingment and after displaying *player, should have same result." << std::endl;
    std::cout << gPlayer << "!!!!!!!!!!End ASSIGNING player = &gplayer!!!!!!!!!! >" << std::endl;
    
    
    std::cout << "Player count: " << Player::_playerCount << std::endl;
    std::cout << "DELETING PLAYER!!!" << std::endl;
    player = NULL;
    delete player;
    
    std::cout << "*player should have been deleted." << std::endl;
    std::cout << "Player count: " << Player::_playerCount << std::endl;
    
    std::cout << "Testing new gPlayer2 without empty parameters: " << std::endl;
    GamePlayer gPlayer2; //playercount should be 2
    std::cout << "Players name:" << gPlayer2.getName(false) << std::endl;
    std::cout << "Adding a card to gPlayer2 (card[1](8diamonds)) " << std::endl;
    gPlayer2.addCardToHandFromDeck(cards[1]);
    std::cout << "gPlayer2: " << gPlayer2 << std::endl;
    std::cout << "Player count is now " << Player::_playerCount << std::endl;
    std::cout << gPlayer2 << "!!!!!!!!!!End Testing new gPlayer2 without empty parameters: !!!!!!!!!! >" << std::endl;
    
    std::cout << "Adding another GamePlayer" << std::endl;
    GamePlayer gPlayer3;
    std::cout << "Player count is now " << Player::_playerCount << std::endl;
    
    std::cout << "Merging 3 players and dealer into <players>" << std::endl;
    
    std::vector<Player*> players;
    players.push_back(&gPlayer);
    players.push_back(&gPlayer2);
    players.push_back(&gPlayer3);
    
    std::cout << "<players>.size = " << players.size() << " = " << Player::_playerCount << " (Player::_playerCount)" << std::endl;
    std::cout << "Showing all players from loop..." << std::endl;
    
    DealerPlayer dealer;
    players.push_back(&dealer);
    std::cout << "Added dealer." << std::endl;
    std::cout << "Player count is now " << Player::_playerCount << std::endl;
    std::cout << "Adding cards to dealer (card[1](8diamonds), card[0](5spades) " << std::endl;
    dealer.addCardToHandFromDeck(cards[1]);
    dealer.addCardToHandFromDeck(cards[0]);
    
    //dealer.addCardToHandFromDeck(cards[0], 1); //should crash with error message
    std::cout << dealer << std::endl;
    
    gPlayer.setInSession(false);
    
    for (auto player: players) {
        std::cout << "Players name:" << player->getName(false) << std::endl;
        std::cout << *player <<std::endl;
        
    }
}

void testAskForInsurance() {
    Game game;
    std::vector<GamePlayer*> gPlayers;
    DealerPlayer dealer;
    dealer.addCardToHandFromDeck(Card(1, spades));
    dealer.addCardToHandFromDeck(Card(10, spades));
    std::cout << (game.isInsuranceRequired(gPlayers, dealer.getHand(0)) ? "DEBUG isInsuranceRequired: TRUE" : "DEBUG isInsuranceRequired: FALSE") << std::endl;
}

void testInsurance() {
    Game game;
    std::vector<GamePlayer*> gPlayers;
    DealerPlayer dealer;
    dealer.addCardToHandFromDeck(Card(1, spades));
    dealer.addCardToHandFromDeck(Card(10, spades));
    std::cout << (game.isInsuranceRequired(gPlayers, dealer.getHand(0)) ? "DEBUG testInsurance: TRUE" : "DEBUG isInsuranceRequired: FALSE") << std::endl;
    
    gPlayers.push_back(new GamePlayer());
    gPlayers[0]->setPreBetMoney();
    std::cout << "PLAYER CREATED" << std::endl << *gPlayers[0] << std::endl;
    
    
    gPlayers[0]->addCardToHandFromDeck(Card(2, spades));
    gPlayers[0]->addCardToHandFromDeck(Card(10, hearts));
    game.getBetsFromAllPlayers(gPlayers);
    
    std::cout << "Testing bets: " << std::endl;
    //gPlayers[0]->setMoney(500);
    //gPlayers[0]->setBet(450);
    std::cout << "Players name is " << gPlayers[0]->getName() << std::endl;
    std::cout << "Players money set to " << gPlayers[0]->getMoney() << std::endl;
    std::cout << "Players bet set to " << gPlayers[0]->getBet() << std::endl;
    
    std::cout << "Printing player: \n" <<  *gPlayers[0] << std::endl;
    game.getInsuranceFromPlayer(*gPlayers[0]);
    std::cout << game.insurancePayout(gPlayers, dealer.getHand(0)) << std::endl;
    
    std::cout << "Printing player after insurance payout: \n" <<  *gPlayers[0] << std::endl;
}

void testMenu() {
    std::vector<std::string> options { "string1", "string2", "string3" };
    std::string header = "title";
    Menu menu(header,  options);
    std::cout << menu.displayAndGetChoice() << std::endl;
    
}
