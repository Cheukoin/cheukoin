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
    _game.getCurrentTrick()->addCard(card);
    _hand.removeCard(card);
    _playedCard = card;
    if (_game.getMode() == Online) {
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

Hand Player::getHand() const
{
    return _hand;
}

void Player::setHand(Hand& hand)
{
    _hand = hand;
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

bool operator==(Player const& a, Player const& b)
{
    return a.getName() == b.getName();
}

bool operator!=(Player const& a, Player const& b)
{
    return !(a == b);
}

/*
void Player::playByClick()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_game.getWindow().get());
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (auto card : _hand.getCards()) {
            if (card.sprite->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                card.flip();
                _game.getCurrentTrick()->addCard(card);
            }
        }
    }
}*/
