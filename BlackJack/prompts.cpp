//
//  prompts.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-30.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "prompts.h"

bool promptUserForDemoMode() {
    if (getYNFromQuestion("Would you like to run in demo mode? ") ==  "y") {
        return true;
    }
    else {
        return false;
    }

}

void askUserForName() {
    std::cout << "Enter a name:";
}