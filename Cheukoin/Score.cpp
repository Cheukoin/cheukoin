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
        Bid bid = Application::getInstance().getGame()->getBid();
        
    }

    return -1;
}

void Score::addOutcome(Team team, int score)
{
}

map<int, string> Score::getOutcome()
{
    return _gameOutcome;
}
