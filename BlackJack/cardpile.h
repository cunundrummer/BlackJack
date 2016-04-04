//
//  cardpile.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-04.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__cardpile__
#define __BlackJack__cardpile__

#include <iostream>
#include <vector>
#include <ctime>//used for old style randomization
#include <random>
#include "utilities.h"
#include "card.h"
#include "debug.hpp"

class CardPile {
protected:
    std::vector<Card> _cardPile;
    
public:
    CardPile() {};
    CardPile(std::vector<Card>& cards);
    void addCard(Card);
    void addCard(int, Suits);
    Card showCard(int atIndex = 0);
    virtual Card removeLastCard();
    void shuffle();
    void getCardPile(CardPile &cardPile) { cardPile = _cardPile; }
    int pileSize();
    virtual void print();
};
#endif /* defined(__BlackJack__cardpile__) */
