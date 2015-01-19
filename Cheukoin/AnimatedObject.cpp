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

AnimatedObject::AnimatedObject(string spriteName, sf::Vector2f size)
    : _visible(true)
    , _sprite(make_shared<sf::Sprite>())
    , _texture(make_shared<sf::Texture>())
    , _size(size)
    , _targetPosition(0, 0)
    , _transitionTime(sf::seconds(0))

{
    if (!_texture->loadFromFile(resourcePath(spriteName))) {
        cout << "texture file " << resourcePath(spriteName) << " not loaded";
    }
    _texture->setSmooth(true);
    _sprite->setTexture(*_texture);
    _sprite->setScale(_size.x / _texture->getSize().x,
                      _size.y / _texture->getSize().y);
}

AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::draw() const
{
    if (_visible) {
        Application::getInstance().getWindow()->draw(*_sprite.get());
    }
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
        float time = (float)_elapsedTime.asMilliseconds() / (float)_transitionTime.asMilliseconds();
        _sprite->setPosition((1.0f - time) * position + time * _targetPosition);
    }
}

void AnimatedObject::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

void AnimatedObject::setPosition(sf::Vector2f const& position)
{
    _sprite->setPosition(position);
    _targetPosition = position;
    _transitionTime = sf::seconds(0);
    _elapsedTime = sf::seconds(0);
}

void AnimatedObject::show()
{
    _visible = true;
}

void AnimatedObject::hide()
{
    _visible = false;
}

bool AnimatedObject::isVisible()
{
    return _visible;
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
sf::IntRect AnimatedObject::getGlobalBounds() const
{
	// LJ : Pourquoi ne pas directement retourner sf::IntRect(_sprite->getGlobalBounds()); ?
    return sf::IntRect(getGlobalPosition().x, getGlobalPosition().y, getGlobalSize().x, getGlobalSize().y);
}
