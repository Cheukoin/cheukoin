#include "Team.h"

using namespace std;

Team::Team(string name)
    : _name(name)
    , _gameScore(0)
    , _players(vector<shared_ptr<Player> >())
{
}

Team::~Team()
{
}

void Team::addPlayer(Bot const& bot)
{
    if (_players.size() < 2) {
        _players.push_back(make_shared<Bot>(bot));
    }
}

void Team::addPlayer(Human const& human)
{
    if (_players.size() < 2) {
        _players.push_back(make_shared<Human>(human));
    }
}

void Team::addWonTrick(Trick const& trick)
{
    _wonTricks.push_back(trick);
}

void Team::setScore(int const& newScore)
{
    _gameScore = newScore;
}

void Team::addPoints(int const& score)
{
    _gameScore += score;
}

int Team::getScore()
{
    return _gameScore;
}

vector<Trick> Team::getTricks()
{
    return _wonTricks;
}

vector<shared_ptr<Player> > Team::getPlayers()
{
    return _players;
}

bool Team::isTeamDealing()
{
    bool dealing = false;
    for (auto p : _players) {
        if (p->isDealer()) {
            dealing = true;
        }
    }
    return dealing;
}