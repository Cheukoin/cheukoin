#include "Player.h"

using namespace std;

Player::Player()
    : _name("Player 1")
{
}

void Player::playCard(Card const& card)
{
#warning TODO : verify move is valid with rules
    _game.getCurrentTrick()->addCard(card);
    _hand.removeCard(card);
    if (_game.getMode() == online) {
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
