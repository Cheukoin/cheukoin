//
//  Asset.cpp
//  Cheukoin
//
//  Created by Corentin on 11/9/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Asset.h"

Asset::Asset()
    : AnimatedObject("suits.png", sf::Vector2f(50, 50))
    , _suit(Suit::Clubs)
    , _isSet(false)
{
}

void Asset::setSuit(Suit suit)
{
    _suit = suit;
    _isSet = true;

    switch (suit) {
    case Suit::Spades:
        _sprite->setTextureRect(sf::Rect<int>(0, 0, 150, 150));
        break;
    case Suit::Hearts:
        _sprite->setTextureRect(sf::Rect<int>(150, 0, 150, 150));
        break;
    case Suit::Diamonds:
        _sprite->setTextureRect(sf::Rect<int>(0, 150, 150, 150));
        break;
    case Suit::Clubs:
        _sprite->setTextureRect(sf::Rect<int>(150, 150, 150, 150));
        break;
    default:
        break;
    }
}

bool Asset::isSet()
{
    return _isSet;
}
