#include "Player.h"

using namespace std;

Player::Player()
    : _name("Player 1")
{
}

Player::~Player()
{
}

void Player::playCard(Card const& card)
{
#warning TODO : verify move is valid with rules
    if (_cards.size() != 0) {
        for (int i = 0; i < _cards.size(); i++) {
            if (_cards[i] == card) {
                _cards[i].flip();
                _cards[i].move();
                _cards.erase(_cards.begin() + i);
            }
        }
    }
    _game->getCurrentTrick().addCard(card);
    _playedCard = card;
    if (_game->getMode() == Online) {
#warning TODO : notify server if multiplayer
    }
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
