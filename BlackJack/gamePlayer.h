//
//  gamePlayer.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-27.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__gamePlayer__
#define __BlackJack__gamePlayer__

#include <iostream>
#include "player.h"

class GamePlayer : public Player {
private:
    double _max_allowable_bet_allowed;
    double _bet;
    double _insuranceBet;
    bool _wantsInsuranceFlag = false;
    bool _insuranceBetIsSet = false;
    
public:
    GamePlayer();
    GamePlayer(std::string name, const int MAX_CHARACTERS_ALLOWED = 15, double money = 500,  const size_t MAX_NUMBER_HANDS = 4, bool inSession = true);
    
    void setBet(double);
    double getBet() { return _bet; }
    
    double getMaxBetAllowed(double, double);
    void setMaxAllowableBet(double, double);
    
    virtual void print();
    
    void setInsuranceFlag(bool flag) { _wantsInsuranceFlag = flag; }
    bool getInsuranceFlag() { return _wantsInsuranceFlag; }
    void implementInsuranceBet();
    double getInsuranceBet() { return _insuranceBet; }
    void setInsuraceIsSet(bool tOrf) { _insuranceBetIsSet = tOrf; }
    bool getInsuranceIsSet() { return _insuranceBetIsSet; }
    
    /*void getHand(std::vector<Hand>& hands) {
        hands = hands_;
    }*/
    void hit(Card card);
    
};

#endif /* defined(__BlackJack__gamePlayer__) */
