//
//  Rules.cpp
//  Cheukoin
//
//  Created by Adrien Bruchet on 07/10/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Rules.h"

Rules::Rules()
{
    _cardValues = {
        {Seven,0},
        {Eight,0},
        {Nine,0},
        {Ten,10},
        {Jack,2},
        {Queen,3},
        {King,4},
        {Ace,11}
    };
    
    _cardValuesAsset = {
        {Seven, 0},
        {Eight, 0},
        {Nine, 14},
        {Ten, 10},
        {Jack, 20},
        {Queen, 3},
        {King, 4},
        {Ace, 11},
    };
}
