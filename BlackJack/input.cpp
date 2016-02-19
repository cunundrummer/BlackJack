//
//  input.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-28.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "input.h"

/**
 * @brief Gets an input consisting of only letters and numbers upto MAX_CHARACTERS long
 * @return proper string
 */
std::string getAlphaNumInput(const int MAX_CHARACTERS, bool canBeEmpty) {
    std::string input;
    if (canBeEmpty == false) {
        while ( !(getline(std::cin, input) ) || input.empty() || stringIsAlphaNumOnly(input) == false || input.size() > MAX_CHARACTERS ) {
            
            std::cin.clear();
            std::cout << "Bad input, letters and numbers only. No more then " << MAX_CHARACTERS << " characters long" << std::endl;
            
        }
    }
    else {
        while ( !(getline(std::cin, input) ) || stringIsAlphaNumOnly(input) == false || input.size() > MAX_CHARACTERS ) {
            
            std::cin.clear();
            std::cout << "Bad input, letters and numbers only. No more then " << MAX_CHARACTERS << " characters long" << std::endl;
            
        }
    }
    
   // std::cout << input.size();
    return input;
}

char getDigitInput(const int biggest_allowable_number) {
    char input = '0';
    std::string str_input;
    while (!(getline(std::cin, str_input) ) || str_input.empty() || !is_digits(str_input) || convertStringToInt(str_input) >= biggest_allowable_number ) {
        std::cin.clear();
        std::cout << "Bad input, numbers only." << std::endl;
    }
    
    input = std::stoi(str_input);
    return input;
}



/**
 *@abstract Asks a question and returns a Y or N only
 **/
std::string getYNFromQuestion(std::string const &question) {
    
    std::cout << question << "y or n: " << std::endl;
    std::string answer = "";

    while (!getline(std::cin, answer) || answer.empty() || answer.length() > 1 || (stringToUpperLower(answer) != "y" && stringToUpperLower(answer) != "n")) { //check for capitals and convert?
        
        std::cout << "You must input y or n only! " << std::endl;
        std::cout << question << "y or n: " << std::endl;
        std::cin.clear();
    }
    
    return answer;
}

std::string stringToUpperLower(std::string str, STRING_CASE c) {
    
    for (int i = 0; i < str.length(); i++) {
        if (c == STRING_CASE::lower) {
            str[i] = std::tolower(str[i]);
        }
        else {
            str[i] = std::toupper(str[i]);
        }
    }
    return str;
}

double getDoubleInput(bool allowDecimal) {
    
    std::string input;
    
    while ( !(getline(std::cin, input) ) || is_digits(input) == false) {
        
        std::cout << "Please enter numbers only!" <<  std::endl;
        
    }
    
    return atof(input.c_str());
}

