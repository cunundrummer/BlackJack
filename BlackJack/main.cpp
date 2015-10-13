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
enum PLAY_OPTIONS {HIT, STAND, DOUBLE_DOWN, SPLIT};
//const int MIN_AMOUNT_OF_MONEY = 5;
//const int BLACKJACK_FLAG = 21;
//const int GAME_GOES_ON_FLAG = 0;
//const int ASK_FOR_INSURANCE_FLAG = 1;

void testMenu();
void testPlayer();

int main(int argc, const char * argv[]) {
    testPlayer();
 /*
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
    DealerPlayer dealer;
    game.setUpPlayers(gPlayers);
    std::cout << "Dealers name is " << dealer << std::endl;
    ////////Making a vector for all player objects for ease of use in certain methods/functions
    std::vector<Player*> players(gPlayers.begin(), gPlayers.end());
    players.push_back(&dealer);
    ///////////////////////////////////////////////////////////////////////////////////////////
    

    std::cout << "Dealers name is " << dealer << std::endl;
    //testing std::cout << "Player1 name is " << *gPlayers[0] << std::endl;

    std::cout << "Player setup phaze complete." << std::endl;
    std::cout << "Added dealer to players list." << std::endl;
    std::cout << "Building cards...deck(s)..." << std::endl;
    //std::cout << "There are a total of " << players.size() << " players on the table. " << std::endl;
    
    game.setupDeck(2);
    std::cout << std::endl;
    std::cout << "GAME BEGINS, asking players for bets..." << std::endl;

    //game.getBetsFromAllPlayers(gPlayers);
    
    if (game.getDealStart()) { //deal only 2 cards for start, dealers second card will be masked
        game.dealCardToAllPlayers(players, true);
        game.dealCardToAllPlayers(players, true);
        game.setDealStart(false); //game started, must be reset to false when round is over
        
        /*phase1 is the start of the game; with checking dealers hand, and insurance phase

        int gameFlag = game.phase1(gPlayers, dealer.getHand()); //check dealers hand to see if players need to be asked for insurance
        std::cout << "Gameflag is " << printFlag(gameFlag) << std::endl;
        
        std::cout << "Checking play options for players, i.e. Double down/Split/Surrender/Hit" << std::endl;
        int choice = game.buildPlayOptionForPlayerAndReturnChoice(*gPlayers[0]);

        switch (choice) {
            case PLAY_OPTIONS::HIT:
                //add card from deck to players hand
                std::cout << "Player chose to hit." << std::endl;
                gPlayers[0]->hit(game.getDeck().removeLastCard());
                break;
            case PLAY_OPTIONS::STAND:
                std::cout << "Player chose to stand." << std::endl;
                //pause players session
                gPlayers[0]->stand();
                break;
            case PLAY_OPTIONS::DOUBLE_DOWN:
                //bet equivalent of another bet and pause players session
                std::cout << "Player chose to double down." << std::endl;
                break;
            case PLAY_OPTIONS::SPLIT:
                // create another hand from players second card and bet equivalent of another bet.  play hand to completion then play other hand splits allowed upto 4 times.  optional: allow double after splits
                std::cout << "Player chose to split." << std::endl;
                break;
            default:
                std::cout << "Unknown error in switch(choice)...exiting";
                exit(9);
                break;
        }
        
    }
    
    //todo: test phase1
    
    
    game.printGame(gPlayers, dealer);*/
    return 0;
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
    std::cout << "<Player pre card assignment: " << *player << std::endl;
    player->addCardToHandFromDeck(cards[0]);
    player->addCardToHandFromDeck(cards[1]);
    player->addCardToHandFromDeck(cards[2], 1);
    player->addCardToHandFromDeck(cards[3], 2);
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

void testMenu() {
    std::vector<std::string> options { "string1", "string2", "string3" };
    std::string header = "title";
    Menu menu(header,  options);
    std::cout << menu.displayAndGetChoice() << std::endl;

}
