//
//  Playersv2.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-10-08.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "Playersv2.h"

PlayerV2::PlayerV2 (bool toIncludeInCount):
    MAX_HANDS_ALLOWED_TO_HOLD_(4),
    _name("PLAYER"),
    _money(500)
{
    if (toIncludeInCount == true) {
        _player2Count++;
        
    }
    if (_name == "PLAYER") {
        _name.append(std::to_string(_player2Count));
    }

}

PlayerV2::PlayerV2(std::string name, const int MAX_CHARACTERS = 15, double money = 500, const size_t MAX_NUMBER_HAND_TO_HOLD = 4, bool toIncludeInCount = false) :
    _money(money),
    MAX_HANDS_ALLOWED_TO_HOLD_(MAX_NUMBER_HAND_TO_HOLD)
{
    if (toIncludeInCount == true) {
        _player2Count++;
        
    }
    
    setName(name, MAX_CHARACTERS);
    if (_name == "PLAYER") {
        _name.append(std::to_string(_player2Count));
    }
    
}

std::ostream& operator<< (std::ostream &os, PlayerV2 &p) {
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
void PlayerV2::setName(std::string &name, const int MAX_CHARACTERS) {
    
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
 * @discussion Returns the name of player.  If a name is empty, then an default name will be set.
 * @param optional error message, set to tru to show message
 * @warning
 * @return string
 */
void PlayerV2::removeCardsFromHand(int numCards = 1, size_t index = 0) {
    if (numCards > hands_[index].pileSize()) {
        std::cout << "Invalid amount of cards to be removed in Player::removeCardsFromHand(...), making numCards = pilesize." << std::endl;
        numCards = hands_[index].pileSize();
    }
    
    for (int i = 0; i < numCards; i++) {
        hands_[index].removeLastCard();
    }
    
}

std::string PlayerV2::getName(bool showErrMsg) {
    if ( _name.empty() || stringIsAlphaNumOnly(_name) == false || _nameIsSet == false) {
        if (showErrMsg == true)
            std::cout << "Name error: Giving a default name!" << std::endl;
        std::string name = "PLAYER";  //maybe move into parameter list?
        name.append(std::to_string(0/*_player2Count*/)); //give player1/2/3/...
        _nameIsSet = true;
        
        return _name = name;
    }
    else
        return _name;
}

int PlayerV2::getPlayer2Count() {
    return  _player2Count;
}

void PlayerV2::setPlayer2Count(int count) {
    _player2Count = count;
}

double PlayerV2::getMoney() {
    
    return _money;
}

void PlayerV2::setMoney(double money) {
    _money = money;
}

void PlayerV2::addCardToHandFromDeck(Card cardToAdd, size_t index) {
    //std::cout << "\n\nIn addCardToHand for " << _name << "...\nindex = " << index << ", " << "MAX_HANDS_ALLOWED_TO_HOLD_: " << MAX_HANDS_ALLOWED_TO_HOLD_ <<std::endl;
    if (index > MAX_HANDS_ALLOWED_TO_HOLD_) {
        std::cout << "ERROR: Exceeded MAX_HANDS_TO_HOLD in PlayerV2::addCardsToHandFromDeck" << std::endl;
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

void PlayerV2::displayHand() {
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

void PlayerV2::print() {
    //if ( getInSession() == true)
        std::cout << _name << ": " << "$" << std::fixed << std::setprecision(2) << getMoney();
    //else
       // std::cout << _name << ": " << "[out]";
    std::cout << std::endl;
    displayHand();

}

void PlayerV2::hit(Card card) {
    
    //std::cout << "Before handing card to player, there are " << _deck->pileSize() << " cards in deck" << std::endl;
    addCardToHandFromDeck(card);
    //std::cout << "After handing card to player, there are " << _deck->pileSize() << " cards in deck" << std::endl;
}

void PlayerV2::stand() {
    //setInSession(false);
}
