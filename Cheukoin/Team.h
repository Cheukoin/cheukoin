#ifndef __Cheukoin_Team__
#define __Cheukoin_Team__

#include <string>
#include <memory>

#include "Trick.h"
#include "Bot.h"
#include "Human.h"
#include "Player.h"
#include "Score.h"

class Team {
public:
    Team(std::string name);
    ~Team();

    void addPlayer(Human const& human);
    void addPlayer(Bot const& bot);

    void addWonTrick(Trick const& trick);
    void setScore(int const& newScore);
    void updateScore();
    int getScore();
    std::vector<Trick> getTricks();
    int computeScore(Trick& trick);

    std::vector<std::shared_ptr<Player> > getPlayers();
    bool isTeamDealing();

    bool isPlayerInTeam(Player const& player);

private:
    std::string _name;
    std::vector<std::shared_ptr<Player> > _players;
    int _gameScore;
    std::vector<int> _totalScore;
    std::vector<Trick> _wonTricks;
};

#endif
