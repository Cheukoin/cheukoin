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

    auto team = _game->getLobby()->getTeamForPlayer(*this);
    auto enemyTeam = _game->getLobby()->getTeamForPlayer(*this, true);

    _friend = *(*team->getPlayers().at(0) != *this ? team->getPlayers().at(0) : team->getPlayers().at(1));
    _enemy1 = *enemyTeam->getPlayers().at(0);
    _enemy2 = *enemyTeam->getPlayers().at(1);

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
    Card card = _game->getCurrentTrick().getCards().back();
    _remainingCardsInGame.erase(remove(_remainingCardsInGame.begin(), _remainingCardsInGame.end(), card), _remainingCardsInGame.end());

    if (card.getSuit() == _game->getBid().getSuit()) {
        _remainingAssets.erase(remove(_remainingAssets.begin(), _remainingAssets.end(), card), _remainingAssets.end());
    }

    if (card != _playedCard) {
        _cardProbability[card.getSuit()][card.getValue()][_friend.getName()] = 0;
        _cardProbability[card.getSuit()][card.getValue()][_enemy1.getName()] = 0;
        _cardProbability[card.getSuit()][card.getValue()][_enemy2.getName()] = 0;
    }
    _guessHands();
}

Card Bot::chooseCard()
{
    vector<Card> playableCards = _game->getRules()->getPlayableCards(*this);
    return playableCards.front();
}

int Bot::_playerCountThatMayHave(Suit suit, Value value)
{
}

void Bot::_playerHasNoMore(string name, Suit suit)
{
    for (int value = 0; value < 8; ++value) {
        float previousProba = _cardProbability[suit][(Value)value][name];
        _cardProbability[suit][(Value)value][name] = 0;
        int playerCount = _playerCountThatMayHave(suit, (Value)value);
    }
}

void Bot::_guessHands()
{
    Card card = _game->getCurrentTrick().getCards().back();
    shared_ptr<Player> player = _game->getCurrentPlayer();
    Suit askedSuit = _game->getCurrentTrick().getCards().front().getSuit();
    Suit asset = _game->getBid().getSuit();

    if (card.getSuit() != askedSuit) {
        _playerHasNoMore(player->getName(), askedSuit);
    }
}
