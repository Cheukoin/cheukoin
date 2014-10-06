#include <map>
#include <string>
#include "Player.h"

class Bot : Player {
public:
    Bot();
    ~Bot();

private:
    std::map<Suit, std::vector<Card> > _remainingCardsInGame;
};
