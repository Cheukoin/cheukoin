//
//  AnimatedSprite.h
//  Cheukoin
//
//  Created by Corentin on 11/8/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__AnimatedSprite__
#define __Cheukoin__AnimatedSprite__

#include <iostream>
#include <memory.h>
#include <SFML/Graphics.hpp>

#include "ResourcePath.h"
#include "Application.h"

class AnimatedObject {
public:
    AnimatedObject(std::string spriteName, sf::Vector2f size);


    virtual ~AnimatedObject();

    void draw() const;

    /**
     * Animate the card position
     */
    void moveTo(sf::Vector2f const& position, sf::Time transitionTime);

    void update(sf::Time elapsed);

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f const& position);

    void show();
    void hide();
    bool isVisible();

    sf::Vector2f getGlobalPosition() const;
    sf::Vector2f getGlobalSize() const;
    sf::IntRect getGlobalBounds() const;

protected:
	// LJ : Certains noms commençant par _ sont réservés à l'usage exclusif du compilateur (les règles sont un peu plus compliquées que ça).
	// LJ : il est donc déconseillé de prendre une convention de nommage qui fait commencer des noms par _
    bool _visible;
    sf::Vector2f _size;
    sf::Vector2f _targetPosition;
    sf::Time _transitionTime;
    sf::Time _elapsedTime;
    std::shared_ptr<sf::Sprite> _sprite;
    std::shared_ptr<sf::Texture> _texture;
};

#endif /* defined(__Cheukoin__AnimatedSprite__) */
