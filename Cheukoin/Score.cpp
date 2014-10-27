#include "Score.h"

using namespace std;

Score::Score(Team const& team)
    : _biddingTeam(team)
{
}

Score::~Score()
{
}

int Score::computeScore(Trick trick)
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

void Score::updateScore()
{
    for (int i = 0; i < Application::getInstance().getGame()->getLobby().getTeams().size(); i++) {
        Team team = Application::getInstance().getGame()->getLobby().getTeams()[i];
        if (Application::getInstance().getGame()->getCurrentTrick().getNumber() == team.getTricks().back().getNumber()) {
            int score = computeScore(Application::getInstance().getGame()->getCurrentTrick());
            _scores[i] += score;
        }
    }
};

void Score::displayScore()
{
}