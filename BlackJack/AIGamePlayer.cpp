//
//  AIGamePlayer.cpp
//  BlackJack
//
//  Created by Leeran on 2016-04-04.
//  Copyright © 2016 Compulsive Gamblers inc. All rights reserved.
//

#include "AIGamePlayer.hpp"

/**
 *  This method will make a random bet between minBetAllowed and 100(subject to change).
 *
 *  @param double bet has a default value of 0. Don't feed a value when using this method
 *  @warning don't feed a bet when using this method. Strictly for AI to implement bet.
 */
void AIGamePlayer::setBet(double bet) {
    //todo: check money
    //todo: get a 'card count' to make more accurate bets
    double curMoney = getMoney();
    double minMoney = 5;
    double maxMoney = (curMoney > 500) ? maxMoney = 500 : maxMoney = curMoney;
    double maxBet = 100;
    
    if (DEBUGGING) {
        std::cout << getName() << "'s maxMoney to bet is " << maxMoney << std::endl;
    }
    
    std::random_device randomDevice;
    std::mt19937 randomNumberGenerator(randomDevice());
    std::uniform_real_distribution<double> dist(minMoney, maxBet);
    
    bet = std::round(dist(randomNumberGenerator));  // remove the decimal
    while ((static_cast<int>(bet) % 5) != 0) {
        bet--;
    }
    // round down bet to every '5th'
    
    if (DEBUGGING) {
        std::cout << "Bet atm is " << bet << std::endl;
    }
    
    _bet = bet;

}

int AIGamePlayer::makePlayChoice(Hand& dealersHand) {
    const int UP_CARD_INDEX = 0;
    Card upCard = dealersHand.showCard(UP_CARD_INDEX);
    
    bool hardHand = getHand().isHardHand();  //hard or soft
    int calculatedPlayerHand = getHand().calculate();
    
    
    int choice = 0;
    
    if (hardHand) {
        choice = getDecisionForHardHand(calculatedPlayerHand, upCard.getCardValue());
    }
    else {
        choice = getDecisionForSoftHand(calculatedPlayerHand, upCard.getCardValue());
    }
    
    return choice;
}

int AIGamePlayer::getDecisionForHardHand(int handValue, int dealersUpCardValue) {
    std::cout << "DEBUG: Entered AIGamePlayer::getDecisionForHardHand:..." << std::endl;
    std::cout << "AIplayers hand value: " << handValue << std::endl;
    std::cout << "DealersUpCardValue: " << dealersUpCardValue << std::endl;
    
    //Dealer = column; player = row//
    //5 dummy rows for offset( has to start at 5 for hard hands
    std::vector<std::vector<int> > chart = {
        //1    2    3    4    5    6    7    8    9    10
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},

        {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT}, //START AT HARD 5 BECAUSE 4 = (2 | 2 ) AND ANYTHING LESS IS soft
        {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
        {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
        {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
        {HIT, HIT, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, HIT, HIT, HIT, HIT},
        {HIT, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, HIT},
        {DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN, DOUBLE_DOWN},
        {HIT, HIT, STAND, STAND, STAND, HIT, HIT, HIT, HIT, HIT},
        {HIT, STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT, HIT},
        {HIT, STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT, HIT},
        {HIT, STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT, HIT}, //find better chart!!!
        {HIT, STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT, HIT},
        {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
        {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
        {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
        {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
        {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND}
        /*
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
         */
        
    };
    
    int choice = 0;
    for (int row = 0; row < handValue; row++) {
        
        std::cout << row;
        (row < 10) ? std::cout << " |": std::cout << "|";
        
        for (int colummn = 0; colummn < dealersUpCardValue; colummn++) {
            std::cout << chart[row][colummn] << "|";
            choice = chart[row][colummn];
        }
        std::cout << std::endl;
    }
    if (DEBUGGING) {
        std::cout << "chart[17][5]" << " is reading " << chart[handValue][dealersUpCardValue] << std::endl;
    }
    choice = chart[handValue][dealersUpCardValue];
    
    return choice;
}

int AIGamePlayer::getDecisionForSoftHand(int handValue, int dealersUpCardValue) {
    std::cout << "DEBUG: Entered AIGamePlayer::getDecisionForSoftHand:..." << std::endl;
    return getDecisionForHardHand(handValue, dealersUpCardValue);
    
}