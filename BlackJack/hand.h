//
//  hand.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-07.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__hand__
#define __BlackJack__hand__

#include <iostream>
#include <algorithm>
#include "cardpile.h"

class Hand : public CardPile {
private:
    /* FLAGS */
    
    bool surrenderFlag_;
    bool doubledFlag_;
    bool splitFlag_;
    bool bustedFlag_;
    bool pushFlag_;
    bool inSessionFlag_;
    bool standFlag_;
    bool blackjackFlag_;
    bool simpleLossFlag_;
    bool simpleWinFlag_;
    
public:
    Hand();
    Hand(std::vector<Card> &cards):CardPile(cards) { init(); }
    
    void init(bool bustedFlag = false, bool pushFlag = false, bool surrenderFlag = false, bool doubledFlag = false, bool standFlag = false, bool splitFlag = false, bool blackjackFlag = false, bool simpleLossFlag = false, bool simpleWinFlag = false);
    
    void setBustedFlag(bool flag)       { bustedFlag_ = flag; }
    void setPushFlag(bool flag)         { pushFlag_ = flag; }
    void setSurrenderFlag(bool flag)    { surrenderFlag_ = flag; }
    void setDoubledFlag(bool flag)      { doubledFlag_ = flag; }
    void setSplitFlag(bool flag)        { splitFlag_ = flag; }
    void setStandFlag(bool flag)        { standFlag_ = flag; }
    void setBlackjackFlag(bool flag)    { blackjackFlag_ = flag; }
    void setSimpleLossFlag(bool flag)   { simpleLossFlag_ = flag; }
    void setSimpleWinFlag(bool flag)    { simpleWinFlag_ = flag; }
    
    bool getBustedFlag()    { return bustedFlag_; }
    bool getPushFlag()      { return pushFlag_; }
    bool getSurrenderFlag() { return surrenderFlag_; }
    bool getDoubledFlag()   { return doubledFlag_; }
    bool getSplitFlag()     { return splitFlag_; }
    bool getStandFlag()     { return standFlag_; }
    bool getBlackJackFlag() { return blackjackFlag_; }
    bool getSimpleLossFlag(){ return simpleLossFlag_;}
    bool getSimpleWinFlag() { return simpleWinFlag_; }
    
    friend std::ostream& operator<< (std::ostream &os, Hand &h);
    void showHandFlags(const Hand& h);
    
    int calculate();
    void handToIndividualCards();//std::vector<Card>);
    Card getIndividualCard(int index);
    Hand& clearHand();
    
    
};
#endif /* defined(__BlackJack__hand__) */
