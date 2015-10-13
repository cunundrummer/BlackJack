//
//  hand.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-07.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "hand.h"

std::ostream& operator<< (std::ostream &os, Hand &h) {
    std::vector<Card> cVector;
    
    //std::cout << "In HAND<<, pilesize is " << h.pileSize() << std::endl;
        for (auto hnd :h._cardPile) {
            if (hnd.getFaceUp()) {
                os << hnd << " ";
            }
            else {
                os << "X" << " ";
            }
        }
    
    os << ": " << h.calculate();
    
    return os;
}

void Hand::handToIndividualCards() {// std::vector<Card> c) {
    std::vector<Card> c;
    for (int i = 0; i < _cardPile.size();  i++) {
        c.push_back(_cardPile[i]);
        //std::cout << c[i];
    }
    std::cout << "CardPile has " <<  c.size() << " elements. " << std::endl;
    //std::cout << "Card is " << c << std::endl;

}
int Hand::calculate() {
    int total = 0;
    int value = 0;
    int aceCount = 0;
    const int JACK_QUEEN_KING_VALUE = 10;
    const int BLACKJACK = 21;
    
    if (_cardPile.empty())
        return 0;
    else {
        for (auto c : _cardPile ) {
            int cardValue = c.getCardValue();
            if ( cardValue >= 2 && cardValue < JACK_QUEEN_KING_VALUE) {
                value = c.getCardValue();
                total += value;
            }
            else if (cardValue >= JACK_QUEEN_KING_VALUE) {
                value = JACK_QUEEN_KING_VALUE;
                total += value;
            }
            else {
                aceCount++;
            }
        }
    }
    
    //begin ace calculation. If the total is >= 22 recalculate until answer is less then/= 21 if possible
    if (aceCount == 0) {
        //std::cout << "In Hand::Calculate method, The total is: " << total << " and the aceCount is: " << aceCount << std::endl;
        return total;
    }
    else {
        //std::cout <<std::endl;
        for (int i = 0; i < aceCount; i++) {
            //std::cout << i + 1 << " Total is: " << total << std::endl;
            total += 11;
            //std::cout << "Total after adding 11: " << total << std::endl;
            
            if (total > BLACKJACK)  {
                total -= 10;
            }
            
        }
        return total;
    }
    
}

Card Hand::getIndividualCard(int index) {
    return _cardPile[index];
}