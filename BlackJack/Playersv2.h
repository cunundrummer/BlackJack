//
//  Playersv2.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-10-08.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__Playersv2__
#define __BlackJack__Playersv2__

#include <iostream>
#include <string>
#include <iomanip>
#include "input.h"
#include "hand.h"

class PlayerV2 {
private:
    
    bool _nameIsSet;
    //bool _inSession;
    
protected:
    int _MAX_CHARACTERS_ALLOWED = 15;
    std::string _name;
    double _money;
    const size_t MAX_HANDS_ALLOWED_TO_HOLD_;
    std::vector<Hand> hands_;
    void setMAX_CARDS_TO_HOLD(const size_t NUMBER_OF_HANDS);
    
public:
    static int _player2Count;
    friend std::ostream& operator<< (std::ostream &os, PlayerV2 &p);
    
    PlayerV2() = delete;
    PlayerV2(bool toIncludeInCount = false);
    PlayerV2(std::string name, const int MAX_CHARACTERS, double money, const size_t MAX_NUMBER_HAND_TO_HOLD, bool toIncludeInCount); //set name only, left out bool to allow for auto/default name
    
    int getPlayer2Count();
    void setPlayer2Count(int count);
    
    virtual void setName(std::string&, const int  MAX_CHARACTERS);
    std::string getName(bool showErrMsg); //bool for showing error message
    
    //void setNameIsSet(bool TrueOrFalse);
    //bool getNameIsSet() { return _nameIsSet; }
    
    virtual void setMoney(double money);
    virtual double getMoney();
    
    void addCardToHandFromDeck(Card, size_t index = 0);
    void removeCardsFromHand(int numCards, size_t index);
    
    std::vector<Hand>& getHand() { return hands_; }
    void displayHand();
    
    virtual void print();
    virtual void hit(Card card);
    void stand();
    //void stand();
    
    
};

#endif /* defined(__BlackJack__Playersv2__) */
