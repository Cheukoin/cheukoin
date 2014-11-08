//
//  AnimatedSprite.cpp
//  Cheukoin
//
//  Created by Corentin on 11/8/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "AnimatedObject.h"
#include <math.h>

using namespace std;

AnimatedObject::AnimatedObject()
    : _sprite(make_shared<sf::Sprite>())
    , _texture(make_shared<sf::Texture>())
    , _size(0, 0)
    , _targetPosition(0, 0)
    , _transitionTime(sf::seconds(0))
{
}

AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::draw() const
{
    Application::getInstance().getWindow()->draw(*_sprite.get());
}

void AnimatedObject::moveTo(sf::Vector2f const& position, sf::Time transitionTime)
{
    _targetPosition = position;
    _transitionTime = transitionTime;
    _elapsedTime = sf::microseconds(0);
}

void AnimatedObject::update(sf::Time elapsed)
{
    _elapsedTime += elapsed;
    sf::Vector2f position = _sprite->getPosition();

    if (_elapsedTime > _transitionTime) {
        _sprite->setPosition(_targetPosition);
    }
    else {
        float t = (float)_elapsedTime.asMilliseconds() / (float)_transitionTime.asMilliseconds();
        _sprite->setPosition((1.0f - t) * position + t * _targetPosition);
    }
}

void AnimatedObject::setPosition(sf::Vector2f const& position)
{
    _sprite->setPosition(position);
    _targetPosition = position;
    _transitionTime = sf::seconds(0);
    _elapsedTime = sf::seconds(0);
}

sf::Vector2f AnimatedObject::getGlobalPosition() const
{
    return sf::Vector2f(_sprite->getGlobalBounds().left,
                        _sprite->getGlobalBounds().top);
}

sf::Vector2f AnimatedObject::getGlobalSize() const
{
    return sf::Vector2f(_sprite->getGlobalBounds().width,
                        _sprite->getGlobalBounds().height);
}
