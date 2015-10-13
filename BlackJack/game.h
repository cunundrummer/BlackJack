//
//  game.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-28.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__game__
#define __BlackJack__game__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "player.h"
#include "gamePlayer.h"
#include "dealerPlayer.h"
#include "deck.h"
#include "menu.h"


class Game {
private:
    const std::string _GAME_TITLE = "BLACKJACK";
    const int _MIN_DECKS_TO_USE = 1;
    const int _MAX_DECKS_TO_USE = 8;
    const int _MAX_CHARACTERS_FOR_NAME = 15;
    const int _MAX_GAMEPLAYERS_ALLOWED = 5;
    const int MIN_ALLOWABLE_BET = 5;
    const int MAX_ALLOWABLE_BET = 500;
    
    bool _isDemoMode;
    bool _dealStart = true; //For dealing 2 cards at first(if true) and for dealers special case; false will deal only 1 card to each player including dealer
    int _numPlayers;
    int _insuranceFlags;
    
    Deck *_deck;
    std::vector<Player*> _players;

public:
    std::string generateName(std::string); //private
    Game(bool isDemoMode = true, int numPlayers = 5) : _isDemoMode(isDemoMode), _numPlayers(numPlayers) {};
    
    //void retrievePlayers(std::vector<Player*> &p) {  p = _players; }
    /*
    std::string getGameTitle()      { return _GAME_TITLE; }
    int getMinDecksToUse()          { return _MIN_DECKS_TO_USE; }
    int getMaxDecksToUse()          { return _MAX_DECKS_TO_USE; }
    Deck getDeck()                  { return *_deck; }
    bool getIsInDemoMode()          { return _isDemoMode; }
    void setIsDemoMode(bool);
    
    int getMaxCharactersForName()   { return _MAX_CHARACTERS_FOR_NAME; }
    void setUpPlayers(std::vector<GamePlayer*> &);
    int getNumPlayers()             { return _numPlayers; }
    void setNumPlayers(int);
    
    void displayHelp();
    
    void setupDeck(int);
    void dealCard(Player &, bool faceUp);
    void dealCardToAllPlayers(std::vector<Player*>, bool faceUp);
    
    void getBetsFromAllPlayers(std::vector<GamePlayer*> &);
    void getBetFromPlayer(GamePlayer &);
    void setDealStart(bool tf) { _dealStart = tf; }
    bool getDealStart() { return _dealStart; }
    
    bool getInsuranceFlag() { return _insuranceFlags; }
    void setInsuranceFlag(int flag) { _insuranceFlags = flag; }
    void getInsuranceFromPlayers(std::vector<GamePlayer*> &);
    void getInsuranceFromPlayer(GamePlayer &);
    
    int phase1(std::vector<GamePlayer*> &, Hand); // returns 0 for game goes on; 1 ask for insurance; 2 dealer has blackjack
    int buildPlayOptionForPlayerAndReturnChoice(GamePlayer &gPlayer);
    
    void hit(Player &p);
    void stand();
    void double_down();
    void split();
    
    void printGame(std::vector<GamePlayer*> &, DealerPlayer) const;
    void showDebug();
    //~Game() { delete _dealer; }
*/
};

#endif /* defined(__BlackJack__game__) */
