#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

#include <vector>

#include "Constants.h"

class Trick;
class Player;
class Bid;

class Game {
public:
    static Game& getInstance();

    void setMode(GameMode mode);
    GameMode getMode();

    void setBid(Bid* const& bid);
    Bid* getBid();

    void addPlayer(Player*& player);
    std::vector<Player*> getPlayers();

    void addTrick(Trick* const& trick);
    std::vector<Trick*> getTricks();
    Trick* getCurrentTrick();

private:
    Game(){};
    Game(Game const&);
    void operator=(Game const&);

    GameMode _mode;
    Bid* _bid;
    std::vector<Player*> _players;
    std::vector<Trick*> _tricks;
};

#endif