#include "Bot.h"

using namespace std;

Bot::Bot(string name, Position position)
    : Player(name, position)
{
}

Bot::~Bot()
{
}

void Bot::initialize()
{
    _game = Application::getInstance().getGame();

    Team team = _game->getLobby().getTeamForPlayer(*this);
    Team enemyTeam = _game->getLobby().getTeamForPlayer(*this, true);

    _friend = (team.getPlayers().at(0) != *this ? team.getPlayers().at(0) : team.getPlayers().at(1));
    _enemy1 = enemyTeam.getPlayers().at(0);
    _enemy2 = enemyTeam.getPlayers().at(1);

    for (Card card : Card::getAllCards()) {
        _remainingCardsInGame.push_back(card);
        _cardProbability[card.getSuit()][card.getValue()][_friend.getName()] = 0.33;
        _cardProbability[card.getSuit()][card.getValue()][_enemy1.getName()] = 0.33;
        _cardProbability[card.getSuit()][card.getValue()][_enemy2.getName()] = 0.33;
        if (card.getSuit() == _game->getBid().getSuit()) {
            _remainingAssets.push_back(card);
        }
    }
}

void Bot::play()
{
    Card nextCard = chooseCard();
    Player::playCard(nextCard);
}

Card Bot::chooseCard()
{
    return _cards[0];
}

void Bot::guessHands() {}