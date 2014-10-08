//
//  Rules.h
//  Cheukoin
//
//  Created by Adrien Bruchet on 08/10/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__Rules__
#define __Cheukoin__Rules__

#include <iostream>
#include <map>
#include "Card.h"
#include "Trick.h"

class Rules
{
public:
    Rules();
    ~Rules();
    bool isGreater(Card card1, Card card2, Suit asset);
    Card tagueule();
    
 
private:
    std::map<Value, int> _cardValues;
    std::map<Value, int> _cardValuesAsset;
    
};

#endif /* defined(__Cheukoin__Rules__) */
