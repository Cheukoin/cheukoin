#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Bid.h"

class Trick;
class Player;
class Team;
class Lobby;
class Bot;

class Game {
public:
    Game(Lobby& lobby, GameMode const& mode);

    void startGame();

    GameMode getMode();

    void setBid(Bid const& bid);
    Bid getBid();

    Lobby& getLobby();

    void addTrick(Trick const& trick);
    std::vector<Trick> getTricks();
    Trick getCurrentTrick();

private:
    GameMode const& _mode;
    Bid _bid;
    Lobby& _lobby;
    std::vector<Player> _players;
    std::vector<Trick> _tricks;
};

#endif