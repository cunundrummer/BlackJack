//
//  dealerPlayer.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-27.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "dealerPlayer.h"

void DealerPlayer::init(bool bustedFlag, bool pushFlag, bool inSessionFlag, bool standFlag, bool blackjackFlag) {
    bustedFlag_ = bustedFlag;
    pushFlag_ = pushFlag;
    inSessionFlag_ = inSessionFlag;
    standFlag_ = standFlag;
    blackjackFlag_ = blackjackFlag;
}

void DealerPlayer::print() {
    std::cout << getName(false) << ": " << "$" << std::fixed << std::setprecision(2) << getMoney() << std::endl ;
    displayHand();
    
}

void DealerPlayer::hit(Card card) {
    const int SEVENTEEN = 17; //dealer cannot hit when hand == 17, thats the rules!
    Hand *ptr_dealersHand = &hands_[ONE_HAND]; //alias for clarity
    if (ptr_dealersHand->calculate() >= SEVENTEEN) {
        std::cout << _name << " stands on " << SEVENTEEN << std::endl;
    }
    else {
        addCardToHandFromDeck(card);
    }
}