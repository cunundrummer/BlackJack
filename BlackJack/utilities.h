//
//  utilities.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-29.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__utilities__
#define __BlackJack__utilities__

#include <iostream>
#include <sstream>
#include <cmath>

bool stringIsAlphaNumOnly(const std::string &);
bool is_digits(const std::string &str);

std::string convert_SizeT_toString(size_t);
int convertStringToInt(std::string);
int convertSizeTtoInt(size_t);
bool isDoubleEqual(const double num1, const double num2, const double accuracy = 0.00001);

std::string printFlag(int flag);

#endif /* defined(__BlackJack__utilities__) */
