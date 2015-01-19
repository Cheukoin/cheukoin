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
		// LJ : Donc, pour les cartes qu'on a on ne crée par d'entrée dans la map, alors que pour les cartes jouées
		// LJ : il y aura une entrée dans la map, mais avec 0 en probabilité. Ce qui signifie qu'il va falloir gérer
		// LJ : deux situations pour le même effet, ça aurait été plus simple de mettre toutes les valeurs
        if (card.getSuit() == _game->getBid()->getSuit()) {
            _remainingAssets.push_back(card.getValue());
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
        _remainingAssets.erase(remove(_remainingAssets.begin(), _remainingAssets.end(), card.getValue()), _remainingAssets.end());
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
    vector<Card> playableCards = getPlayableCards();
    vector<Card> firstCards = _game->getCurrentTrick().getCards();
    Suit asset = _game->getBid()->getSuit();

    if (firstCards.size() == 0) {
        // the bot is the first player
        if (_remainingAssets.size() == 0 || _remainingAssets.size() == Rules::cardsForSuit(_cards, asset).size()) {
            // no more asset for other players
            if (_remainingAssets.size() == _cards.size()) {
                // bot only has assets : play them // LJ : C'est généralement une mauvaise idée
                return playableCards.front(); // LJ : Je ne vois pas le lien entre ce code et le commentaire juste au dessus

            }

            for (Card card : playableCards) {
                // play the first master card not asset
                if (card.getSuit() != asset && _isCardMaster(card)) {
                    return card;
                }
            }

            for (Card card : playableCards) {
                // bot has no master card except asset, play a not asset random one
                if (card.getSuit() != asset) {
                    return card;
                }
            }
        }
        else {
            // somebody else has assets

            // TODO : faire couper les autres, chercher ou son coequipier est maitre
        }
    }
    else {
        // there are cards in the trick

        // TODO : check de pas se faire couper, check des impasses

        for (Card card : playableCards) {
            if (card.getSuit() == firstCards.front().getSuit() && _isCardMaster(card) && !_playerCutsFor(_enemy1, card.getSuit()) && !_playerCutsFor(_enemy2, card.getSuit()) && !isFriendMaster()) {
                return card;
            }
        }
    }

    return playableCards.front();
}

bool Bot::_isCardMaster(Card card)
{
    vector<Card> firstCards = _game->getCurrentTrick().getCards();

    for (int i = 0; i <= 8; ++i) {
        if (Card(card.getSuit(), (Value)i).isGreaterThan(card, card.getSuit())
            && find(firstCards.begin(), firstCards.end(), card) != firstCards.end()) {
            return false;
        }
        else if (i != (int)card.getValue()
                 && Card(card.getSuit(), (Value)i).isGreaterThan(card, card.getSuit())
                 && _playersThatMayHave(card.getSuit(), (Value)i).size() != 0) {
            return false;
			// LJ : Trop simpliste : Si le joueur ayant encore la carte a déjà joué, ma carte est maître
        }
    }
    return true;
}

bool Bot::_playerCutsFor(Player player, Suit suit)
{
    for (int i = 0; i <= 8; ++i) {
        if (_cardProbability[suit][(Value)i][player.getName()] != 0) {
            return false;
        }
    }
    return true;
}

// LJ : Player étant une classe de base, et ayant une sémantique d'entité, faire un vector<player> n'est pas une bonne idée, car
// LJ : il copie les joueurs (d'ailleurs, il aurait été intéressant d'interdire la copie dans cette classe pour éviter cette
// LJ : situation qui n'ap as grand sens). Il vaudrait mieux faire un vector<Player*>.
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

void Bot::chooseBid()
{
    Suit asset = Clubs;
    int value = 0, amount;

    vector<Card> cards = getCards();
    map<Suit, vector<Card> > cardsPerSuit;

    for (auto card : cards) {
        cardsPerSuit[card.getSuit()].push_back(card);
    }

    for (int suit = 0; suit < 4; suit++) {
        amount = 0;

        if (hasCard(Card((Suit)suit, Jack)) && hasCard(Card((Suit)suit, Nine))) {
            amount = 90;
        }
        else if (hasCard(Card((Suit)suit, Jack)) || hasCard(Card((Suit)suit, Nine))) {
            amount = 80;
        }

        if (amount >= 80) {
            for (int suitBis = 0; suitBis < 4; suitBis++) {
                if (suitBis != suit && hasCard(Card((Suit)suit, Ace))) {
                    amount += 10;
                }
            }
        }

        if (cardsPerSuit[(Suit)suit].size() > 3) {
            amount += (cardsPerSuit[(Suit)suit].size() - 4) * 10;
        }

        if (amount > value) {
            value = amount;
            asset = (Suit)suit;
        }
    }

    amount = (amount > 180 ? 180 : amount);
	// LJ : L'enchère est donc calculée seul dans son coin, sans tenir compte des enchères du partenaire ou des adversaires
    Application::getInstance().getGame()->getBidMaker()->setBid(asset, value);
}
