//
//  utilities.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-29.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "utilities.h"

/**
 * @brief Test whether string is lettlers or numbers
 * @return true if string is alpha-numeric, false if not alpha-numeric
 */
bool stringIsAlphaNumOnly(const std::string &str) {
    
    bool TF = true;
    for (std::string::const_iterator str_it = str.begin(); str_it != str.end(); str_it++) {
        if ( !(isalnum(*str_it)) ) {
            TF = false;
        }
    }
    
    return TF;
}

std::string convert_SizeT_toString(size_t val) {
    std::string str = "";
    std::ostringstream output;
    
    output << val;
    str = output.str();
    
    return str;
}

int convertStringToInt(std::string str) {
    std::istringstream istr(str);
    int i;
    istr >> i;
    
    return i;  //should check for min/max values
}

int convertSizeTtoInt(size_t val) {
    std::string str = convert_SizeT_toString(val);
    return convertStringToInt(str);   //should check for min/max values
}

std::string printFlag(int flag) {
    switch (flag) {
        case 0:
            return "GAME_GOES_ON";
            break;
        case 21:
            return "BLACKJACK";
            break;
            
        default:
            return "YET UNKNOWN";
            break;
    }
}

bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}