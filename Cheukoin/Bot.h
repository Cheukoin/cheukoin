#include <map>
#include <string>
#include "Player.h"

class Bot : public Player {
public:
    Bot();
    ~Bot();

    void play();
    Card chooseCard();

private:
    std::vector<Card> _remainingCardsInGame;
    std::vector<Card> _remainingAssets;
};
