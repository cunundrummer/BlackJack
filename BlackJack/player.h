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

class Player {
private:

    bool _nameIsSet;
    bool _inSession;
    
protected:
    int _MAX_CHARACTERS_ALLOWED = 15;
    std::string _name;
    double _money;
    //Hand hands_; //only dealer?
    std::vector<Hand> hands_; //only gameplayer?
    //Hands(Gameplayer allowed 4 hand[4 splits], Dealer only allowed 1)
    
public:
    static int _playerCount;
    friend std::ostream& operator<< (std::ostream &os, Player &p);
    
    Player();
    Player(std::string, int, double, bool); //set name only, left out bool to allow for auto/default name
    
    int getPlayerCount();
    void setPlayerCount(int);
    
    void setName(std::string, const int);
    std::string getName(bool); //boolfor showing error message

    void setNameIsSet(bool TrueOrFalse);
    bool getNameIsSet() { return _nameIsSet; }
    
    void setInSession(bool TrueOrFalse) { _inSession = TrueOrFalse; }
    bool getInSession() { return _inSession; }
    
    void setMoney(double);
    double getMoney();
    
    //Hand getHand() { return hands_; }
    
    void displayHand();
    void addCardToHandFromDeck(Card);
    void addCardToHandFromDeck(Card cardToAdd, int handIndex = 0);
    void removeCardsFromHand(int numCards);
    //virtual void getHand(Hand &hand, int index);
    Hand getHand(int index);
    //void getAllHands(std::vector<Hand>& hands) { hands_=hands; }
    virtual void print() {
        std::cout << "Base";
    }
    
    virtual void hit(Card card);
    void stand();
    //void stand();
    
};

#endif /* defined(__BlackJack__player__) */
