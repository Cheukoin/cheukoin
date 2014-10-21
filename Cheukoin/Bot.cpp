#include "Bot.h"

using namespace std;

Bot::Bot(string name, Position position)
    : Player(name, position)
    , _cardProbability()
{
}

Bot::~Bot()
{
}

void Bot::initialize()
{
    Player::initialize();

    _game = Application::getInstance().getGame();

    Team team = _game->getLobby().getTeamForPlayer(*this);
    Team enemyTeam = _game->getLobby().getTeamForPlayer(*this, true);

    _friend = *(*team.getPlayers().at(0) != *this ? team.getPlayers().at(0) : team.getPlayers().at(1));
    _enemy1 = *enemyTeam.getPlayers().at(0);
    _enemy2 = *enemyTeam.getPlayers().at(1);

    for (Card card : Card::getAllCards()) {
        _remainingCardsInGame.push_back(card);
        if (find(_cards.begin(), _cards.end(), card) == _cards.end()) {
            _cardProbability[card.getSuit()][card.getValue()][_friend.getName()] = 0.33f;
            _cardProbability[card.getSuit()][card.getValue()][_enemy1.getName()] = 0.33f;
            _cardProbability[card.getSuit()][card.getValue()][_enemy2.getName()] = 0.33f;
        }
        if (card.getSuit() == _game->getBid().getSuit()) {
            _remainingAssets.push_back(card);
        }
    }
}

void Bot::play()
{
    Card nextCard = chooseCard();
    playCard(nextCard);
}

void Bot::update()
{
    for (Card card : _game->getCurrentTrick().getCards()) {
        _remainingCardsInGame.erase(remove(_remainingCardsInGame.begin(), _remainingCardsInGame.end(), card), _remainingCardsInGame.end());

        if (card.getSuit() == _game->getBid().getSuit()) {
            _remainingAssets.erase(remove(_remainingAssets.begin(), _remainingAssets.end(), card), _remainingAssets.end());
        }

        if (card != _playedCard) {
            _cardProbability[card.getSuit()].erase(card.getValue());
        }
    }
    guessHands();
}

Card Bot::chooseCard()
{
    return _cards.front();
}

void Bot::guessHands()
{
}