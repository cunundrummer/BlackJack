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
    bool bustedFlag_;
    bool pushFlag_;
    bool inSessionFlag_;
    bool standFlag_;
    bool blackjackFlag_;
    
    virtual void init(bool bustedFlag = false, bool pushFlag = false, bool inSessionFlag = true, bool standFlag = false, bool blackjackFlag = false);
    
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
        
    virtual void setBustedFlag(bool flag)       { bustedFlag_ = flag; }
    virtual void setpushFlag(bool flag)         { pushFlag_ = flag; }
    virtual void setInSession(bool flag)        { inSessionFlag_ = _inSession = flag; } //remove reudundant _inSession
    virtual void setStandFlag(bool flag)        { standFlag_ = flag; }
    virtual void setBlackjackFlag(bool flag)    { blackjackFlag_ = flag; }
    
    virtual bool getBustedFlag()    { return bustedFlag_; }
    virtual bool getPushFlag()      { return pushFlag_; }
    virtual bool getStandFlag()     { return standFlag_; }
    virtual bool getBlackJackFlag() { return blackjackFlag_; }
    bool isInSession()              { return _inSession; } //should be renamed getSessionFlag/fast ugly hack: make method and call it?
    
    virtual void setMoney(double money);
    virtual double getMoney();
    
    void addCardToHandFromDeck(Card, size_t index = 0);
    void removeCardsFromHand(int numCards, size_t index);
    
    Hand& getHand(int index = 0);/* { return hands_[index] ; }*/
    //Hand getHand(/*const int index = 0*/);
    std::vector<Hand> getHands() { return hands_; }
    void displayHand();
    virtual void printFlags();
    virtual void print();
    
    virtual void hit(Card card);
    virtual void stand();
    virtual void doubleDown();
    virtual void split();
    
};

#endif /* defined(__BlackJack__player__) */
