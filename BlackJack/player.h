//
//  player.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-29.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__player__
#define __BlackJack__player__

#include <iostream>
#include <string>
#include <iomanip>
#include "input.h"
#include "hand.h"
#include "deck.h"
#include "debug.hpp"

class Player {
private:
    
    bool _nameIsSet;
    bool _inSession;
    
protected:
    int _MAX_CHARACTERS_ALLOWED = 15;
    std::string _name;
    double _money;
    const size_t MAX_HANDS_ALLOWED_TO_HOLD_;
    std::vector<Hand> hands_;
    void setMAX_CARDS_TO_HOLD(const size_t NUMBER_OF_HANDS);
    bool inSessionFlag_;    //togo: might place in hands | might also need one for player instance
    
    virtual void init(bool inSessionFlag = true);
    
public:
    static int _playerCount;
    friend std::ostream& operator<< (std::ostream &os, Player &p);
    
    Player() = delete;
    Player(bool toIncludeInCount = false);
    Player(std::string name, const int MAX_CHARACTERS, double money, const size_t MAX_NUMBER_HAND_TO_HOLD, bool toIncludeInCount, bool inSession); //set name only, left out bool to allow for auto/default name
    
    int getPlayerCount();
    void setPlayerCount(int count);
    
    virtual void setName(std::string&, const int  MAX_CHARACTERS);
    std::string getName(bool showErrMsg = false); //bool for showing error message
        
    virtual void setInSession(bool flag)        { inSessionFlag_ = _inSession = flag; } //remove reudundant _inSession
    bool isInSession()              { return _inSession; } //should be renamed getSessionFlag/fast ugly hack: make method and call it?
    
    virtual void setMoney(double money);
    virtual double getMoney();
    
    void addCardToHandFromDeck(Card, size_t index = 0);
    void removeCardsFromHand(int numCards, size_t index);
    
    void setHands(std::vector<Hand>& hands);
    
    Hand& getHand(int index = 0);/* { return hands_[index] ; }*/
    //Hand getHand(/*const int index = 0*/);
    std::vector<Hand>& getHands() { return hands_; }
    void displayHand();
    virtual void print();
    
    virtual void hit(Card card, int index);
    virtual void stand();
    virtual void doubleDown();
    //virtual void split();
    
    virtual void playHand(Deck& deck); //auto play hand
    
};

#endif /* defined(__BlackJack__player__) */
