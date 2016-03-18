//
//  main.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-28.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//
/*
 -consider using a debug flag, so if there is an if DEBUG then all debug statements would be shown
 */
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
#include "dealerPlayer.h"
#include "menu.h"
#include "player.h"
#include "testFunctions.hpp"

const bool DEBUGGING = false;  //this will be used for debug statements, not yet incorporated
const int GAME_GOES_ON_FLAG = 0;

int Player::_playerCount = 0;

void showAllPlayers(std::vector<Player*> players, bool showOnePlayer = true, int playerToShowIndex = 0);
int calculatePlayerResult(GamePlayer& g);

int main(int argc, const char * argv[]) {
    
    Game game(false, 1); // default is demo mode(false)

    std::cout << "***** " << game.getGameTitle() << " *****" << std::endl;
    game.setIsDemoMode(promptUserForDemoMode());
    
    if (game.getIsInDemoMode() == true ) {
        std::cout << "Demo mode. Only computer(5) players will be playing." << std::endl;
    }
    else {
        std::cout << "Player setup..." << std::endl;
    }
    
    std::vector<GamePlayer*> gPlayers;
    std::cout << "DEBUG: Main: Entering player setup..." << std::endl;
    game.setUpPlayers(gPlayers);
    
    DealerPlayer dealer;
    std::cout << "Dealers name is " << std::endl << dealer << std::endl;
    
    ////////Making a vector for all player objects for ease of use in certain methods/functions
    std::vector<Player*> players(gPlayers.begin(), gPlayers.end());
    players.push_back(&dealer);
    std::cout << "DEBUG: Testing all players including dealer..." << std::endl;
    
    std::cout << "END OF DEBUG: Testing all players including dealer..." << std::endl;
    ///////////////////////////////////////////////////////////////////////////////////////////
    
    std::cout << "Player setup phaze complete." << std::endl;
    std::cout << "Added dealer to players list." << std::endl;
    std::cout << "Building cards...deck(s)..." << std::endl;
    
    game.setupDeck(2);
    std::cout << std::endl;
    
    do {
        std::cout << "GAME BEGINS, asking players for bets..." << std::endl;

        game.getBetsFromAllPlayers(gPlayers);
        std::cout << "Bets have been taken, dealing cards to players..." << std::endl;
        
        if (game.getDealStart()) { //deal only 2 cards for start, dealers second card will be masked
            game.dealCardToAllPlayers(players, true);
            game.dealCardToAllPlayers(players, true);
        }
        else {
            game.dealCardToAllPlayers(players, true);
        }
        
        setPlayersHandForTesting(dealer, 5, Suits::clubs, 2, Suits::spades);
        setPlayersHandForTesting(*gPlayers[0], 10, Suits::spades, 5, Suits::hearts);
        
        if (game.isInsuranceRequired(gPlayers, dealer.getHand()/* dealersHand*/)) {
            game.getInsuranceFromPlayers(gPlayers);
        }
    
        game.setDealStart(false); //game started, must be reset to false when round is over
        int gameFlag = game.insurancePayout(gPlayers, dealer.getHand()); //1. detects and pays/deducts insurance if players chose insurance. 2.Returns blackjack for quick startover in case no game can be played.
        std::cout << "\nGameflag is " << printFlag(gameFlag) << std::endl;
    
        if (gameFlag == BLACKJACK) {
            std::cout << "DEBUG: Main: Dealer has blackjack, prepping new round..." << std::endl;
            game.getQuitAnswer();
            
        }
        else { //GAME_GOES_ON
            //start for loop for all players here
            if (gPlayers[0]->isInSession()) {
                //build options for players still in session
                std::cout << "Checking play options for players, i.e. Double down/Split/Surrender/Hit" << std::endl;  //maybe check if player has bj first
                //std::cout << *gPlayers[0] << std::endl;
                std::cout << "Dealers hand is " << dealer.getHand() << std::endl;
                std::cout << gPlayers[0]->getName() << "'s hand is " << std::endl;
                Hand h(gPlayers[0]->getHand());
                std::cout << h << std::endl;
                
                int choice = gPlayers[0]->buildPlayOptionForPlayerAndReturnChoice();
                //playout choice selection
                game.resolveChoice(choice, *gPlayers[0]);
            
                std::cout << gPlayers[0]->getName() << " 's session: ";
                (gPlayers[0]->isInSession()) ?  std::cout << "TRUE" << std::endl :  std::cout << "FALSE"  << std::endl;
                std::cout << "Player has " << gPlayers[0]->getHands().size() << " hands." << std::endl;
                //compare hands here
                switch (game.comparePlayerHands(gPlayers[0]->getHand(), dealer.getHand())) {
                    case 0: //push //HANDS_ARE_EQUAL
                        game.payout(PUSH, *gPlayers[0]);
                        std::cout << "PUSH!!!" << std::endl;
                        break;
                    case 1: //pay player  //HAND1_IS_GREATER
                        std::cout << gPlayers[0]->getName() << " 's hand is > then dealer" << std::endl;
                        game.payout(WIN, *gPlayers[0]);
                        break;
                    case 2:  //remove bet from player //HAND2_IS_GREATER
                        std::cout << gPlayers[0]->getName() << " 's hand is < dealers hand" << std::endl;
                        //std::cout << "DEBUG: MAIN: swCASE 2: money is $" << gPlayers[0]->getMoney() << std::endl;
                        game.payout(LOSE, *gPlayers[0]);
                        //money already deducted with bet
                        break;
                    case 3: //HAND1_IS_BUSTED
                        std::cout << "Player busted!" << std::endl;
                       // std::cout << "DEBUG: MAIN: swCASE 3: money is $" << gPlayers[0]->getMoney() << std::endl;
                        game.payout(BUST, *gPlayers[0]);
                        //money already deducted with bet
                        break;
                    case 21: //TWENTY_ONE
                        std::cout << "Blackjack!!!, paying at 3:2!" << std::endl;
                        game.payout(BLACK_JACK, *gPlayers[0]);
                    default:
                        std::cout << "An oddity occurred, mostly and error." << std::endl;
                        break;
                }
            }
            
        }
        
        //players = game.preparePlayersForNewRound(players);
        game.preparePlayersForNewRound(gPlayers, dealer);
        game.setDealStart(true);
        game.getQuitAnswer();
    } while (game.getQuitSentinal() == false);
        
    std::cout << std::endl << std::endl << "****************************" << std::endl;
    std::cout << "DEBUG: MAIN: showing all players..." << std::endl;
    showAllPlayers(players);
    std::cout << "DEBUG: MAIN: showing player1" << std::endl;
    std::cout << *gPlayers[0] << std::endl;
    std::cout << "END OF DEBUG MAIN" << std::endl;
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

/**
    Shows player information.
 
    @param players players is All player types
 
    @param showOnePlayer Option to display all players or just one with optional index. Default is true.

    @param index if showing just one players, show player at index. Default is 0.
*/
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

