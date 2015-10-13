//
//  menu.h
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-10-02.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#ifndef __BlackJack__menu__
#define __BlackJack__menu__

#include <iostream>
#include <vector>
#include <string>
#include "input.h"

class Menu {
private:
    std::string header_;
    std::vector<std::string> options_;
    
public:
    Menu() {};
    Menu(std::string &header, std::vector<std::string> &options);
    void setHeader(std::string header) { header_ = header; }
    std::string getHeader() { return header_; }
    
    void setOptions(std::vector<std::string>& options);
    void display();
    int displayAndGetChoice();
};


#endif /* defined(__BlackJack__menu__) */
