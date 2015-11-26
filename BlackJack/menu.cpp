//
//  menu.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-10-02.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "menu.h"

Menu::Menu(std::string &header, std::vector<std::string> &options): header_(header), options_(options) {
    
}

void Menu::setOptions(std::vector<std::string> &options) {
    options_ = options;
    }

void Menu::display() {
    int i = 0;
    for (auto o: options_) {
        std::cout << i << ": " << o << std::endl;
        i++;
    }

}

int Menu::displayAndGetChoice() {
    display();
    std::cout << "Enter choice: ";
    std::string str_size = convert_SizeT_toString(options_.size());
    int int_size = convertStringToInt(str_size);
    char choice = getDigitInput(int_size);
    
    return choice;
}