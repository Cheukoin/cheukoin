#ifndef __Cheukoin_Bot__
#define __Cheukoin_Bot__

#include "Player.h"
#include "Card.h"
#include "Team.h"
#include "Lobby.h"

class Bot : public Player {
public:
    Bot(std::string name, Position position);
    ~Bot();

    virtual void initialize();
    virtual void play();

    Card chooseCard();
    void guessHands();

private:
    std::vector<Card> _remainingCardsInGame;
    std::vector<Card> _remainingAssets;
    // probability that a card is in a player's hand ({suit: {value: {player}}})
    std::map<Suit, std::map<Value, std::map<std::string, float> > > _cardProbability;

    Player _friend;
    Player _enemy1;
    Player _enemy2;

    std::shared_ptr<Game> _game;
};

#endif