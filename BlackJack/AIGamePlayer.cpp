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
    const int MAX_ROWS = 10;
    const int MAX_COLUMNS = 26;
    
    //std::vector<std::vector<int>> simpleChart
    
    
    int choice = 0;
    /*switch (upCard.getCardValue()) {
        case 1:
            <#statements#>
            break;

        case 2:
            <#statements#>
            break

        case 3:
            <#statements#>
            break
        
        case 4:
            <#statements#>
            break
        
        case 5:
            <#statements#>
            break
        
        case 6:
            <#statements#>
            break
        
        case 7:
            <#statements#>
            break
        
        case 8:
            <#statements#>
            break
        
        case 9:
            <#statements#>
            break
        
        case 10:
            <#statements#>
            break
        
        default:
            break;
    }*/
    
    return 0;
}