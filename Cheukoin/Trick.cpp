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

shared_ptr<Player> Trick::getWinner()
{
    return Application::getInstance().getGame()->getLobby().getPlayers().front();
}