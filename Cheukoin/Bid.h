#ifndef __Cheukoin_Bid__
#define __Cheukoin_Bid__

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "ResourcePath.h"

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
    
    void displayNextButton();

private:
    int _amount;
    Suit _suit;
};

#endif