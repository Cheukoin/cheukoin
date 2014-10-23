#include "Score.h"

using namespace std;

Score::Score(Team const& team)
    : _biddingTeam(team)
{
}

Score::~Score()
{
}

Bid Score::getRetainedBid()
{
    return _retainedBid;
}

int Score::computeScore(Trick trick)
{
    if (trick.getCards().size() != 4) {
        cout << "Ce n'est pas une pli valide!" << endl;
    }
    else {
        
    }

    return -1;
}

void Score::addOutcome(string equipe, int score)
{
}

map<int, string> Score::getOutcome()
{
    return _gameOutcome;
}
