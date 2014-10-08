#include <string>
#include "Bid.h"
#include "Hand.h"

class Player {
public:
    Player();
    ~Player();
    void playCard(Card card);
    Bid makeBid(int amount, std::string asset);
    std::string getName();
    void setName(std::string name);

private:
    std::string _name;
    Hand _hand;
    Bid _bid;
};
