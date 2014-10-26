#include "Trick.h"
#include "Lobby.h"

using namespace std;

Trick::Trick(int number)
    : _number(number)
    , _cards(vector<Card>())
{
}

Trick::~Trick()
{
}

void Trick::setNumber(int number)
{
    _number = number;
}

int Trick::getNumber()
{
    return _number;
}

void Trick::addCard(Card const& card)
{
    _cards.push_back(card);
}

vector<Card> Trick::getCards()
{
    return _cards;
}

void Trick::draw()
{
    for (auto card : _cards) {
        card.draw();
    }
}

int Trick::getWinnerCardIndex()
{
    vector<Card> sortedCards = _cards;
    sort(sortedCards.begin(), sortedCards.end(), [](Card a, Card b) {
        return Application::getInstance().getGame()->getRules()->isCardGreater(a, b);
    });

    auto best = find(_cards.begin(), _cards.end(), sortedCards.front());
    long bestIndex = best - _cards.begin();

    return (int)bestIndex;
}