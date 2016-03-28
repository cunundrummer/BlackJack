//
//  dealerPlayer.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-27.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "dealerPlayer.h"

void DealerPlayer::init(bool inSessionFlag) {
    inSessionFlag_ = inSessionFlag;
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

/**
 *  The dealer will play his hand here.  Dealer will always hit as long as hand is less then hard 17.  A hard 17 is any hand thay totals 17 w/o aces.
 *  @param Deck&
 *  deck will have a card removed for hitting and will give to dealer
 */
void DealerPlayer::playHand(Deck& deck) {
    
    int dealersOnlyHand = 0;
    const int HARD17 = 17;
    //define method to determine wether hand is hard or soft
    int handTotal = 0;
    
    do {
        
        handTotal = hands_[dealersOnlyHand].calculate();
        
        if (handTotal < HARD17) {
            std::cout << DEALERS_NAME << " has a total of " << handTotal << ". " << DEALERS_NAME << " will hit." << std::endl;
            hit(deck.removeLastCard());
            std::cout << hands_[dealersOnlyHand];
        }
        else {
            std::cout << DEALERS_NAME << " stands on " << handTotal << std::endl;
        }
    
    } while (handTotal < HARD17);
    
}