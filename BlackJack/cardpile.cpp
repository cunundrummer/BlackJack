//
//  cardpile.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-04.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "cardpile.h"

CardPile::CardPile(std::vector<Card>& cards) {
    for (auto card: cards) {
        addCard(card);
    }
}

/**
 *  Gets how many cards are in the 'pile'
 */
int CardPile::pileSize() {
    int sz =  convertSizeTtoInt(_cardPile.size());
    
    return sz;
}

/*!
 * @discussion Will remove the last card in the card pile
 *
 * @return Card object if good or error card object if bad
 */
Card CardPile::removeLastCard() {
    
    if (!(_cardPile.empty())) {
        Card lastCard = _cardPile.back();
        //std::cout << "PILRSIZE before removing card is " << pileSize() <<std::endl;
        _cardPile.pop_back();
        //std::cout << "PILRSIZE after removing card is " << pileSize() <<std::endl;
        return lastCard;
    }
    else if (_cardPile.empty()) {
        std::cout << "CardPile::remove card error, cannot remove from empty deck." << std::endl;
        return Card(0, error);
    }
    else {
        std::cout << "Aborting program: index < 0 in removeLastCard." << std::endl;
        exit(9);
        return Card(0, error);
    }
}

void CardPile::addCard(Card c) {
    _cardPile.push_back(c);
}

void CardPile::addCard(int val, Suits suit) {
    Card c(val, suit);
    addCard(c);
}

void CardPile::print() {
    
    if (DEBUGGING) {
        std::cout << "DEBUG: CarPile: Print: BEGIN" << std::endl;
    }
    int i= 0;
    int nCards = 0;
    std::cout << "DECK #" << nCards + 1 << std::endl;
    for (std::vector<Card>::iterator it = _cardPile.begin(); it != _cardPile.end(); it++) {

        if (nCards == 52) {
            std::cout << std::endl << "DECK #" << (nCards / 52) + 1; //displays deck number
        }
        if (i >= 13) {
            std::cout << std::endl;
            i = 0;
        }
        ++i;
        ++nCards;
        std::cout << *it << " ";
    }
    if (DEBUGGING) {
        std::cout << "DEBUG: CarPile: Print: END" << std::endl;
    }
}

/**
 * Shuffles a pile of card objects
 * @warning Implented with newer c++14 randomization. Requires <random> header
 */
void CardPile::shuffle() {
    //c++14 'proper randomization
    std::random_device rng;
    std::mt19937 urng(rng());
    std::shuffle(_cardPile.begin(), _cardPile.end(), urng);
    
    //std::random_shuffle(_cardPile.begin(), _cardPile.end()); //deprecated randomization, required srand
}

