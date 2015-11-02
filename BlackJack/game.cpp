//
//  game.cpp
//  BlackJack
//
//  Created by Leeran Pinckovich on 2015-04-28.
//  Copyright (c) 2015 Compulsive Gamblers inc. All rights reserved.
//

#include "game.h"

void Game::displayHelp() {
    std::cout << std::endl << "Blackjack allows up to 5 player (might change) of human, computer players.  Either all or mixed." <<
                std::endl << "There are 52 cards per deck.  There is a limit of 8 decks in use." << std::endl;
}

void Game::setUpPlayers(std::vector<GamePlayer*> &gPlayers){
    //reset player count
    Player::_playerCount = 0;
    
    //Name, money, flags, computer/human
    if (_isDemoMode == true) {
        //default computer player names...
        
        std::cout << "In setUpPlayers(), before setting up players, player count is " << Player::_playerCount <<std::endl;
        
        while (Player::_playerCount < _numPlayers) {  //use iterators instead?
            std::string compName = generateName("COMP");
            gPlayers.push_back(new GamePlayer(compName, _MAX_CHARACTERS_FOR_NAME, 500, true));
            std::cout << "DEBUG: In game::setUpPlayers, new gameplayer setup...\n" << gPlayers.at(gPlayers.size() -1)->getName(false) << std::endl;
            
        }
    }
    else {
        do {
            std::string answeryn = getYNFromQuestion("Will this player be human (y/n)?");
            if (answeryn == "y") {
                std::cout << "Please enter a name upto " << _MAX_CHARACTERS_FOR_NAME << " characters long. Leave blank for default name: " << std::endl;
                
                std::string pName = getAlphaNumInput(_MAX_CHARACTERS_FOR_NAME, true);
                
                //Maybe ask to stop inputting names(for < 5 player games
                if (pName.empty())
                {
                    gPlayers.push_back(new GamePlayer());
                    std::cout << "Players name will be: " << gPlayers.at(gPlayers.size() - 1)->getName(false) << std::endl;
                }
                else {
                    //code for non empty names
                    std::cout << "Player" << Player::_playerCount << " will be ";
                    gPlayers.push_back(new GamePlayer(pName, _MAX_CHARACTERS_FOR_NAME,500, true));
                    std::cout << gPlayers.at(gPlayers.size() - 1)->getName(false) << std::endl;
                }
            }
            else {
                //enter code for computer player init
                std::string compName = generateName("COMP");
                gPlayers.push_back(new GamePlayer(compName, _MAX_CHARACTERS_FOR_NAME, 500, true));
            }
        } while (GamePlayer::_playerCount < _MAX_GAMEPLAYERS_ALLOWED);
    }
    std::cout << "DEBUG: GAME::setUpPlayers" << std::endl;
    std::cout << "After adding players in setUpPlayers(), player count is " << Player::_playerCount <<std::endl;
    for (auto p: gPlayers) {
        std::cout << *p << std::endl;
    }
    std::cout << "END Debug of GAME::SetupPlayers: SetupPlayers done..." << std::endl;
}


void Game::setIsDemoMode(bool val) {
    _isDemoMode = val;
}

void Game::setNumPlayers(int numPlayers = 5) {
    //_numPlayers = players.size();
}

/*!
 * @discussion Show as many or all variables in Game
 * @param none
 * @return none
 */
void Game::showDebug() {
    
    std::cout <<  std::endl << "IN GAME.DEBUG....for testing purposes only-------------------" << std::endl;
    //show demomode status
    std::cout << std::endl << "Demo mode:" << ((getIsInDemoMode()  == true ) ? "yes" : "no") << std::endl;
    //how many players allowed
    std::cout << "Maximum players allowed to play: " << _MAX_GAMEPLAYERS_ALLOWED << " including dealer." << std::endl;
    //how many players
    std::cout << "Players on table: " << _players.size() << std::endl;
    //players names
    int i = 0;
    for (auto p: _players) {
        std::cout << i + 1 << ": " << p->getName(false) << " $" << p->getMoney() << ". Player isSet:" << ((p->isInSession() == true) ? "yes" : "no") << std::endl;
        i++;
    }
    
        for (auto p: _players) {
            std::cout << *p << std::endl;
        }
    //players status's
    std::cout << "----------------------------------" << std::endl;
    
}

std::string Game::generateName(std::string name) {
    name.append(std::to_string(GamePlayer::_playerCount + 1));
    return  name;
}

void Game::setupDeck(int nDecks) {
    Deck d(nDecks);
    Deck *ptrDeck = new Deck(d);
    _deck = ptrDeck;
    _deck->print();
    std::cout << std::endl << "[InGame::setUpDeck]There are " << _deck->pileSize() << " cards in the deck" << std::endl;
    
}
void Game::dealCard(Player &player, bool faceup = true) {
    
    //for (auto pl: players) {
        if (player.isInSession() == true) {
            Card c = _deck->removeLastCard();
            //std::cout << "PILE SIZE is " << pl->getHand().pileSize();
            if (player.getHand(0).pileSize() == 1 && player.getName(false).compare("DEALER") == 0 ) //setting hidden card for dealing only!
                c.setFaceUp(false);
            else
                c.setFaceUp(faceup);
            
            player.addCardToHandFromDeck(c, 0);
        }
    //}
    //_deck->print();
    //std::cout << "After dealing cards, there are " << _deck->pileSize() << " cards left in the deck." << std::endl;
    
}

void Game::dealCardToAllPlayers(std::vector<Player*> players, bool faceUp = true) {
    const int ONE_CARD = 1;
    const int NO_CARDS = 0;
    for (auto p: players) {
        if (p->isInSession() == true) {
            Card card = _deck->removeLastCard();
            Hand plyrHand = p->getHand(NO_CARDS); //check for errors!!!!!!
            int handSize = plyrHand.pileSize();
            if (handSize == ONE_CARD && p->getName(false).compare("DEALER") == NO_CARDS ) //setting hidden card for dealing only!
                card.setFaceUp(false);
            else
                card.setFaceUp(faceUp);
            
            p->addCardToHandFromDeck(card, 0);
        }
    }
}

void Game::getBetsFromAllPlayers(std::vector<GamePlayer*> &p) {
    
    //do demo mode a.i. here for determining bets?
    std::cout << "DEBUG: getBetsFromAllPlayers" << std::endl;
    
    std::cout << "Players size is " << p.size() << std::endl;

    for (size_t pCounter = 0; pCounter < p.size(); pCounter++) {
        p[pCounter]->setPreBetMoney();
        
        const double MAX_ALLOWABLE_BET_FROM_PLAYER = p[pCounter]->getMaxBetAllowed(MIN_ALLOWABLE_BET, MAX_ALLOWABLE_BET);
        std::cout << p[pCounter]->getName(false) << " session status: " << p[pCounter]->isInSession() << std::endl;
        if (p[pCounter]->isInSession() == true) {
            std::cout << p[pCounter]->getName(false) << " has " << p[pCounter]->getMoney() << "." << std::endl;
            std::cout << "Please enter an amount upto " << MAX_ALLOWABLE_BET_FROM_PLAYER << std::endl;
            std::cout << "$";
            
            double bet;
            /*
             player will be allowed to input 0 in order to not play round.  min. bet should be five and max should be 500(or 50)
            */
            while ( (bet = getDoubleInput(false)) > MAX_ALLOWABLE_BET_FROM_PLAYER || (bet < 5 && bet > 0) ) {
                std::cout << "Type 0 to skip round or input a bet not more then " << MAX_ALLOWABLE_BET_FROM_PLAYER << ": ";
            }
            
            p[pCounter]->setBet(bet);

            if (bet == 0) {
                std::cout << p[pCounter]->getName(false) << " is out." << std::endl;
                p[pCounter]->setInSession(false);
                p[pCounter]->setBet(0);
            }
            std::cout << p[pCounter]->getName(false) << " before bet had " << p[pCounter]->getMoney() << " and after bet has ";
            std::cout << p[pCounter]->getMoney() << " - " << p[pCounter]->getBet() << " = " << p[pCounter]->getMoney() - p[pCounter]->getBet() << std::endl;
            p[pCounter]->setMoney(p[pCounter]->getMoney() - bet);
        }
        else {
            std::cout << p[pCounter]->getName(false) << " cannot bet less then min bet and is out." << std::endl;
            p[pCounter]->setInSession(false);
        }
    }
    //std::cout << "END";
    /* this method probably does too much.  It probably shouldn't change the session but return an error sentinel per player?
     May change getting all players bets to getting individual players bets, like a loop in main or from a fuction in main
     */
}

int Game::insurancePayout(std::vector<GamePlayer*> &gPlayers, Hand dealersHand) {
    
    const int BLACKJACK_FLAG = 21;
    const int GAME_GOES_ON_FLAG = 0;
    
    if (dealersHand.calculate() == BLACKJACK_FLAG) {
        for (auto gP: gPlayers) {
            if (gP->getHand(0).calculate() == BLACKJACK_FLAG) { //dealer and player have BJ
                if (gP->getInsuranceFlag() == true) {
                    std::cout << gP->getName(false) << " took insurance and wins even money! (2:1)" << std::endl;
                    std::cout << "BEFORE: $" << gP->getMoney() << std::endl;
                    gP->setResolvedInsurancePayout(gP->getBet() + gP->getInsuranceBet());
                    gP->setMoney(gP->getMoney() + gP->getBet() + gP->getInsuranceBet());
                    std::cout << "AFTER $" << gP->getMoney() << std::endl;
                }
                else {
                    std::cout << gP->getName(false) << " did not take insurance, therefore it's a push! (1:1)" << std::endl;
                    std::cout << "BEFORE: $" << gP->getMoney() << std::endl;
                    gP->setResolvedInsurancePayout(gP->getBet());
                    gP->setMoney(gP->getMoney() + gP->getBet());
                    std::cout << "AFTER $" << gP->getMoney() << std::endl;
                }
            }
            else { //dealer has BJ but player does not
                if (gP->getInsuranceFlag() == true) {
                    std::cout << gP->getName(false) << " took insurance, therefore " << gP->getName(false) << " loses bet, but get back insurance! (2:1)" << std::endl;
                    std::cout << "BEFORE: $" << gP->getMoney() << std::endl;
                    gP->setResolvedInsurancePayout((gP->getInsuranceBet() * 2));
                    gP->setMoney(gP->getMoney() + (gP->getInsuranceBet() * 2));
                    std::cout << "AFTER $" << gP->getMoney() << std::endl;
                }
                else {
                    std::cout << gP->getName(false) << " did not take insurance, and loses bet as a result." << std::endl;
                    gP->setResolvedInsurancePayout(0);
                    std::cout << "MONEY: $" << gP->getMoney() << std::endl;
                }
            }
        }
        return BLACKJACK_FLAG;
    }
    else { //dealer does not have BJ
        std::cout << "Dealer does not have BlackJack..." << std::endl;
        for (auto gP: gPlayers) {
            if (gP->getHand(0).calculate() == BLACKJACK_FLAG) { //dealer does not have BJ, player does have BJ
                std::cout << gP->getName(false) << " has BlackJack and wins bet at 3:2 payout" << std::endl;
                std::cout << "BEFORE: $" << gP->getMoney() << std::endl;
                gP->setMoney(gP->getMoney() + (gP->getBet() * 2 ));
                std::cout << "AFTER $" << gP->getMoney() << std::endl;
                //set player session to false because he already won, other players can continue
                gP->setInSession(false);
            }
            else { //neither dealer or player have BJ
                if (gP->isInSession()) {
                    std::cout << gP->getName(false) << " and Dealer do not have BlackJack, checking for special plays..." << std::endl;
                }
                else
                    std::cout << gP->getName(false) << " not in play" << std::endl;
            }
        }
    }
        //game goes on
    return GAME_GOES_ON_FLAG;
}

void Game::getInsuranceFromPlayers(std::vector<GamePlayer*> &gPlayers) {
    //gets the insurance answer from the players and sets the insurance flag & insurance bet.
    
    for (auto gp: gPlayers) {

        if (gp->isInSession() == true) {
            std::cout << std::endl;
            std::cout << gp->getName(false) << ": " << std::endl;
            std::string question = "Would you like insurance? ";
            std::cout << "Your insurance will be 1/2 of your bet. i.e.";
            std::cout << "BET: $" << gp->getBet() << " | " << "INSURANCE BET: $" << gp->getBet() / 2 << std::endl;
            std::string answer = getYNFromQuestion(question);
            if (answer == "y") {
                gp->setInsuranceFlag(true);
                gp->implementInsuranceBet();
            }
            else
                gp->setInsuranceFlag(false);
        }
    }
}

void Game::getInsuranceFromPlayer(GamePlayer &p) {
    std::string question = p.getName(false) + ", would you like insurance? ";
    std::string answer = getYNFromQuestion(question);
    if (answer == "y") {
        std::cout << p.getName(false) << " wants insurance.";
        p.setInsuranceFlag(true);
    }
    else {
        std::cout << p.getName(false) << " does not want insurance.";
        p.setInsuranceFlag(false);
    }
}

void Game::getBetFromPlayer(GamePlayer &p) {
    const double MAX_ALLOWABLE_BET_FROM_PLAYER = p.getMaxBetAllowed(MIN_ALLOWABLE_BET, MAX_ALLOWABLE_BET);
    
    if (p.isInSession() == true) {
        std::cout << p.getName(false) << " has " << p.getMoney() << "." << std::endl;
        std::cout << "Please enter an amount upto " << MAX_ALLOWABLE_BET_FROM_PLAYER << std::endl;
        std::cout << "$";
        
        double bet;
        /*
         player will be allowed to input 0 in order to not play round.  min. bet should be five and max should be 500(or 50)
         */
        while ( (bet = getDoubleInput(false)) > MAX_ALLOWABLE_BET_FROM_PLAYER || (bet < 5 && bet > 0) ) {
            std::cout << "Type 0 to skip round or input a bet not more then " << MAX_ALLOWABLE_BET_FROM_PLAYER << ": ";
        }
        if (bet == 0) {
            std::cout << p.getName(false) << " is out." << std::endl;
            p.setInSession(false);
        }
        std::cout << p.getName(false) << " after a bet of " << p.getBet() << " has " ;
        p.setMoney(p.getMoney() - bet);
        std::cout << p.getMoney() << "." << std::endl;
    }
    else {
        std::cout << p.getName(false) << " cannot bet the min bet and is out." << std::endl;
        p.setInSession(false);
    }
}

void Game::printGame(std::vector<GamePlayer*> &gPlayers, DealerPlayer dealer) const {
    for (auto gp: gPlayers) {
        std::cout << *gp << std::endl;
    }
    
    std::cout << dealer << std::endl;
}

int Game::buildPlayOptionForPlayerAndReturnChoice(GamePlayer &gPlayer) {
    
    const int TWO_CARDS = 2;
    
    Menu optionsMenu;
    std::string header = "Here are your options: ";
    std::vector<std::string> options;
    int choice;
    
    if (gPlayer.isInSession() == true) { //default values as long as player is still in the game(hit, stand)
        options.push_back("Hit");
        options.push_back("Stand");
        
        if (gPlayer.getMoney() >= gPlayer.getBet()) {  //double down/splitting requires at least same amount as bet
            if (gPlayer.getHand(0).pileSize() == TWO_CARDS) {
                options.push_back("Double down");
            }
            if (gPlayer.getHand(0).getIndividualCard(0) == gPlayer.getHand(0).getIndividualCard(1) && gPlayer.getHand(0).pileSize() == TWO_CARDS) {
                options.push_back("Split");
            }
        
        } //else player does not have enough money to make any addition bets/plays
        optionsMenu.setHeader(header);
        optionsMenu.setOptions(options);
        choice = optionsMenu.displayAndGetChoice();
    }
    
    return choice;
}

bool Game::isInsuranceRequired(const std::vector<GamePlayer*> &gPlayers, Hand dealersHand) {
    bool askForInsurance = false;
    
    std::cout << "DEALERS HAND: " << dealersHand << std::endl;
    
    Card dealersUpCard = dealersHand.getIndividualCard(0);      //LEARN HOW TO PROGRAM WITH CONSTS!!!
    Card dealersHoleCard = dealersHand.getIndividualCard(1);   //LEARN HOW TO PROGRAM WITH CONSTS!!!
    
    const int TEN_CARD = 10;
    const int ACE = 1;
    
    std::cout << "Dealers up card is " << dealersUpCard << ". And the number is " << dealersUpCard.getCardValue() << std::endl;
    std::cout << "Dealers hole card is " << dealersHoleCard << ". And its value is " << dealersHoleCard.getCardValue() << std::endl;
    
    if (dealersUpCard.getCardValue() == TEN_CARD || dealersUpCard.getCardValue() == ACE)  { //if dealer has 10 or ACE as UP card
        std::cout << "Dealer might have a BlackJack! Dealer will ask for insurance." << std::endl;
        askForInsurance = true;
    }
    else
        askForInsurance = false;
    
    return askForInsurance;
}