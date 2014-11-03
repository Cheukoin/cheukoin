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

int Team::computeScore(Trick& trick)
{
    if (trick.getCards().size() != 4) {
        cout << "Ce n'est pas une pli valide!" << endl;
    }
    else {
        int score = 0;
        Bid bid = Application::getInstance().getGame()->getBid();
        shared_ptr<Rules> rules = Application::getInstance().getGame()->getRules();
        for (Card c : trick.getCards()) {
            if (c.getSuit() == bid.getSuit()) {
                score += rules->getCardValuesAsset()[c.getValue()];
            }
            else {
                score += rules->getCardValues()[c.getValue()];
            }
        };
        return score;
    };
};

bool Team::isTeamWinning(Trick& trick){
    Card winningcard = trick.getWinningCard();
    return (_players[0]->getPlayedCard() == winningcard || _players[1]->getPlayedCard() == winningcard);
}

void Team::addWonTrick(Trick const& trick)
{
    _wonTricks.push_back(trick);
    updateScore();
}

void Team::setScore(int const& newScore)
{
    _gameScore = newScore;
}

int Team::getScore()
{
    return _gameScore;
}

void Team::updateScore()
{
    _gameScore += computeScore(_wonTricks.back());
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

bool Team::isPlayerInTeam(Player const& player)
{
    return (_players[0]->getName() == player.getName() || _players[1]->getName() == player.getName());
}