#include "Score.h"

using namespace std;

Score::Score()
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



