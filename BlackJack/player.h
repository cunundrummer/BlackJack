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
    const size_t MAX_HANDS_ALLOWED_TO_HOLD_;
    std::vector<Hand> hands_;
    void setMAX_CARDS_TO_HOLD(const size_t NUMBER_OF_HANDS);
    //bool _inSession;
    
public:
    static int _playerCount;
    friend std::ostream& operator<< (std::ostream &os, Player &p);
    
    Player() = delete;
    Player(bool toIncludeInCount = false);
    Player(std::string name, const int MAX_CHARACTERS, double money, const size_t MAX_NUMBER_HAND_TO_HOLD, bool toIncludeInCount, bool inSession); //set name only, left out bool to allow for auto/default name
    
    int getPlayerCount();
    void setPlayerCount(int count);
    
    virtual void setName(std::string&, const int  MAX_CHARACTERS);
    std::string getName(bool showErrMsg); //bool for showing error message
    
    //void setNameIsSet(bool TrueOrFalse);
    //bool getNameIsSet() { return _nameIsSet; }
    
    virtual void setMoney(double money);
    virtual double getMoney();
    
    void addCardToHandFromDeck(Card, size_t index = 0);
    void removeCardsFromHand(int numCards, size_t index);
    
    std::vector<Hand>& getHand() { return hands_ ; }
    Hand getHand(const int index = 0)
    {
        if (hands_.empty()) {
            Hand hand;
            hands_.push_back(hand);
        }
        return hands_.at(index);
    }
    void displayHand();
    
    bool isInSession() { return _inSession; }
    void setInSession(bool session) { _inSession = session; }
    
    virtual void print();
    virtual void hit(Card card);
    void stand();
};

#endif /* defined(__BlackJack__player__) */
