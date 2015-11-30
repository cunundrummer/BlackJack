//
//  main.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-28.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "input.h"
#include "prompts.h"
#include "game.h"
#include "player.h"
#include "card.h"
#include "cardpile.h"
#include "hand.h"
#include "deck.h"
#include "gamePlayer.h"
#include "menu.h"
#include "player.h"

int Player::_playerCount = 0;
//int Player::_player2Count = 0;

//const int MIN_AMOUNT_OF_MONEY = 5;
//const int BLACKJACK_FLAG = 21;
const int GAME_GOES_ON_FLAG = 0;
const int NEXT_GAME = 99;
//const int ASK_FOR_INSURANCE_FLAG = 1;

void testMenu();
void testPlayer();
void testAskForInsurance();
void showAllPlayers(std::vector<Player*> players, bool showOnePlayer = true, int playerToShowIndex = 0);
int calculatePlayerResult(GamePlayer& g);

int main(int argc, const char * argv[]) {
    
    Game game; // default is demo mode(false)

    std::cout << "***** " << game.getGameTitle() << " *****" << std::endl;
    game.setIsDemoMode(promptUserForDemoMode());
    
    if (game.getIsInDemoMode() == true ) {
        std::cout << "Demo mode. Only computer(5) players will be playing." << std::endl;
    }
    else {
        std::cout << "Player setup..." << std::endl;
    }
    
    std::vector<GamePlayer*> gPlayers;
    game.setUpPlayers(gPlayers);
    
    DealerPlayer dealer;
    std::cout << "Dealers name is " << std::endl << dealer << std::endl;
    
    ////////Making a vector for all player objects for ease of use in certain methods/functions
    std::vector<Player*> players(gPlayers.begin(), gPlayers.end());
    players.push_back(&dealer);
    std::cout << "DEBUG: Testing all players including dealer..." << std::endl;
    //showAllPlayers(players);
    std::cout << "END OF DEBUG: Testing all players including dealer..." << std::endl;
    ///////////////////////////////////////////////////////////////////////////////////////////
    
    std::cout << "Player setup phaze complete." << std::endl;
    std::cout << "Added dealer to players list." << std::endl;
    std::cout << "Building cards...deck(s)..." << std::endl;
    
    game.setupDeck(2);
    std::cout << std::endl;
    std::cout << "GAME BEGINS, asking players for bets..." << std::endl;

    game.getBetsFromAllPlayers(gPlayers);
    
    if (game.getDealStart()) { //deal only 2 cards for start, dealers second card will be masked
        game.dealCardToAllPlayers(players, true);
        game.dealCardToAllPlayers(players, true);

        //phase1 is the start of the game; with checking dealers hand, and insurance phase
        Hand dealersHand = dealer.getHand(0);
        if (game.isInsuranceRequired(gPlayers, dealersHand)) {
            game.getInsuranceFromPlayers(gPlayers);
        }
        
        game.setDealStart(false); //game started, must be reset to false when round is over
        int gameFlag = game.insurancePayout(gPlayers, dealersHand); //detects and pays/deducts insurance if players chose insurance
        std::cout << "Gameflag is " << printFlag(gameFlag) << std::endl;
        
        if (gameFlag == GAME_GOES_ON_FLAG) {
            do { //move do to better location after implementing split
                //build options for players still in session
                std::cout << "Checking play options for players, i.e. Double down/Split/Surrender/Hit" << std::endl;
                std::cout << *gPlayers[0] << std::endl;
            
                gPlayers[0]->removeCardsFromHand(2, 0); //temp to test splits
                gPlayers[0]->addCardToHandFromDeck(Card(5, spades));//temp to test splits
                gPlayers[0]->addCardToHandFromDeck(Card(5, hearts));//temp to test splits
                Hand h(gPlayers[0]->getHand(0));
                std::cout << h << std::endl;
                int choice = gPlayers[0]->buildPlayOptionForPlayerAndReturnChoice();
                //playout choice selection
                game.resolveChoice(choice, *gPlayers[0]);
                
                std::cout << gPlayers[0]->getName() << " 's session: ";
                (gPlayers[0]->isInSession())?  std::cout << "TRUE" << std::endl :  std::cout << "FALSE"  << std::endl;
                
                
                std::cout << "@END OF DO WHILE LOOP" << std::endl;
                //start from here next programming session!!!!
                
            } while (gPlayers[0]->isInSession() == true);
        }
        else { //gameflag == BLACKJACK_FLAG
            //reinit players, if players are out of session, they are out
            
        }
    }

    std::cout << std::endl << std::endl << "****************************" << std::endl;
    showAllPlayers(players, true);
    std::cout << "****************************" << std::endl;
    
    return 0;
}

int calculatePlayerResult(GamePlayer& g) {
    int total = g.getHand(0).calculate();
    
    if (total > 21) {
        //g.setBustedFlag(true);
        g.setInSession(false);
        return BUSTED;
    }
    else if (total == 21) {
        //g.setBlackjackFlag(true);
        //g.setInSession(false);
        return BLACKJACK;
    }
    else {
        //check if player has enough money to play
        g.setInSession(true);
        return GAME_GOES_ON_FLAG;
    }

    //return 0;
}

void showAllPlayers(std::vector<Player*> players, bool showOnePlayer, int index) {
    
    if (showOnePlayer == true) {
        std::cout << "DEBUG: showAllPlayers...for player[" << index << "]"  << std::endl;
        std::cout << *players[index] << std::endl;
    }
    else {
        std::cout << "DEBUG: showAllPlayers..." << std::endl;
        size_t i  = 0;
        for (auto player: players) {
            std::cout << "(index" << i << ") " << "(PLAYER" << i + 1 << ")" << std::endl;
            std::cout << *player << std::endl;
            i++;
        }
    }
    std::cout << "END OF DEBUG: showAllPlayers" << std::endl;
}

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
    dealer.addCardToHandFromDeck(Card(9, spades));
    dealer.addCardToHandFromDeck(Card(9, spades));
    std::cout << (game.isInsuranceRequired(gPlayers, dealer.getHand(0)) ? "DEBUG isInsuranceRequired: TRUE" : "DEBUG isInsuranceRequired: FALSE") << std::endl;
}

void testMenu() {
    std::vector<std::string> options { "string1", "string2", "string3" };
    std::string header = "title";
    Menu menu(header,  options);
    std::cout << menu.displayAndGetChoice() << std::endl;

}
