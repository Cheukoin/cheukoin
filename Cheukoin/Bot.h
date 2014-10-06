#include <map>
#include <string>
#include "Player.h"

class Bot : Player {
public:
    Bot();
    ~Bot();

private:
    std::map<char, vector<Card> > _remainingCardsInGame;
};
