//
//  player.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-29.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "player.h"

Player::Player (bool toIncludeInCount):
MAX_HANDS_ALLOWED_TO_HOLD_(4),
_name("PLAYER"),
_money(500)
{
    if (toIncludeInCount == true) {
        _playerCount++;
        
    }
    if (_name == "PLAYER") {
        _name.append(std::to_string(_playerCount));
    }
    
}

Player::Player(std::string name, const int MAX_CHARACTERS = 15, double money = 500, const size_t MAX_NUMBER_HAND_TO_HOLD = 4, bool toIncludeInCount = false, bool inSession = true) :
_money(money),
MAX_HANDS_ALLOWED_TO_HOLD_(MAX_NUMBER_HAND_TO_HOLD),
_inSession(inSession)
{
    if (toIncludeInCount == true) {
        _playerCount++;
        
    }
    
    setName(name, MAX_CHARACTERS);
    if (_name == "PLAYER") {
        _name.append(std::to_string(_playerCount));
    }
    
}

void Player::init(bool bustedFlag, bool pushFlag, bool inSessionFlag, bool standFlag, bool blackjackFlag) {
    bustedFlag_ = bustedFlag;
    pushFlag_ = pushFlag;
    inSessionFlag_ = inSessionFlag;
    standFlag_ = standFlag;
    blackjackFlag_ = blackjackFlag;
}

std::ostream& operator<< (std::ostream &os, Player &p) {
    //int maxSpaces = p._MAX_CHARACTERS_ALLOWED;
    /*if (p.getInSession())
     os << p._name << ": " << "$" << std::fixed << std::setprecision(2) << p._money;
     else
     os << p._name << ": " << "[out]";*/
    std::cout << "*****" << p.getName() << " STATUS DISPLAY START" << "*****" << std::endl;
    p.printFlags();
    std::cout << "*****" << p.getName() << " STATUS DISPLAY END" << "*****" << std::endl;
   
    p.print();
    return os ;
}

void Player::printFlags() {
    std::cout << "bustedFlag: " <<  "[" << bustedFlag_ << "] " <<
    "pushFlag: " << "[" << pushFlag_ << "] " <<
    "inSessionFlag: " << "[" << inSessionFlag_ << "] " << std::endl <<
    "standFlag: " << "[" << standFlag_ << "] " <<
    "blackJackFlag"  << "[" << blackjackFlag_ << "] " << std::endl;
}

/*!
 * @discussion Sets the name manually. Sets _nameIsSet appropriatly.  Sets _playerCount if all is well.
 * @param
 * @return
 */
void Player::setName(std::string &name, const int MAX_CHARACTERS) {
    
    if ( name.empty() || stringIsAlphaNumOnly(name) == false || name.size() > MAX_CHARACTERS ) {
        std::cout << "Name error: letters and numbers only. No more then " << MAX_CHARACTERS << " characters long" << std::endl;
        _nameIsSet = false;
    }
    else {
        _name = name;
        _nameIsSet = true;
        
    }
}

/*!
 * @discussion Removes a card from the hand
 * @param int numCards: number of cards to remove, index of hand vector
 * @param size_t index: index of hand vector
 * @warning
 * @return
 */
void Player::removeCardsFromHand(int numCards = 1, size_t index = 0) {
    if (numCards > hands_[index].pileSize()) {
        std::cout << "Invalid amount of cards to be removed in Player::removeCardsFromHand(...), making numCards = pilesize." << std::endl;
        numCards = hands_[index].pileSize();
    }
    
    for (int i = 0; i < numCards; i++) {
        hands_[index].removeLastCard();
    }
    
}

std::string Player::getName(bool showErrMsg) {
    if ( _name.empty() || stringIsAlphaNumOnly(_name) == false || _nameIsSet == false) {
        if (showErrMsg == true)
            std::cout << "Name error: Giving a default name!" << std::endl;
        std::string name = "PLAYER";  //maybe move into parameter list?
        name.append(std::to_string(0/*_playerCount*/)); //give player1/2/3/...
        _nameIsSet = true;
        
        return _name = name;
    }
    else
        return _name;
}

Hand& Player::getHand(const int index) {
    if (hands_.empty()) {
        Hand hand;
        hands_.push_back(hand);
    }
    return hands_.at(index);
}


int Player::getPlayerCount() {
    return  _playerCount;
}

void Player::setPlayerCount(int count) {
    _playerCount = count;
}

double Player::getMoney() {
    
    return _money;
}

void Player::setMoney(double money) {
    _money = money;
}

void Player::addCardToHandFromDeck(Card cardToAdd, size_t index) {
    //std::cout << "\n\nIn addCardToHand for " << _name << "...\nindex = " << index << ", " << "MAX_HANDS_ALLOWED_TO_HOLD_: " << MAX_HANDS_ALLOWED_TO_HOLD_ <<std::endl;
    if (index > MAX_HANDS_ALLOWED_TO_HOLD_) {
        std::cout << "ERROR: Exceeded MAX_HANDS_TO_HOLD in Player::addCardsToHandFromDeck" << std::endl;
        exit(9);
    }
    
    if (hands_.empty() || index >= hands_.size()) {
        Hand h;
        h.addCard(cardToAdd);
        
        hands_.push_back(h);
    }
    else
        hands_.at(index).addCard(cardToAdd);
}

void Player::displayHand() {
    if (hands_.size() == 0) {
        std::cout << "Hand(s) N/A" << std::endl;
    }
    else {
        int i = 0;
        
        for (auto hand: hands_) {
            std::cout << "Hand " << i << ": " << hand << std::endl;
            i++;
        }
    }
}

void Player::print() {
    //if ( getInSession() == true)
    std::cout << _name << ": " << "$" << std::fixed << std::setprecision(2) << getMoney();
    //else
    // std::cout << _name << ": " << "[out]";
    std::cout << std::endl;
    displayHand();
    
}

void Player::hit(Card card) {
    
    std::cout << "DEBUG: IN HIT" << std::endl;
    std::cout << _name << " hits" << std::endl;
    addCardToHandFromDeck(card);
    int total = getHand(0).calculate();
    
    if (total > 21) {
        setBustedFlag(true);
        setInSession(false);
    }
    else if (total == 21) {
        setBlackjackFlag(true);
        setInSession(false);
    }
    else {
        //default case: break?
    }
     std::cout << "DEBUG: END OF HIT" << std::endl;
}

void Player::stand() {
    std::cout << _name << " stands" << std::endl;
    setStandFlag(true);
    setInSession(false);
}

void Player::doubleDown() {
    
}

void Player::split() {
    
}