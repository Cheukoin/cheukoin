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
    void playBot();
    void addTrick(Trick const& trick);

    Trick& getCurrentTrick();

    std::vector<std::shared_ptr<Bot> > getBots();
    std::shared_ptr<Player> getCurrentPlayer();
    int getIndexCurrentPlayer();
    void setIndexCurrentPlayer(int i);
    void draw();

    void play();

private:
    GameMode const& _mode;
    Bid _bid;
    Lobby& _lobby;
    std::vector<Trick> _tricks;
    int _currentRound;
    int _currentPlayer;
};

#endif