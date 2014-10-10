#include "Score.h"

using namespace std;

Score::Score()
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
    if (trick.getComposition().size() != 4) {
        cout << "Ce n'est pas une pli valide!" << endl;
        return false;
    }
    else {
    }
}

void Score::addOutcome(string equipe, int score)
{
}

map<int, string> Score::getOutcome()
{
    return _gameOutcome;
}
