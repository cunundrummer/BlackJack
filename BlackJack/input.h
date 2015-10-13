//
//  input.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-28.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__input__
#define __BlackJack__input__

#include <iostream>
#include <string>
#include <locale>
#include "utilities.h"


char getDigitInput(const int biggest_allowable_number);
std::string getAlphaNumInput(const int, bool);
std::string getYNFromQuestion(std::string const &);
double getDoubleInput(bool allowDecimal = false);
#endif /* defined(__BlackJack__input__) */
