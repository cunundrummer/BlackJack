//
//  deck.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-05-07.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "deck.h"

Deck::Deck(int nDecks) {
    
    std::cout << "DEBUG: Deck constructor:  building " << nDecks << " decks." << std::endl;
    
    cardCount = 0;
    
    if (nDecks == 0) {
        nDecks = 1;
    }
    
    for (int i = 0; i < nDecks; i++) {
        
        
        const int MIN_VAL = 1;
        const int MAX_VAL = 13;
        
        int valCounter = MIN_VAL; //value cannot be more the 0 or > 13
        int suitCounter = 0;
        
        for (int cardCounter = 0; cardCounter < MAX_CARDS_IN_A_DECK; ++cardCounter) {
            if (suitCounter == 4) {
                suitCounter = 0;
            }
            
            //create card
            _cardPile.push_back(Card(valCounter, static_cast<Suits>(suitCounter)));
            
            valCounter++;
            if (valCounter > MAX_VAL) {
                valCounter = MIN_VAL; //resets the suit counter so it stays below 14
                ++suitCounter; //new suit because of above statement
            }
            if ((cardCounter > 1) and (cardCounter % MAX_CARDS_IN_A_DECK == 0 )) {
                suitCounter = 0; //reset suits for new deck if more then 1 deck
            }
        }
    }
        std::cout << "DEBUG: Deck constructor: END: Have " << _cardPile.size() << " decks." << std::endl;
}
