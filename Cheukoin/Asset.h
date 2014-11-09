//
//  Asset.h
//  Cheukoin
//
//  Created by Corentin on 11/9/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__Asset__
#define __Cheukoin__Asset__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "AnimatedObject.h"

class Asset : public AnimatedObject {
public:
    Asset(Suit asset);
};

#endif /* defined(__Cheukoin__Asset__) */
