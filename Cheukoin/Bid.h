#ifndef __Cheukoin_Bid__
#define __Cheukoin_Bid__

#include "Constants.h"

class Bid {
public:
    Bid(Suit suit, int amount);
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