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
        if (_bjValue == other._bjValue) {
            std::cout << "(_bjValue == other._bjValue)" << " true" << std::endl;
        }
        else
            std::cout << "(_bjValue == other._bjValue)" << " false" << std::endl;
    }
    
    return _bjValue == other._bjValue;
}

std::ostream& operator<< (std::ostream &out, Card &card)
{
    
    if (card._bjValue == 1)
        out << "A";
    else if ( card._bjValue == 11)
        out << "J";
    else if (card._bjValue == 12)
        out << "Q";
    else if (card._bjValue == 13)
        out << "K";
    else if (card._bjValue >= 2 && card._bjValue <= 10)
        out << card._bjValue;
    else {
        out << "Error: Value not in range: quitting!";
        exit(9);
    }
    
    switch (card._suit) {
        case 0:
            out << "♡";
            break;
        case 1:
            out << "♠";
            break;
        case 2:
            out << "♢";
            break;
        case 3:
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
    _bjValue = val;
}

int Card::getCardValue() { //must rework 11 and jack to give right values!!!
    if (_bjValue >= 11) {
       _bjValue = 10;
    }
    return _bjValue;
}