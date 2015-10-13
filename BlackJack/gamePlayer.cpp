//
//  gamePlayer.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-27.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "gamePlayer.h"

GamePlayer::GamePlayer(): Player("PLAYER", 15, 500, 4, true) {
    //setName("PLAYER", 15);
}


GamePlayer::GamePlayer(std::string name, const int MAX_CHARACTERS_ALLOWED = 15, double money = 500,  const size_t MAX_NUMBER_HANDS = 4, bool inSession = true) : Player(name, MAX_CHARACTERS_ALLOWED, money, MAX_NUMBER_HANDS, true) {
    setName(name, 15);
    _name = getName(false);
    _insuranceBet = 0;
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
        std::cout << _name << ": " << "[out]";
    std::cout << std::endl;
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

void GamePlayer::hit(Card card) {
    
    //std::cout << "Before handing card to player, there are " << _deck->pileSize() << " cards in deck" << std::endl;
    addCardToHandFromDeck(card);
    //std::cout << "After handing card to player, there are " << _deck->pileSize() << " cards in deck" << std::endl;
}