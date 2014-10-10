#ifndef __Cheukoin_Bid__
#define __Cheukoin_Bid__

#include "Constants.h"

class Game;
class Card;

class Bid {
public:
    Bid();
    ~Bid();
    int getAmount();
    void setAmount(int amount);
    void setSuit(Suit suit);
    Suit getSuit();
    bool isBidValid(Bid previousBid);

private:
    int _amount;
    Suit _suit;
};

#endif