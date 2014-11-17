//
//  Asset.h
//  Cheukoin
//
//  Created by Corentin on 11/9/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__Asset__
#define __Cheukoin__Asset__

#include "AnimatedObject.h"
#include "Card.h"

class Asset : public AnimatedObject {
public:
    Asset();

    void setSuit(Suit suit);
    bool isSet();

private:
    Suit _suit;
    bool _isSet;
};

#endif /* defined(__Cheukoin__Asset__) */
