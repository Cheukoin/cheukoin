#include "Player.h"

using namespace std;

Player::Player(string name, Position position)
    : _name(name)
    , _position(position)
{
}

Player::Player()
    : _name("Default")
{
}

Player::~Player()
{
}

void Player::initialize()
{
    sf::Vector2u pos;
    sf::Vector2u winSize = Application::getInstance().getWindow()->getSize();
    sf::Vector2u cardSize = _cards.front().getGlobalSize();

    switch (_position) {
    case Top:
        pos = sf::Vector2u(winSize.x / 2, 0);
        break;
    case Bottom:
        pos = sf::Vector2u(winSize.x / 2, winSize.y - cardSize.y);
        break;
    case Left:
        pos = sf::Vector2u(cardSize.x, winSize.y / 2 - cardSize.y / 2);
        break;
    case Right:
        pos = sf::Vector2u(winSize.x - cardSize.x, winSize.y / 2 - cardSize.y / 2);
        break;
    default:
        pos = sf::Vector2u(0, 0);
        break;
    }

    for (int i = 0; i < _cards.size(); i++) {
        _cards[i].moveTo(sf::Vector2u(pos.x + 20 * (i - 4) - cardSize.x / 2, pos.y));
    }
}

void Player::play()
{
    // to be reimplemented
}

void Player::playCard(Card const& card)
{
    cout << "-- " << _name << " playing " << card << endl;
#warning TODO : verify move is valid with rules
    if (_cards.size() != 0) {
        for (int i = 0; i < _cards.size(); i++) {
            if (_cards[i] == card) {
                _cards[i].flip();
                _moveCardToTrick(_cards[i]);
                _cards.erase(_cards.begin() + i);
            }
        }
    }

    shared_ptr<Game> game = Application::getInstance().getGame();
    game->getCurrentTrick().addCard(card);
    _playedCard = card;
    if (game->getMode() == Online) {
#warning TODO : notify server if multiplayer
    }
}

void Player::_moveCardToTrick(Card& card)
{
    sf::Vector2u winSize = Application::getInstance().getWindow()->getSize();
    sf::Vector2u cardSize = _cards.front().getGlobalSize();
    sf::Vector2u pos(winSize.x / 2, winSize.y / 2);

    switch (_position) {
    case Top:
        pos += sf::Vector2u(0, -cardSize.y / 2);
        break;
    case Bottom:
        pos += sf::Vector2u(0, cardSize.y / 2);
        break;
    case Left:
        pos += sf::Vector2u(-cardSize.x / 2, 0);
        break;
    case Right:
        pos += sf::Vector2u(cardSize.x / 2, 0);
        break;
    default:
        pos = sf::Vector2u(0, 0);
        break;
    }

    card.moveTo(pos);
}

Bid Player::makeBid(int amount, Suit const& asset)
{
    _bid.setAmount(amount);
    _bid.setSuit(asset);
    return _bid;
}

string Player::getName() const
{
    return _name;
}

void Player::setName(string name)
{
    _name = name;
}

Card Player::getPlayedCard()
{
    return _playedCard;
}

Bid Player::getBid() const
{
    return _bid;
}

void Player::setBid(Bid& bid)
{
    _bid = bid;
}

void Player::makeDealer()
{
    _dealer = true;
}

void Player::changeDealer()
{
    _dealer = false;
}

bool Player::isDealer()
{
    return _dealer;
}

// Card management

void Player::addCard(Card card)
{
    _cards.push_back(card);
}

vector<Card> Player::getCards() const
{
    return _cards;
}

void Player::drawCards() const
{
    for (Card card : _cards) {
        card.draw();
    }
}

Position Player::getPosition() const
{
    return _position;
}

void Player::setPosition(Position position)
{
    _position = position;
}

vector<Card> Player::cardsForSuit(Suit suit)
{
#warning TODO : appeler l'equivalent ds rules
    std::vector<Card> cardsForSuit;
    for (auto c : _cards) {
        if (c.getSuit() == suit) {
            cardsForSuit.push_back(c);
        }
    }
    return cardsForSuit;
}

bool operator==(Player const& a, Player const& b)
{
    return a.getName() == b.getName();
}

bool operator!=(Player const& a, Player const& b)
{
    return !(a == b);
}
