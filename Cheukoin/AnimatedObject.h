//
//  AnimatedSprite.h
//  Cheukoin
//
//  Created by Corentin on 11/8/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__AnimatedSprite__
#define __Cheukoin__AnimatedSprite__

#include <stdio.h>
#include <memory.h>
#include <SFML/Graphics.hpp>
#include "Application.h"

class AnimatedObject {
public:
    AnimatedObject();

    virtual ~AnimatedObject();

    void draw() const;

    /**
     * Animate the card position
     */
    void moveTo(sf::Vector2f const& position, sf::Time transitionTime);

    void update(sf::Time elapsed);

    void setPosition(sf::Vector2f const& position);

    sf::Vector2f getGlobalPosition() const;

    sf::Vector2f getGlobalSize() const;

protected:
    sf::Vector2f _size;
    std::shared_ptr<sf::Sprite> _sprite;
    std::shared_ptr<sf::Texture> _texture;
};

#endif /* defined(__Cheukoin__AnimatedSprite__) */
