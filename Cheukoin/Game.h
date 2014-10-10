#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

#include <vector>

#include "Bid.h"
#include "Player.h"
#include "Trick.h"

class Game {
public:
    static Game& getInstance();

    void setBid(Bid const& bid);
    Bid getBid();

    void addPlayer(Player& player);
    std::vector<Player> getPlayers();

    void addTrick(Trick const& trick);
    std::vector<Trick> getTricks();

private:
    Game(){};
    Game(Game const&); // Don't Implement
    void operator=(Game const&); // Don't implement\

    Bid _bid;
    std::vector<Player> _players;
    std::vector<Trick> _tricks;
};

#endif