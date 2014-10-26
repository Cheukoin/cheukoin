#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Bid.h"

class Rules;
class Trick;
class Player;
class Team;
class Lobby;
class Bot;
class Human;

class Game {
public:
    Game(Lobby& lobby, GameMode const& mode);

    void startGame();

    GameMode getMode();

    void setBid(Bid const& bid);
    Bid getBid();

    Lobby& getLobby();

    void addTrick(Trick const& trick);

    Trick& getCurrentTrick();

    std::shared_ptr<Rules> getRules();

    std::vector<std::shared_ptr<Bot> > getBots();
    std::shared_ptr<Human> getHuman();
    std::shared_ptr<Player> getCurrentPlayer();

    void notifyHumanPlayed();

    void draw();

    void play();

private:
    GameMode const& _mode;
    Bid _bid;
    Lobby& _lobby;
    std::vector<Trick> _tricks;
    int _currentRound;
    int _currentPlayer;
    std::shared_ptr<Rules> _rules;

    void _initializeRound();
    void _goToNextPlayer();
};

#endif