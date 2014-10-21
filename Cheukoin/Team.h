#ifndef __Cheukoin_Team__
#define __Cheukoin_Team__

#include <string>
#include <memory>

#include "Trick.h"
#include "Bot.h"

class Team {
public:
    Team();
    Team(std::string name);
    ~Team();
    void addPlayer(Bot const& player);
    void addWonTrick(Trick const& trick);
    void setScore(int const& newScore);
    void addPoints(int const& score);
    int getScore();
    std::vector<Trick> getTricks();

    std::vector<std::shared_ptr<Player> > getPlayers();
    bool isTeamDealing();

private:
    std::string _name;
    std::vector<std::shared_ptr<Player> > _players;
    int _score;
    std::vector<Trick> _wonTricks;
};

#endif
