//
//  dealerPlayer.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-27.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "dealerPlayer.h"

void DealerPlayer::print() {
    std::cout << getName(false) << ": " << "$" << std::fixed << std::setprecision(2) << getMoney() << std::endl ;
    displayHand();
    
}