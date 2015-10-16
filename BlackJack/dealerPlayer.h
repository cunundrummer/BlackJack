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

const bool inSession = true; //for constructor -> player

class DealerPlayer : public Player {
private:

public:
    DealerPlayer(std::string name = "Dealer", const int MAX_CHARACTERS = 15, double money = 2000, const size_t MAX_NUMBER_HAND_TO_HOLD = 0, bool toIncludeInCount = true):
    Player(name, MAX_CHARACTERS, money, MAX_NUMBER_HAND_TO_HOLD, toIncludeInCount, inSession) {
        //setInSession(true);
    }
    
    void print();
    
    
    ~DealerPlayer(){};
};

#endif /* defined(__BlackJack__dealerPlayer__) */
