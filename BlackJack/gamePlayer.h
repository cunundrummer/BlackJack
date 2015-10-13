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
//#include "Playersv2.h"

class GamePlayer : public Player { //original :Player
private:
    double _max_allowable_bet_allowed;
    double _bet;
    double _insuranceBet;
    bool _wantsInsuranceFlag = false;
    bool _insuranceBetIsSet = false;
    bool _inSession = true;
    
public:
    GamePlayer();
    GamePlayer(std::string, int, double money, const size_t maxNumberHands, bool inSession);
    
    void setBet(double);
    double getBet() { return _bet; }
    
    double getMaxBetAllowed(double, double);
    void setMaxAllowableBet(double, double);
    bool isInSession() { return _inSession; }
    void setInSession(bool session) { _inSession = session; }
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
