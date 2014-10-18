#ifndef __Cheukoin_Team__
#define __Cheukoin_Team__

#include <string>
#include "Trick.h"
#include "Player.h"

class Team {
public:
    Team();
    Team(std::string name);
    ~Team();
    void addPlayer(Player const& player);
    void addTrick(Trick const& trick);
    void setScore(int const& newScore);
    void addPoints(int const& score);
    int getScore();
    std::vector<Trick> getTricks();

    std::vector<Player> getPlayers() const;
    bool isTeamDealing();

private:
    std::string _name;
    std::vector<Player> _players;
    int _score;
    std::vector<Trick> _wonTricks;
};

#endif
