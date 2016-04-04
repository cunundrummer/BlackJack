//
//  card.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-04.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__card__
#define __BlackJack__card__

#include <iostream>
#include "debug.hpp"

enum Suits { hearts, spades, diamonds, clubs, error };

class Card {
private:
   
    Suits suit_;
    int bjValue_;  //blackjack value as opposed to face (10, 11, 12, 13)
    bool isFaceUp_ = true; //mostly used to display dealers 2nd hand on first deal

public:
    friend std::ostream& operator<< (std::ostream &out, Card &card);
    bool operator==(const Card &other);
    
    Card(int bjValue = 0, Suits s = error) : suit_(s), bjValue_(bjValue) { };
    int getCardValue();
    void setBJValue(int);
    void setFaceUp(bool tOrf) { isFaceUp_ = tOrf; }
    bool getFaceUp() { return isFaceUp_; }
    //maybe add additional constructor to init. an actual value for card.  Will need to add appropriate data member for it.

};
#endif /* defined(__BlackJack__card__) */
