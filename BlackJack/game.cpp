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
        } while (GamePlayer::_playerCount < _numPlayers);
    }
    /*
    std::cout << "DEBUG: GAME::setUpPlayers" << std::endl;
    std::cout << "After adding players in setUpPlayers(), player count is " << Player::_playerCount <<std::endl;
    for (auto p: gPlayers) {
        std::cout << *p << std::endl;
    }
    std::cout << "END Debug of GAME::SetupPlayers: SetupPlayers done..." << std::endl;
    */
}


void Game::setIsDemoMode(bool val) {
    _isDemoMode = val;
}

void Game::setNumPlayers(int numPlayers = 5) {
    _numPlayers = numPlayers;
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

/**
 Prepare the decks. 
 @param nDecks (int) the number of decks to setup
 @param randomize (bool) Defaults to true for actual release. Set to false for DEBUGGING
*/
void Game::setupDeck(int nDecks, bool randomize = true) {
    Deck d(nDecks);
    _deck = d;
    //Deck *deckPtr = new Deck(d);
    //_deck = deckPtr;
    _deck.print();
    std::cout << std::endl << "[InGame::setUpDeck]There are " << _deck.pileSize() << " cards in the deck" << std::endl;
    
}

void Game::dealCard(Player &player, bool faceup = true) {
    
    //for (auto pl: players) {
        if (player.isInSession() == true) {
            Card c = _deck.removeLastCard();
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
            Card card = _deck.removeLastCard();
            Hand plyrHand = p->getHand(NO_CARDS); //check for errors!!!!!!
            int handSize = plyrHand.pileSize();
            if (handSize == ONE_CARD && p->getName(false).compare("DEALER") == NO_CARDS ) //setting hidden card for dealing only!
                card.setFaceUp(false);
            else
                card.setFaceUp(faceUp);
            
            p->addCardToHandFromDeck(card, 0);
        }
    }
    std::cout << "DEBUG: game::dealcardstoallplayers: END OF METHOD" << std::endl;
}

void Game::getBetsFromAllPlayers(std::vector<GamePlayer*> &p) {
    
    //do demo mode a.i. here for determining bets?
    std::cout << "DEBUG: Game::getBetsFromAllPlayers start" << std::endl;
    
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
            while ( (bet = getDoubleInput(false)) > MAX_ALLOWABLE_BET_FROM_PLAYER || (bet > 0 && bet < 5) ) {
                std::cout << "Type 0 to skip round or input a bet more then $" << MIN_ALLOWABLE_BET << " and upto $" << MAX_ALLOWABLE_BET_FROM_PLAYER << ": ";
            }
            
            p[pCounter]->setBet(bet);

            if (bet == 0) {
                std::cout << p[pCounter]->getName(false) << " is out." << std::endl;
                p[pCounter]->setInSession(false);
                p[pCounter]->setBet(0);
            }
            std::cout << p[pCounter]->getName(false) << " before bet had " << p[pCounter]->getMoney() << " and after bet has ";
            std::cout << p[pCounter]->getMoney() << " - " << p[pCounter]->getBet() << " = " << p[pCounter]->getMoney() - p[pCounter]->getBet() << std::endl;
            p[pCounter]->setMoney(p[pCounter]->getMoney() - p[pCounter]->getBet());
        }
        else {
            std::cout << p[pCounter]->getName(false) << "is not in session and therefore cannot participate." << std::endl;
            p[pCounter]->setInSession(false);
        }
    }
    //std::cout << "END";
    /* this method probably does too much.  It probably shouldn't change the session but return an error sentinel per player?
     May change getting all players bets to getting individual players bets, like a loop in main or from a fuction in main
     */
    //std::cout << "DEBUG: game::getBetsFromAllPlayers: at the end of getbetsfromallplayers, money is " << p[0]->getMoney() << std::endl;
}

void Game::getInsuranceFromPlayers(std::vector<GamePlayer*> &gPlayers) {
    //gets the insurance answer from the players and sets the insurance flag & insurance bet.
    
    for (auto gp: gPlayers) {

        if (gp->isInSession() == true && gp->getMoney() >= gp->getBet() ) {
            std::cout << std::endl;
            std::cout << gp->getName(false) << ": " << std::endl;
            std::string question = "Would you like insurance? ";
            std::cout << "Your insurance will be 1/2 of your bet. i.e.\n";
            std::cout << "BET: $" << gp->getBet() << " | " << "INSURANCE BET: $" << gp->getBet() / 2 << std::endl;
            std::string answer = getYNFromQuestion(question);
            if (answer == "y") {
                gp->setInsuranceFlag(true);
                gp->implementInsuranceBet(); //does not alter player.money
            }
            else
                gp->setInsuranceFlag(false);
        }
        else {
            std::cout << gp->getName() << " cannot get insurance.  He/she has $" << gp->getMoney() << " and has a current bet of $" << gp->getBet() << std::endl;
        }
    }
}

void Game::getInsuranceFromPlayer(GamePlayer &p) {
    if (p.isInSession() == true && p.getMoney() >= p.getBet()) {
        std::string question = p.getName(false) + ", would you like insurance? ";
        std::cout << "Your insurance will be 1/2 of your bet. i.e.\n";
        std::cout << "BET: $" << p.getBet() << " | " << "INSURANCE BET: $" << p.getBet() / 2 << std::endl;
        std::string answer = getYNFromQuestion(question);
        if (std::tolower(answer[0]) == 'y') {
            std::cout << p.getName(false) << " wants insurance.";
            p.setInsuranceFlag(true);
            p.implementInsuranceBet();
        }
        else {
            std::cout << p.getName(false) << " does not want insurance.";
            p.setInsuranceFlag(false);
        }
    }
    else {
        std::cout << p.getName() << " cannot get insurance.  He/she has $" << p.getMoney() << " and has a current bet of $" << p.getBet() << std::endl;
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

bool Game::isInsuranceRequired(const std::vector<GamePlayer*> &gPlayers, Hand dealersHand) {
    bool askForInsurance = false;
    std::cout << "DEBUG: game.isInsuranceRequired" << std::endl;
    std::cout << "DEALERS HAND: " << dealersHand << std::endl;
    
    Card dealersUpCard = dealersHand.getIndividualCard(0);      //LEARN HOW TO PROGRAM WITH CONSTS!!!
    Card dealersHoleCard = dealersHand.getIndividualCard(1);   //LEARN HOW TO PROGRAM WITH CONSTS!!!
    
    //removed because of rule clarification const int TEN_CARD = 10;
    const int ACE = 1;
    
    std::cout << "DEBUG: \nDealers up card is " << dealersUpCard << ". And the number is " << dealersUpCard.getCardValue() << std::endl;
    std::cout << "Dealers hole card is " << dealersHoleCard << ". And its value is " << dealersHoleCard.getCardValue() << std::endl;
    
    if (dealersUpCard.getCardValue() == ACE)  { //if dealer has ACE as UP card
        std::cout << "Dealer might have a BlackJack! Dealer will ask for insurance." << std::endl;
        askForInsurance = true;
    }
    else
        askForInsurance = false;
    
    std::cout << "END DEBUG: game.isInsuranceRequired" << std::endl;
    return askForInsurance;
}

int Game::resolveChoice(int choice, GamePlayer& player) {
    static int index = 0;  //index for players current hand
    
    switch (choice) {
        case PLAY_OPTIONS::HIT: {
            //add card from deck to players hand
            std::cout << "Player chose to hit to hand of index:" << index << std::endl;
            player.hit(getDeck().removeLastCard(), index); //should just add card, nothing else!
            std::cout << "DEBUG: Game.resolvechoice: HITcase: After hitting, hand is: " << player.getHand(index);
            player.displayHand();
            
            int result = player.getHand(index).calculate();
            if (result < 21) {
                std::cout << player.getName() << " can make more plays: " << std::endl;
                resolveChoice(player.buildPlayOptionForPlayerAndReturnChoice(), player);
            }
            else if (result > 21) {
                std::cout << player.getName() << " busted!" << std::endl;
                player.getHand(index).setBustedFlag(true);
            }
            else if (result == 21) { //soft 21
                std::cout << player.getName() << " has a soft 21! Player will be set to stand!" << std::endl;
                player.getHand(index).setStandFlag(true);
            }
            else {
                std::cout << "UNKNOWN/FORGOTTEN POSSIBILITY GOES HERE"  <<std::endl;
            }
            
            std::cout << "END OF PLAY_OPTIONS::HIT" << std::endl;
            break;
        }
        case PLAY_OPTIONS::STAND:
            
            std::cout << "Player chose to stand with " << player.getHand(index) << std::endl;
            //pause players session
            player.getHand(index).setStandFlag(true);
            calculatePlayerResult(player, index);
            player.stand();  //pause player session? or use hands status to determine session

            break;
        case PLAY_OPTIONS::DOUBLE_DOWN:
            //bet equivalent of another bet and pause players session
            std::cout << "Player chose to double down." << std::endl;
            player.doubleDown(getDeck().removeLastCard(), index);  //adds a card if there is enough money, removes money = to bet amount
            std::cout << player.getName() << "'s hand is :" << std::endl << player.getHand(index) << std::endl;
            calculatePlayerResult(player, index);
            player.getHand(index).setDoubledFlag(true);
            player.getHand(index).setStandFlag(true); //Cannot get any new cards after a double
            //return choice;
            break;
        case PLAY_OPTIONS::SPLIT:
            
            std::cout << "Player chose to split" << std::endl;
            
            for (int i = 0; i < player.getHands().size(); i++) {
                player.split(i); //
                player.getHand(i).addCard(_deck.removeLastCard()); //good
                player.getHand(i).setSplitFlag(true);
                player.getHand(i).showHandFlags(player.getHand(i));
                
                std::cout << "Players hands after splitting is: " << std::endl;
                std::cout << player.getHand(i) << " at index " << i << std::endl;
                
                index = i;
                const int EMPTY_CHOICE = 99;
                int choice = EMPTY_CHOICE;
                if (choice == EMPTY_CHOICE) {
                    choice = player.buildPlayOptionForPlayerAndReturnChoice();
                }
                
                resolveChoice(choice, player);
            }
        
        break;
        default:
            std::cout << "Unknown error in game.resolveChoice switch(choice)...exiting";
            exit(9);
            break;
    }
    
    std::cout << "Game::resolveChoice: returning choice " << choice << std::endl;
    return choice;
}

int Game::calculatePlayerResult(GamePlayer &g, int index) {
    int total = g.getHand(index).calculate();
    
    if (total > 21) {
        g.getHand(index).setBustedFlag(true);
        //g.setInSession(false); //maybe check in main
        return BUSTED;
    }
    else if (total == 21) {
        g.getHand(index).setBlackjackFlag(true);
        //g.setInSession(false);
        return BLACKJACK;
    }
    else {
        //check if player has enough money to play
        g.setInSession(true);
        return GAME_GOES_ON;
    }
    
    //return 0;

}

bool Game::getQuitAnswer() {
    if (stringToUpperLower(getYNFromQuestion("Round over, prepping new round, unless you want to quit? Quit?")) == "y") {
        std::cout << "Quitting..." << std::endl;
        setQuitSentinel(true);
    }
    else {
        setQuitSentinel(false);
    }
    return getQuitSentinal();
}

std::string Game::displayResult(const int resultOfHand)  {
    switch (resultOfHand) {
        case BUSTED:
            return "BUSTED";
            break;
        case BLACKJACK:
            return  "BLACKJACK";
            break;
        case GAME_GOES_ON:
            return "GAME_GOES_ON";
        default:
            return "UNKOWN result returned in GAME::displayResult";
            break;
    }
    
}

/**
    Compares 2 hands and returns int of winner or 3 if a push
    @return 1: if 1st hand is > 2nd hand.
    @return 2: if 1st hand is < 2nd hand.
    @return 0: if 1st hand is = 2nd hand.
 */
int Game::comparePlayerHands(Hand playersHand, Hand DealersHand) {
    const int HAND1_IS_GREATER = 1;
    const int HAND2_IS_GREATER = 2;
    const int HAND1_IS_BUSTED = 3;
    const int HANDS_ARE_EQUAL = 0;
    const int TWENTY_ONE = 21;
    int h1 = playersHand.calculate();
    int h2 = DealersHand.calculate();
    
    if (h1 > TWENTY_ONE  ) {
        return HAND1_IS_BUSTED;
    }
    else if (h1 > h2) {
        return HAND1_IS_GREATER;
    }
    else if (h1 == h2) {
        return HANDS_ARE_EQUAL;
    }
    else if (h1 < h2) {
        return HAND2_IS_GREATER;
    }
    else {
        return TWENTY_ONE;
    }
}

/**
 Prepares players for new round.  Checks players money to see if player can be in game, resests status based on sessions. Also removes all hands including dealers hand.
 */
void Game::preparePlayersForNewRound(std::vector<GamePlayer*>& gPlayer, DealerPlayer& dealer) {
    
    for (auto p: gPlayer) {
        p->setInsuranceFlag(false);
        p->setPreBetMoney();
        p->setResolvedInsurancePayout(0);
        p->setBet(0);
        
        if (p->isInSession() == false) {
            if (p->getMoney() < 5) {
                std::cout << p->getName() << " does not have enough money to participate. Deleting player..." << std::endl;
                std::cout << "DEBUG: GAME: preparePlayersForNewRound: Before player deletion, player count is " << gPlayer.size() << std::endl;
                //std::vector<Player>::iterator it = ( gPlayer.begin() + index );
                
                std::cout << "Player deleted, player count is : " << gPlayer.size() << std::endl;
            }
            else {
                std::cout << p->getName() << " has enough money to continue." << std::endl;
                p->getHands().erase(p->getHands().begin(), p->getHands().end());
                p->setInSession(true);
            }
        }
        else {
            std::cout << p->getName() << " is all good, continuing game." << std::endl;
            p->getHands().erase(p->getHands().begin(), p->getHands().end());
            p->setInSession(true);
        }

    }

    dealer.getHands().erase(dealer.getHands().begin(), dealer.getHands().end());
}

int Game::insurancePayout(std::vector<GamePlayer*> &gPlayers, Hand dealersHand) {
    //Player shouldn't be asked for insurance if he has BJ because it is unnessacary according to most forums/wikipedia
    const int BLACKJACK_FLAG = 21;
    const int GAME_GOES_ON_FLAG = 0;
    
    if (dealersHand.calculate() == BLACKJACK_FLAG) {
        for (auto gP: gPlayers) {
            if (gP->getHand(0).calculate() == BLACKJACK_FLAG) { //dealer and player have BJ (push w/ins.)
                if (gP->getInsuranceFlag() == true) {
                    payout(INSURANCE_PUSH, *gP);
                    //std::cout << gP->getName(false) << " took insurance and wins even money! (2:1)" << std::endl;
                    
                }
                else {
                    payout(NO_INSURANCE_PUSH, *gP);
                    //std::cout << gP->getName(false) << " did not take insurance, therefore it's a push! (1:1)" << std::endl; //dealer and player have BJ (push/no ins.)
                }
            }
            else { //dealer has BJ but player does not
                if (gP->getInsuranceFlag() == true) {
                    payout(INSURANCE_BJ, *gP);
                    //std::cout << gP->getName(false) << " took insurance, therefore " << gP->getName(false) << " loses bet, but gets back insurance! (2:1)" << std::endl;
                }
                else {
                    payout(NO_INSURANCE_BJ, *gP);
                    //std::cout << gP->getName(false) << " did not take insurance, and loses bet as a result." << std::endl;
                    
                }
            }
        }
        return BLACKJACK_FLAG; //game will start next round after payout
    }
    else { //dealer does not have BJ
        std::cout << "Dealer does not have BlackJack..." << std::endl;
        for (auto gP: gPlayers) {
            if (gP->getHand(0).calculate() == BLACKJACK_FLAG) { //dealer does not have BJ, player does have BJ
                std::cout << gP->getName(false) << " has BlackJack and wins bet at 3:2 payout" << std::endl;
                payout(BLACK_JACK, *gP);
            }
            else { //neither dealer or player have BJ
                if (gP->isInSession()) {
                    std::cout << gP->getName(false) << " and Dealer do not have BlackJack" << std::endl;//, checking for special plays..." << std::endl;
                }
                else
                    std::cout << gP->getName(false) << " not in play" << std::endl;
            }
        }
    }
    //game goes on
    return GAME_GOES_ON_FLAG;
}

/**
 Payouts dependant on type of bet
 Player wasn't asked for insurance if he had BJ because it is unnessacary according to most forums/wikipedia
 
 "The dealer will check to see if he has a 10-value card underneath his Ace, and if he does have Blackjack, your winning Insurance bet will be paid at odds of 2:1. You will still lose your original bet (unless you also have a Blackjack), so the net effect is that you break even (assuming you bet the full half bet for insurance.) This is why the bet is described as “insurance”, since it seems to protect your original bet against a dealer blackjack. Of course, if the dealer does not have blackjack, you’ll lose the insurance bet, and still have to play the original bet out."
 */
void Game::payout(PAYOUT_TYPE payoutType, GamePlayer& gPlayer) {
    //try making payouts outside of this method, this method should probably just set appropriate flags, called set payoutflags
    //also, probably don't need so many cases.  Put conditional statements for insurance.  
    std::string name = gPlayer.getName();
    for (int index = 0; index < gPlayer.getHands().size(); index++) {
    
        switch (payoutType) {
            case INSURANCE_PUSH:  //Dealer and player have BJ, player took insurance
                std::cout << "DEBUG: INSURANCE_PUSH" << std::endl;
                std::cout << name << " took insurance and has a 21 as does the dealer. Even money (2:1 payout)" << std::endl;
                gPlayer.setMoney(gPlayer.getMoney() + gPlayer.getBet() + gPlayer.getInsuranceBet()); //gets back bet + insurance bet
                gPlayer.getHand(index).setPushFlag(true);
                gPlayer.getHand(index).setBlackjackFlag(true);
                gPlayer.setInSession(false);
                break;
            case PUSH: //neither dealer or player have BJ, but both have same total
                std::cout << "DEBUG: PUSH" << std::endl;
                std::cout << name << " has " << gPlayer.getHand(index).calculate() << " as does the dealer. Push.(1:1 payout)" << std::endl;
                gPlayer.setMoney(gPlayer.getMoney() + gPlayer.getBet()); //gets back bet because of push
                gPlayer.getHand().setPushFlag(true);
                gPlayer.setInSession(false);
                break;
            case NO_INSURANCE_PUSH:  //Dealer and player have BJ, player did not take insurance
                std::cout << "DEBUG: NO_INSURANCE_PUSH" << std::endl;
                std::cout << name << " did not take insurance and has 21 as does the dealer. Push(1:1 payout)" << std::endl;
                
                gPlayer.setMoney(gPlayer.getMoney() + gPlayer.getBet()); //gets back bet because of push
                gPlayer.getHand(index).setBlackjackFlag(true);
                gPlayer.getHand(index).setPushFlag(true);
                gPlayer.setInSession(false);
                break;
            case INSURANCE_BJ: //dealer has BJ and player does not
                std::cout << "DEBUG: INSURANCE_BJ" << std::endl;
                std::cout << name << " took insurance and doesn't have BJ but dealer does. Lose bet but get back insurance @ (2:1 payout)" << std::endl;
                gPlayer.setMoney(gPlayer.getMoney() + (gPlayer.getInsuranceBet()*2)); //see method documentation
                gPlayer.getHand(index).setSimpleLossFlag(true);
                gPlayer.setInSession(false);
                gPlayer.setInsuranceBet(0);
                break;
            case NO_INSURANCE_BJ: //dealer has BJ but player does not
                std::cout << "DEBUG: NO_INSURANCE_BJ" << std::endl;
                std::cout << name << " did not take insurance and doesn't have BJ, but dealer does. Lose bet." << std::endl;
                //money already set
                gPlayer.setInSession(false);
                gPlayer.getHand(index).setSimpleLossFlag(true);
                break;
            case INSURANCE_NO_BJ://dealer doesn't have blackjack, neither does player, player has insurance
                std::cout << "DEBUG: INSURANCE_NO_BJ" << std::endl;
                std::cout << name << " took insurance, but no-one has BJ (lose insurance bet)" << std::endl;
                //No need to remove money, as it is already removed when implementing insurance
                //set flag?
                gPlayer.setInsuranceBet(0);
                break;
            case BLACK_JACK: //player has BJ
                std::cout << name << " has BJ. Dealer does not. (3:2 payout)" << std::endl;
                gPlayer.getHand(index).setBlackjackFlag(true);
                gPlayer.setInSession(false);
                gPlayer.setMoney(gPlayer.getMoney() + (gPlayer.getBet() * 2.5));
                break;
            case LOSE:
                std::cout << name << " did not win. Lose bet." << std::endl;
                //gPlayer.setMoney(gPlayer.getMoney() - gPlayer.getBet()); //player already has bet detucted
                gPlayer.getHand(index).setSimpleLossFlag(true);
                gPlayer.setInSession(false);
                break;
            case BUST:
                std::cout << name << " busted, loses bet" << std::endl;
                gPlayer.getHand(index).setSimpleLossFlag(true); //bust flag?
                gPlayer.setInSession(false);
                break;
            case WIN:
                if (gPlayer.getHand(index).getDoubledFlag()) {
                    std::cout << name << " wins with a doubled down hand for hand " << index << "  Win back bet. (3:1 payout)" << std::endl;
                    gPlayer.setMoney(gPlayer.getMoney() + (gPlayer.getBet() *2));
                }
                else {
                    std::cout << name << " wins. Win back bet. (2:1 payout)" << std::endl;
                    gPlayer.setMoney(gPlayer.getMoney() + (gPlayer.getBet() * 2));
                }
            
                gPlayer.getHand(index).setSimpleWinFlag(true);
                break;
            default:
                break;
        }
    }
    std::cout << name << " now has " << gPlayer.getMoney() << std::endl;
    std::cout << "DEBUG: END OF Game::payout()" << std::endl;
}