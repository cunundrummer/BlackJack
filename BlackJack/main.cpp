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
#include "dealerPlayer.h"
#include "menu.h"
#include "player.h"
#include "testFunctions.hpp"
#include "debug.hpp"

const int GAME_GOES_ON_FLAG = 0;

int Player::_playerCount = 0;

void showAllPlayers(std::vector<Player*> players, bool showOnePlayer = true, int playerToShowIndex = 0);
int calculatePlayerResult(GamePlayer& g);

int main(int argc, const char * argv[]) {
    
    if (DEBUGGING) {
        std::cout << "Debugging mode!" << std::endl;
    }
    
    Game game(false, 2); // default is demo mode(false)

    std::cout << "***** " << game.getGameTitle() << " *****" << std::endl;
    game.setIsDemoMode(promptUserForDemoMode());
    
    if (game.getIsInDemoMode() == true ) {
        std::cout << "Demo mode. Only computer(5) players will be playing." << std::endl;
    }
    else {
        std::cout << "Player setup..." << std::endl;
    }
    
    std::vector<GamePlayer*> gPlayers;
    (DEBUGGING) ? std::cout << "DEBUG: Main: Entering player setup..." << std::endl : std::cout << std::endl;
    game.setUpPlayers(gPlayers);
    
    DealerPlayer dealer;
    std::cout << "Dealers name is " << std::endl << dealer << std::endl;
    
    ////////Making a vector for all player objects for ease of use in certain methods/functions
    std::vector<Player*> players(gPlayers.begin(), gPlayers.end());
    players.push_back(&dealer);
    if (DEBUGGING) {
        std::cout << "DEBUG: Testing all players including dealer..." << std::endl;
        
        std::cout << "END OF DEBUG: Testing all players including dealer..." << std::endl;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    
    std::cout << "Player setup phaze complete." << std::endl;
    std::cout << "Added dealer to players list." << std::endl;
    std::cout << "Building cards...deck(s)..." << std::endl;
    
    game.setupDeck(2,true);
    std::cout << std::endl;
    
    do {
        std::cout << "GAME BEGINS, asking players for bets..." << std::endl;

        game.getBetsFromAllPlayers(gPlayers);
        std::cout << "Bets have been taken, dealing cards to players...\n" << std::endl;
        
        if (game.getDealStart()) { //deal only 2 cards for start, dealers second card will be masked
            game.dealCardToAllPlayers(players, true);
            game.dealCardToAllPlayers(players, true);
        }
        else {
            game.dealCardToAllPlayers(players, true);
        }
        
        /*
        // these 2 statements are for debugging purposes only
        //setPlayersHandForTesting(dealer, 2, Suits::clubs, 3, Suits::spades);
        //setPlayersHandForTesting(*gPlayers[0], 5, Suits::spades, 5, Suits::hearts);
        */
       
        if (game.isInsuranceRequired(gPlayers, dealer.getHand()/* dealersHand*/)) {
            game.getInsuranceFromPlayers(gPlayers);
        }
    
        game.setDealStart(false); //game started, must be reset to false when round is over
        int gameFlag = game.insurancePayout(gPlayers, dealer.getHand()); //1. detects and pays/deducts insurance if players chose insurance. 2.Returns blackjack for quick startover in case no game can be played.
        
        if (DEBUGGING) {
            std::cout << "\nGameflag is " << printFlag(gameFlag) << std::endl;
        }
        
        if (gameFlag == BLACKJACK) {
            if (DEBUGGING) {
                std::cout << "DEBUG: Main: Dealer has blackjack, prepping new round..." << std::endl;
            }
            //check players hand for blackjack(push)
            for (auto player: gPlayers) {
            
                if (game.comparePlayerHands(player->getHand(), dealer.getHand()) == 0) {
                    std::cout << "Dealer and player have BJ. It's a push... " << std::endl;
                    std::cout << "Dealers hand: " << dealer.getHand() << std::endl;
                    std::cout << player->getName() << "'s hand: " << player->getHand() << std::endl;
                }
            }
            game.getQuitAnswer();
            
        }
        else { //GAME_GOES_ON
            //start for loop for all players here
            for (int playerIndex = 0; playerIndex < gPlayers.size(); playerIndex++) {
                
                if (gPlayers[playerIndex]->isInSession()) {
                    
                    std::cout << "Checking play options for player " << gPlayers[playerIndex]->getName() <<
                    ", i.e. Double down/Split/Surrender/Hit" << std::endl;  //maybe check if player has bj first
                    
                    std::cout << "Dealers hand is " << dealer.getHand() << std::endl;
                    std::cout << gPlayers[playerIndex]->getName() << "'s hand is " << gPlayers[playerIndex]->getHand() << std::endl;
                    
                    int choice = gPlayers[playerIndex]->buildPlayOptionForPlayerAndReturnChoice();
                    game.resolveChoice(choice, *gPlayers[playerIndex]);
                    //All players should have finished playing there hands by now. Next step is to play the dealers hand and then payouts
                    
                    
                }//end of if (inSession)
                else {
                    std::cout << gPlayers[playerIndex]->getName() << " out of session" << std::endl;
                }
                
            }//end of for (playercount...)
            dealer.playHand(game.getDeck());
            for (int playerIndex = 0; playerIndex < gPlayers.size(); playerIndex++) {
                for (int i = 0; i < gPlayers[playerIndex]->getHands().size(); i++) {
                    
                    const int HAND1_IS_GREATER = 1;
                    const int HAND2_IS_GREATER = 2;
                    const int HANDS_ARE_EQUAL = 0;
                    const int TWENTY_ONE = 21;
                    if (gPlayers[playerIndex]->getHand(i).getBustedFlag() == true || gPlayers[playerIndex]->getHand(i).getSimpleLossFlag() == true) {
                        game.payout(LOSE, *gPlayers[0], i);
                    }
                    else if (gPlayers[playerIndex]->getHand(i).getStandFlag()) { //out of place
                        std::cout << "Dealers hand is " << dealer.getHand();
                        std::cout << gPlayers[playerIndex]->getName() << " hand[" << i << "] is " << gPlayers[playerIndex]->getHand(i) << std::endl;
                        switch (game.comparePlayerHands(gPlayers[playerIndex]->getHand(i), dealer.getHand())) {
                                
                            case HAND1_IS_GREATER:
                                game.payout(WIN, *gPlayers[playerIndex], i);
                                break;
                            case HAND2_IS_GREATER:
                                if (dealer.getHand().getBustedFlag()) {
                                    game.payout(WIN, *gPlayers[playerIndex], i);
                                }
                                else {
                                    game.payout(LOSE, *gPlayers[playerIndex], i);
                                }
                                break;
                            case HANDS_ARE_EQUAL:
                                game.payout(PUSH, *gPlayers[playerIndex], i);
                                break;
                            case TWENTY_ONE:
                                game.payout(WIN, *gPlayers[playerIndex], i);
                                break;
                            default:
                                break;
                        }
                    }
                    else {
                        std::cout << "Error in main: else if standFlag" << std::endl;
                        exit(9);
                    }
                }
            }
            
        }//end of else
        
        game.preparePlayersForNewRound(gPlayers, dealer);
        game.setDealStart(true);
        game.getQuitAnswer();
        
    } while (game.getQuitSentinal() == false);
    
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

