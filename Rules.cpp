//
//  Rules.cpp
//  Cheukoin
//
//  Created by Adrien Bruchet on 08/10/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Rules.h"

Rules::Rules():_cardValuesAsset({{Seven, 0}, {Eight, 0}, {Nine, 14}, {Ten, 10}, {Jack, 20}, {Queen, 3}, {King, 4}, {Ace, 11}}), _cardValues({{Seven,0},{Eight,0},{Nine,0},{Ten,10},{Jack,2},{Queen,3},{King,4},{Ace,11}})
{
    
}

Rules::~Rules()
{
    
}

bool Rules::isGreater(Card card1, Card card2, Suit asset)
{
    
}

Card Rules::winningCard(Trick trick, Suit asset)
{
    
}

