//
//  dealerPlayer.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-27.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__dealerPlayer__
#define __BlackJack__dealerPlayer__

#include <iostream>
#include "player.h"

const bool IN_SESSION = true; //for constructor -> player
const std::string DEALERS_NAME = "DEALER";
const int MAX_CHARACTERS_FOR_NAME = 6;
const size_t ONE_HAND = 0;  //0 for a vector index i.e  vector Hands[0] <- thats is one hand

class DealerPlayer : public Player {
private:

public:
    DealerPlayer(double money = 2000, const size_t MAX_NUMBER_HAND_TO_HOLD = ONE_HAND, bool toIncludeInCount = true):
    Player(DEALERS_NAME, MAX_CHARACTERS_FOR_NAME, money, MAX_NUMBER_HAND_TO_HOLD, toIncludeInCount, IN_SESSION) {
        init();
    }
    
    void init(bool bustedFlag = false, bool pushFlag = false, bool inSessionFlag = true, bool standFlag = false, bool blackjackFlag = false);
    void hit(Card card);
    
    void print();
    
    ~DealerPlayer(){};
};

#endif /* defined(__BlackJack__dealerPlayer__) */
