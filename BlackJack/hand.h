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
    bool _isBustedFlag;
    
public:
    Hand(){};
    Hand(std::vector<Card> &cards):CardPile(cards) {};
    friend std::ostream& operator<< (std::ostream &os, Hand &h);
    int calculate();
    void handToIndividualCards();//std::vector<Card>);
    Card getIndividualCard(int index);
    
    
};
#endif /* defined(__BlackJack__hand__) */
