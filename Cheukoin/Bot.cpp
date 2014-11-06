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
        if (card.getSuit() == _game->getBid()->getSuit()) {
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

    if (card.getSuit() == _game->getBid()->getSuit()) {
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

    if (_game->getCurrentTrick().getCards().size() == 0) {
        // the bot is the first player
        cout << "remaining assets : " << _remainingAssets.size() << endl;
        if (_remainingAssets.size() == 0) {
            // no more asset in game : we return the first card which is master at its suit, if exists
            for (Card card : playableCards) {
                if (_isCardMaster(card)) {
                    return card;
                }
            }
        }
        else if (_remainingAssets.size() == Rules::cardsForSuit(_cards, _game->getBid()->getSuit()).size()) {
            // bot is the only one with assets
        }
        else {
            // somebody else has assets
        }
    }
    else {
        // there are cards in the trick
    }

    return playableCards.front();
}

bool Bot::_isCardMaster(Card card)
{
    for (int i = 0; i < (int)card.getValue(); ++i) {
        if (i != (int)card.getValue() && _game->getRules()->isCardGreater(Card(card.getSuit(), (Value)i), card, card.getSuit()) && _playersThatMayHave(card.getSuit(), (Value)i).size() != 0) {
            cout << card << " is not master" << endl;
            return false;
        }
    }
    cout << card << " is master" << endl;
    return true;
}

vector<Player> Bot::_playersThatMayHave(Suit suit, Value value)
{
    vector<Player> players = { _friend, _enemy1, _enemy2 };
    vector<Player> result;
    for (Player& player : players) {
        if (_cardProbability[suit][value][player.getName()] != 0) {
            result.push_back(player);
        }
    }
    return result;
}

void Bot::_playerHasNoMore(string name, Suit suit)
{
    for (int value = 0; value < 8; ++value) {
        float previousProba = _cardProbability[suit][(Value)value][name];
        _cardProbability[suit][(Value)value][name] = 0;
        vector<Player> playersToAdjust = _playersThatMayHave(suit, (Value)value);
        for (Player& player : playersToAdjust) {
            _cardProbability[suit][(Value)value][player.getName()] += previousProba / playersToAdjust.size();
        }
    }
}

void Bot::_guessHands()
{
    Card card = _game->getCurrentTrick().getCards().back();
    shared_ptr<Player> player = _game->getCurrentPlayer();
    Suit askedSuit = _game->getCurrentTrick().getCards().front().getSuit();

    if (card.getSuit() != askedSuit) {
        _playerHasNoMore(player->getName(), askedSuit);
    }
}
