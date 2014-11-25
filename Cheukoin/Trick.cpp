#include "Trick.h"
#include "Lobby.h"

using namespace std;

Trick::Trick()
    : _cards(vector<Card>())
{
}

Trick::~Trick()
{
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
    sort(sortedCards.begin(), sortedCards.end(), [this](Card a, Card b) {
        return a.isGreaterThan(b, _cards.front().getSuit());
    });

    auto best = find(_cards.begin(), _cards.end(), sortedCards.front());

    return (int)(best - _cards.begin());
}

Card Trick::getWinningCard()
{
    return _cards[getWinnerCardIndex()];
}
