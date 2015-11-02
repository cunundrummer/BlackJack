//
//  gamePlayer.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-27.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "gamePlayer.h"

GamePlayer::GamePlayer(): Player("PLAYER", 15, 500, 4, true, true) {
    //setName("PLAYER", 15);
}

/*!
 * @discussion constructor call with parameters
 * @param name, MAX_CHARACTERS_ALLOWED, double money, const size t MAX_NUMBERS, bool inSession
 * @warning
 */
GamePlayer::GamePlayer(std::string name, const int MAX_CHARACTERS_ALLOWED, double money,  const size_t MAX_NUMBER_HANDS, bool inSession) : Player(name, MAX_CHARACTERS_ALLOWED, money, MAX_NUMBER_HANDS, true, true) {
    setName(name, 15);
    _name = getName(false);
    _insuranceBet = 0;
}

void GamePlayer::init(bool bustedFlag, bool pushFlag, bool surrenderFlag, bool inSessionFlag, bool doubledFlag, bool standFlag, bool splitFlag, bool blackjackFlag) {
    bustedFlag_ = bustedFlag;
    pushFlag_ = pushFlag;
    surrenderFlag_ = surrenderFlag;
    inSessionFlag_ = inSessionFlag;
    doubledFlag_ = doubledFlag;
    standFlag_ = standFlag;
    splitFlag_ = splitFlag;
    blackjackFlag_ = blackjackFlag;
}

void GamePlayer::setBet(double bet = 0) {
    _bet = bet;
}

double GamePlayer::getMaxBetAllowed(double minAllowableBet = 5, double maxAllowableBet = 500) {
    if (_money > maxAllowableBet)
        return maxAllowableBet;
    else if (_money > minAllowableBet && _money <= maxAllowableBet)
        return _money;
    else
        return 0;
    
}

void GamePlayer::setMaxAllowableBet(double min, double max) {
    if (_money < min) {
        std::cout << "Player does not have enough money to continue. Removing" << _name << " from game." << std::endl;
        setInSession(false);
    }
    else
        _max_allowable_bet_allowed = getMaxBetAllowed(min, max);
}

void GamePlayer::print() {
    //std::cout << "Printing from Gameplayer::print()" << std::endl;
    
    if ( isInSession() == true)
        std::cout << _name << ": " << "$" << std::fixed << std::setprecision(2) << getMoney() << "  Insurance Flag:" << getInsuranceFlag();
    else
        std::cout << _name << ": " << "$" << std::fixed << std::setprecision(2) << getMoney() << "[out]";
    std::cout << std::endl;
    printBetReport();
    displayHand();
}

void GamePlayer::implementInsuranceBet() {
    if (_insuranceBetIsSet == false) {
        if (getMoney() >= 5) {
            //std::cout << "In GamePlayer::implementInsurnceBet, _bet = " << _bet << std::endl;
            _insuranceBet = _bet / 2;
            _money -= _insuranceBet;
            std::cout << "After implementing insurance bet, money is: " << _money << std::endl;
        }
        else {
            std::cout << getName(false) << " does not have enough money for insurance. Aborting insurance bet." << std::endl;
            _insuranceBet = 0;
        }
        std::cout << "Bet: " << _bet << std::endl;
        std::cout << "Insurance bet: " << _insuranceBet << std::endl;
    }
    _insuranceBetIsSet = true;
}

void GamePlayer::printFlags() {
    std::cout << "bustedFlag: " <<  "[" << bustedFlag_ << "] " <<
    "pushFlag: " << "[" << pushFlag_ << "] " <<
    "surrenderFlag: " << "[" << surrenderFlag_ << "] " <<
    "inSessionFlag: " << "[" << inSessionFlag_ << "] " << std::endl <<
    "doubleFlag: " << "[" << doubledFlag_ << "] " <<
    "standFlag: " << "[" << standFlag_ << "] " <<
    "splitFlag: " << "[" << splitFlag_ << "] " <<
    "blackJackFlag"  << "[" << blackjackFlag_ << "] " << std::endl;
}

void GamePlayer::printBetReport() {
    std::cout << std::endl;
    std::cout << "BET REPORT:" << std::endl;
    std::cout << "Money @ start of round: " << getPreBetMoney() << std::endl;
    std::cout << "Bet: -$" << _bet << std::endl;
    std::cout << "Insurance bet: -$" << _insuranceBet << std::endl;
    std::cout << "Resolved insurance bet: $" << resolvedInsurancePayout_ << std::endl;
    std::cout << "Double bet: $"; (doubledFlag_) ?  std::cout << "-" << _bet << std::endl : std::cout << "0" << std::endl;
    std::cout << "Total: $" << _money << std::endl;
    std::cout << "END OF BET REPORT" << std::endl << std::endl;
}

void GamePlayer::doubleDown(Card card, int handIndex = 0) {
    //set to return boolean? Might be better for error checking

    std::cout << _name << " doubleing down" << std::endl;
    
    if (_money - _bet > 0) { //enough money available for doubling down?
        std::cout << "Player can double down." << std::endl;
        std::cout << "Removing $" << _bet << " from $" << _money << ": " << "$" << _money << " - $" << _bet << " = $" << _money - _bet << std::endl;
        _money -= _bet;
        std::cout << "Adding card to hand, and disabling rest of session..." << std::endl;
        hands_[handIndex].addCard(card);
        setDoubledFlag(true);
        setInSession(false);
    }
    else {
        std::cout << _name << " cannot double down, not enough money. " << std::endl;
    }
}