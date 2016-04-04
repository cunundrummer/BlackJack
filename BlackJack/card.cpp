//
//  card.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-04.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "card.h"

bool Card::operator==(const Card &other) {
    if (DEBUGGING) {
        if (bjValue_ == other.bjValue_) {
            std::cout << "(bjValue_ == other.bjValue_)" << " true" << std::endl;
        }
        else
            std::cout << "(bjValue_ == other.bjValue_)" << " false" << std::endl;
    }
    
    return bjValue_ == other.bjValue_;
}

std::ostream& operator<< (std::ostream &out, Card &card)
{
    
    if (card.bjValue_ == 1)
        out << "A";
    else if ( card.bjValue_ == 11)
        out << "J";
    else if (card.bjValue_ == 12)
        out << "Q";
    else if (card.bjValue_ == 13)
        out << "K";
    else if (card.bjValue_ >= 2 && card.bjValue_ <= 10)
        out << card.bjValue_;
    else {
        out << "Error: Value not in range: quitting!";
        exit(9);
    }
    
    switch (card.suit_) {
        case hearts:
            out << "♡";
            break;
        case spades:
            out << "♠";
            break;
        case diamonds:
            out << "♢";
            break;
        case clubs:
            out << "♣";
            break;
            
        default:
            out << "Error: Suit is undefined: quitting!";
            exit(9);
            break;
    }
    
    return out;
}

void Card::setBJValue(int val) {
    bjValue_ = val;
}

int Card::getCardValue() { //must rework 11 and jack to give right values!!!
    if (bjValue_ >= 11) {
       bjValue_ = 10;
    }
    return bjValue_;
}