#include "Player.h"

using namespace std;

Player::Player()
{
}

Player::~Player()
{
}

void Player::playCard(Card card) {}

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

void Player::setHand(Hand hand)
{
    _hand = hand;
}

Bid Player::getBid()
{
    return _bid;
}

void Player::setBid(Bid bid)
{
    _bid = bid;
}
