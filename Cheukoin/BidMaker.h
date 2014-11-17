//
//  BidMaker.h
//  Cheukoin
//
//  Created by Gabriel Samain on 17/11/2014.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__BidMaker__
#define __Cheukoin__BidMaker__

#include <SFML/Graphics.hpp>

#include "Application.h"
#include "AnimatedObject.h"
#include "Bid.h"
#include "Player.h"

class BidMaker : public AnimatedObject {
public:
    BidMaker(std::string spriteName, sf::Vector2f size);

    void handleClickAtPosition(sf::Vector2i position);
    void setBid(Suit asset, int value);

    Bid getCurrentBid();

private:
    Bid _currentBid;

    bool _shouldStartGame();
};

#endif /* defined(__Cheukoin__BidMaker__) */
