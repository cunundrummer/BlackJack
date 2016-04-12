//
//  AIGamePlayer.hpp
//  BlackJack
//
//  Created by Leeran on 2016-04-04.
//  Copyright © 2016 Compulsive Gamblers inc. All rights reserved.
//

#ifndef AIGamePlayer_hpp
#define AIGamePlayer_hpp

#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include "gamePlayer.h"
#include "debug.hpp"

class AIGamePlayer: public GamePlayer {
private:
    int getDecisionForHardHand(int handValue, int dealersUpCardValue);
    int getDecisionForSoftHand(int handValue, int dealersUpCardValue);
    
public:
    AIGamePlayer(std::string name) : GamePlayer(name) {};
    
    virtual void setBet(double defaultBet = 0);
    int makePlayChoice(Hand& dealersHand);

};

#endif /* AIGamePlayer_hpp */
