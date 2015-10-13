//
//  deck.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-07.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__deck__
#define __BlackJack__deck__

#include <iostream>
#include "cardpile.h"

class Deck : public CardPile {
private:
    const int MAX_CARDS_IN_A_DECK = 52;
public:
    
    Deck(int);
    /*void print() { for (auto d: _cardPile) {
        std::cout << d;
    }};*/
};


#endif /* defined(__BlackJack__deck__) */
