//
//  testFunctions.hpp
//  BlackJack
//
//  Created by Leeran on 2016-03-18.
//  Copyright © 2016 Compulsive Gamblers inc. All rights reserved.
//

#ifndef testFunctions_hpp
#define testFunctions_hpp

#include <iostream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "input.h"
#include "prompts.h"
#include "game.h"
#include "player.h"
#include "card.h"
#include "cardpile.h"
#include "hand.h"
#include "deck.h"
#include "gamePlayer.h"
#include "dealerPlayer.h"
#include "menu.h"
#include "player.h"
#include "AIGamePlayer.hpp"
#include "debug.hpp"

void testMenu();
void testPlayer();
void testAskForInsurance();
void testInsurance();
void testAIPlayer(AIGamePlayer);

void setPlayersHandForTesting(Player& hand, int cardVal1, Suits suit1, int cardVal2, Suits suit2);


#endif /* testFunctions_hpp */
