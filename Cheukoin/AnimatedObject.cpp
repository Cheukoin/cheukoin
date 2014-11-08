//
//  AnimatedSprite.cpp
//  Cheukoin
//
//  Created by Corentin on 11/8/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "AnimatedObject.h"

using namespace std;

AnimatedObject::AnimatedObject()
    : _sprite(make_shared<sf::Sprite>())
    , _texture(make_shared<sf::Texture>())
{
}

AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::draw() const
{
    Application::getInstance().getWindow()->draw(*_sprite);
}

void AnimatedObject::moveTo(sf::Vector2f const& position, sf::Time transitionTime)
{
    _sprite->setPosition(position);
}

void AnimatedObject::update(sf::Time elapsed)
{
}

void AnimatedObject::setPosition(sf::Vector2f const& position)
{
    _sprite->setPosition(position);
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