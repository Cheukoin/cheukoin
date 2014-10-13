#ifndef __Cheukoin_Player__
#define __Cheukoin_Player__

#include <string>

#include "Bid.h"
#include "Hand.h"
#include "Card.h"
#include "Game.h"
#include "Trick.h"
#include "Constants.h"

class Player {
public:
    Player();

    void playCard(Card const& card);
    Bid makeBid(int amount, Suit const& asset);

    std::string getName();
    void setName(std::string name);
    Hand getHand();
    void setHand(Hand& hand);
    Bid getBid();
    void setBid(Bid& bid);
    void makeDealer();
    void changeDealer();
    bool isDealer();

protected:
    std::string _name;
    Hand _hand;
    Bid _bid;
    Game& _game = Game::getInstance();
    bool _dealer;
};

#endif