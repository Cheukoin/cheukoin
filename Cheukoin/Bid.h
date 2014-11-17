#ifndef __Cheukoin_Bid__
#define __Cheukoin_Bid__

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "ResourcePath.h"

class Bid {
public:
    Bid(Suit suit, int amount, std::string playerName);
    Bid();
    ~Bid();

    void setAmount(int amount);
    int getAmount();

    void setSuit(Suit suit);
    Suit getSuit();

    std::string getPlayerName();

private:
    int _amount;
    Suit _suit;
    std::string _playerName;
};

#endif
