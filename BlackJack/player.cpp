//
//  player.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-29.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "player.h"

Player::Player () {
    _name = "PLAYER";
    int count = 0;
    count = _playerCount;
    _name.append(std::to_string(count));
    _money = 500;
    _playerCount++;
}

Player::Player(std::string name, const int MAX_CHARACTERS = 15, double money = 500, bool inSession = true) : _money(money), _inSession(inSession) {
    setName(name, MAX_CHARACTERS);
    _playerCount++;
}

std::ostream& operator<< (std::ostream &os, Player &p) {
    //int maxSpaces = p._MAX_CHARACTERS_ALLOWED;
    /*if (p.getInSession())
        os << p._name << ": " << "$" << std::fixed << std::setprecision(2) << p._money;
    else
        os << p._name << ": " << "[out]";*/
    p.print();
    return os ;
}

/*!
 * @discussion Sets the name manually. Sets _nameIsSet appropriatly.  Sets _playerCount if all is well.
 * @param
 * @return
 */
void Player::setName(std::string name, const int MAX_CHARACTERS) {
    
    if ( name.empty() || stringIsAlphaNumOnly(name) == false || name.size() > MAX_CHARACTERS ) {
        std::cout << "Name error: letters and numbers only. No more then " << MAX_CHARACTERS << " characters long" << std::endl;
        _nameIsSet = false;
    }
    else {
        _name = name;
        _nameIsSet = true;
       
    }
}


void Player::removeCardsFromHand(int numCards = 1) {
/*
    if (numCards > hands_.pileSize()) {
        std::cout << "Invalid amount of cards to be removed in Player::removeCardsFromHand(...), making numCards = pilesize." << std::endl;
        numCards = hands_.pileSize();
    }
    
    for (int i = 0; i < numCards; i++) {
        hands_.removeLastCard();
    }
*/
}

/*!
 * @discussion Returns the name of player.  If a name is empty, then an default name will be set.
 * @param optional error message, set to tru to show message
 * @warning
 * @return string
 */
std::string Player::getName(bool showErrMsg) {
    if ( _name.empty() || stringIsAlphaNumOnly(_name) == false || _nameIsSet == false) {
        if (showErrMsg == true)
            std::cout << "Name error: Giving a default name!" << std::endl;
        std::string name = "PLAYER";  //maybe move into parameter list?
        name.append(std::to_string(_playerCount)); //give player1/2/3/...
        _nameIsSet = true;
       
        return _name = name;
    }
    else
        return _name;
}

int Player::getPlayerCount() {
    return _playerCount;
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

void Player::addCardToHandFromDeck(Card cardToAdd) {
    hands_.at(0).addCard(cardToAdd);
    
}

void Player::addCardToHandFromDeck(Card cardToAdd, int handIndex) {
    hands_.at(handIndex).addCard(cardToAdd);
}

void Player::hit(Card card) {
    
    //std::cout << "Before handing card to player, there are " << _deck->pileSize() << " cards in deck" << std::endl;
    addCardToHandFromDeck(card, 0);
    //std::cout << "After handing card to player, there are " << _deck->pileSize() << " cards in deck" << std::endl;
}

void Player::stand() {
    setInSession(false);
}

Hand Player::getHand(int index = 0) {
    return hands_[index];
}

void Player::displayHand() {
    int i = 0;
    std::cout << std::endl;
    for (auto hand: hands_) {
        std::cout << "Hand#" << i + 1 << " " << hand << std::endl;
        i++;
    }
    
}