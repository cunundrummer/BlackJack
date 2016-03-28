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
    setBet(0);
    setPreBetMoney();
    setResolvedInsurancePayout();
}

void GamePlayer::init(bool inSessionFlag) {
    inSessionFlag_ = inSessionFlag;
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
/** 
 Implements the insurance bet as long as the player has more money then the required minimum bet. Also sets the insuranceBetIsSet flag accordingly.
*/
void GamePlayer::implementInsuranceBet() {
    if (_insuranceBetIsSet == false) {
        if (getMoney() >= 5) {
            //std::cout << "In GamePlayer::implementInsurnceBet, _bet = " << _bet << std::endl;
            _insuranceBet = _bet / 2;
            // _money -= _insuranceBet;
            std::cout << "After implementing insurance bet, money will be: " << std::endl << "Money $" <<
            getPreBetMoney() << std::endl << " - bet $" << _bet << std::endl << " - insurance bet $" << _insuranceBet << std::endl << " = $" << getPreBetMoney() - _bet -_insuranceBet << std::endl;
            
            _insuranceBetIsSet = true;
            setMoney(getPreBetMoney() - _bet -_insuranceBet);
        }
        else {
            std::cout << getName(false) << " does not have enough money for insurance. Aborting insurance bet." << std::endl;
            _insuranceBet = 0;
            _insuranceBetIsSet = false;
        }
        //std::cout << "Bet: " << _bet << std::endl;
        //std::cout << "Insurance bet: " << _insuranceBet << std::endl;
    }
    else {
        //error
    }
}

void GamePlayer::printBetReport() {
        
    std::cout << std::endl;
    std::cout << "BET REPORT:" << std::endl;
    std::cout << "Money @ start of round: " << getPreBetMoney() << std::endl;
    std::cout << "Bet: -$" << _bet << std::endl;
    if (_insuranceBetIsSet == true) {
        std::cout << "Insurance bet: -$" << getInsuranceBet() << std::endl;
    }
    int splitCout = 0;
    for (auto h: hands_) {
        if (h.getSplitFlag()) {
            std::cout << "Splithand(" << splitCout << "): ";
            std::cout << "-" << getBet() << std::endl;
        }
        if (h.getDoubledFlag()) {
            std::cout << "Doubled: YES for hand(" << splitCout << ")" << std::endl;
        }
        splitCout++;
    }
    //std::cout << "Total: $" << getMoney() << std::endl;
    std::cout << "END OF BET REPORT" << std::endl << std::endl;
}

int GamePlayer::buildPlayOptionForPlayerAndReturnChoice() {
    const int TWO_CARDS = 2;
    
    Menu optionsMenu;
    std::string header = "Here are your options: ";
    std::vector<std::string> options;
    int choice;
    
    /* 
     * this block of code should be made into a function ( getCurrentHandIndex )
     */
    int playerNumberOfHandsInHand = static_cast<int>(getHands().size()); //used for getting last hands index
    int index = 0;
    
    for (int i = 0; i < playerNumberOfHandsInHand - 1; i++) {
        if (getHand(i).getStandFlag() == false && getHand(i).getDoubledFlag() == false && getHand(i).getStandFlag() == false && getHand(i).getBustedFlag() == false && getHand(i).getBlackJackFlag() == false && getHand(i).getPushFlag() == false) {
            index = i;
        }
        else
            index++;
    }
    /*/////////////////////////////////////////////////////////////////////////*/
    
    std::cout << "DEBUG:GamePlayer::buildPlayoptions..., number of hands are: " << playerNumberOfHandsInHand << std::endl;
    std::cout << "DEBUG:GamePlayer::buildPlayoptions..., index = " << index << std::endl;
    if (isInSession() == true) { //default values as long as player is still in the game(hit, stand)
        options.push_back("Hit");
        options.push_back("Stand");
        
        if (getMoney() >= getBet()) {  //double down/splitting requires at least same amount as bet
            std::cout << "HHHAAAANNNDD is " << getHand(index) << std::endl;
            if (getHand(index).pileSize() == TWO_CARDS) { //handIsDoubleable
                options.push_back("Double down");
            }
            else {
                std::cout << "DEBUG: Gameplayer::buildplayOptionsForPlayer..., Hand[" << index << "] is not doubleable" << std::endl;
                std::cout << " because there are " << getHand(index).pileSize() << " cards in hand[" << index << "]" << std::endl;
            }
            if (getHand(index).getIndividualCard(0) == getHand(index).getIndividualCard(1) && getHand(index).pileSize() == TWO_CARDS) { //handIsSplittable
                options.push_back("Split");
            }
            
        } //else player does not have enough money to make any addition bets/plays
        optionsMenu.setHeader(header);
        optionsMenu.setOptions(options);
        choice = optionsMenu.displayAndGetChoice();
    }
    
    return choice;
}

void GamePlayer::hit(Card card, int handIndex) {
    std::cout << "DEBUG: IN HIT" << std::endl;
    std::cout << _name << " hits" << std::endl;
    addCardToHandFromDeck(card, handIndex);
    //int total = getHand(handIndex).calculate();
    
    std::cout << "DEBUG: END OF HIT" << std::endl;

}
/**
 *  This method checks if player has enough money to make a bet (hence the doubling).  Then proceeds to remove the bet from players money.  Last thing it does is add a card to the hand.
 *  @param Card: Takes a card for insertion into hand
 *  @param handIndex: The index of players hand to place card in
 *  @warning ATM this method does not set the doubleFlag/handInSessionFlag
 */
void GamePlayer::doubleDown(Card card, int handIndex) {
    //set to return boolean? Might be better for error checking

    std::cout << _name << " doubleing down" << std::endl;
    
    if (_money - _bet > 0) { //enough money available for doubling down?
        std::cout << "Player can double down." << std::endl;
        std::cout << "Removing $" << _bet << " from $" << _money << ": " << "$" << _money << " - $" << _bet << " = $" << _money - _bet << std::endl;
        _money -= _bet;
        //_bet *= 2;
        std::cout << "Adding card to hand, and disabling rest of session..." << std::endl;
        //maybe make call to hit instead?
        
        hands_[handIndex].addCard(card);
        //setDoubledFlag(true);
        //setInSession(false);
    }
    else {
        std::cout << _name << " cannot double down, not enough money. " << std::endl;
    }
}

/**
 *  @warning There might be a problem if the hand is split more then once
 */
int GamePlayer::split(int index = 0) {
    static int splitCount = 0; //count the number times splits for current player have been made/reset to 0 a the end of round
    const int MAX_SPLITS_ALLOWED = 3;
    
    if ( !(getHand(index).getIndividualCard(0) == getHand(index).getIndividualCard(1))) {
        std::cout << "Cannot split hands, cards 1 & 2 are not equal." << std::endl;
        return splitCount;
    }
    
    std::cout << "DEBUG GamePlayer:Split, splitCount before splitting is " << splitCount << std::endl;
    
    size_t numCurrentHands = hands_.size();
    std::cout << "DEBUG GamePlayer:Split: numCurrentHands = " << numCurrentHands << std::endl;
    
    //seperate hands ->
    if (splitCount < MAX_SPLITS_ALLOWED) {
        Hand h1;
        Hand h2;
        
        h2.addCard(hands_[index].removeLastCard());
        h1.addCard(hands_[index].removeLastCard());
        hands_.pop_back();
        
        double moneyAmountToRemove = 0;
        hands_.push_back(h1);
        std::cout << "Removing $" << getBet() << " for splitting hand" << std::endl;
        moneyAmountToRemove += getBet();
        hands_.push_back(h2);
        std::cout << "Removing $" << getBet() << " for splitting hand" << std::endl;
        moneyAmountToRemove += getBet();
        splitCount++;
        
        setMoney(getMoney() - moneyAmountToRemove);
    }
    else {
        std::cout << "Cannot split anymore hands." << std::endl;
    }
    std::cout << "DEBUG: Splitcount after splitting is " << splitCount << std::endl;
    //return unresolved splitCount;
    return splitCount;
}

int GamePlayer::indexOfSplitHand() {
    int numUnresolvedSplitHands = 0;
    for (auto h: hands_) {
        if (h.pileSize() == 1) {
            return numUnresolvedSplitHands;
        }
        else
            numUnresolvedSplitHands++;
    }
    return numUnresolvedSplitHands;
}

