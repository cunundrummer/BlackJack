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
#include "menu.h"

enum PLAY_OPTIONS {HIT, STAND, DOUBLE_DOWN, SPLIT};

class GamePlayer : public Player {
private:
    double _max_allowable_bet_allowed;
    double _bet;
    double _insuranceBet;
    double doubledBet_;  //used for betReport
    double preBetMoney_;  //used for betReport
    double resolvedInsurancePayout_; // used for betReport
    
    bool _insuranceBetIsSet;
    bool _wantsInsuranceFlag;
    
public:
    GamePlayer();
    GamePlayer(std::string name, const int MAX_CHARACTERS_ALLOWED = 15, double money = 500,  const size_t MAX_NUMBER_HANDS = 4, bool inSession = true);
    virtual void init(bool inSessionFlag = true);
    
    void setBet(double);
    double getBet() { return _bet; }
    void setPreBetMoney() { preBetMoney_ = getMoney(); }
    double getPreBetMoney() { return preBetMoney_; }
    void setResolvedInsurancePayout(double payout = 0) {
        //std::cout << "Payout is " << payout << std::endl;
        resolvedInsurancePayout_ = payout; }
    double getResolvedInsurancePayout() { return resolvedInsurancePayout_; }
    
    double getMaxBetAllowed(double, double);
    void setMaxAllowableBet(double, double);
    
    virtual void print();
    
    void printBetReport();
    
    void setInsuranceFlag(bool flag) { _wantsInsuranceFlag = flag; }
    bool getInsuranceFlag() { return _wantsInsuranceFlag; }         //possible redundancy
    
    void implementInsuranceBet();
    void setInsuranceBet(double value = 0) { _insuranceBet = value; }
    double getInsuranceBet() { return _insuranceBet; }
    void setInsuraceIsSet(bool tOrf) { _insuranceBetIsSet = tOrf; } //possible redundancy, used in implementInsuranceBet
    bool getInsuranceIsSet() { return _insuranceBetIsSet; }         //possible redundancy, used in implementInsuranceBet
    
    int buildPlayOptionForPlayerAndReturnChoice();
    
    int indexOfSplitHand();
    /*void getHand(std::vector<Hand>& hands) {
        hands = hands_;
    }*/
    //void hit(Card card);
    void hit(Card card, int handIndex = 0);
    void doubleDown(Card card, int handIndex = 0);
    int split(int index); //return number of unresolved splits
    
};

#endif /* defined(__BlackJack__gamePlayer__) */
