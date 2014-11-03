#include "Team.h"

using namespace std;

Team::Team(string name, Player player1, Player player2)
    : _name(name)
    , _gameScore(0)
    , _players(vector<shared_ptr<Player> >())
{
    _players.push_back(make_shared<Player>(player1));
    _players.push_back(make_shared<Player>(player2));
}

Team::~Team()
{
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

bool Team::isTeamWinning(Trick& trick)
{
    Card winningcard = trick.getWinningCard();
    return (_players.front()->getPlayedCard() == winningcard || _players.back()->getPlayedCard() == winningcard);
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
    for (auto p : getPlayers()) {
        if (p->isDealer()) {
            dealing = true;
        }
    }
    return dealing;
}

bool Team::isPlayerInTeam(Player const& player)
{
    return (_players.front()->getName() == player.getName() || _players.back()->getName() == player.getName());
}