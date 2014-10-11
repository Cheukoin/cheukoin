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

string Player::getName()
{
    return _name;
}

void Player::setName(string name)
{
    _name = name;
}

Hand Player::getHand()
{
    return _hand;
}

void Player::setHand(Hand& hand)
{
    _hand = hand;
}

Bid Player::getBid()
{
    return _bid;
}

void Player::setBid(Bid& bid)
{
    _bid = bid;
}