//
//  Rules.cpp
//  Cheukoin
//
//  Created by Adrien Bruchet on 08/10/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Rules.h"
#include <map>

using namespace std;

Rules::Rules():_cardValuesAsset({{Seven, 0}, {Eight, 0}, {Nine, 14}, {Ten, 10}, {Jack, 20}, {Queen, 3}, {King, 4}, {Ace, 11}}), _cardValues({{Seven,0}, {Eight,0}, {Nine,0}, {Ten,10}, {Jack,2}, {Queen,3}, {King,4}, {Ace,11}})
{
    
}

Rules::~Rules()
{
    
}

bool Rules::isGreater(Card card1, Card card2, Suit asset)
{
    if (card1.getSuit() != asset && card2.getSuit() == asset)
    {
        return false;
    }
    else if (card1.getSuit() == asset && card2.getSuit() != asset)
    {
        return true;
    }
    else
    {
        map <Value, int> order;
        
        if (card1.getSuit() != card2.getSuit())
        {
            return false;
        }
        else if (card1.getSuit() == asset)
        {
            order = _cardValuesAsset;
        }
        else
        {
            order = _cardValues;
        }
        
        if (order[card1.getValue()] > order[card2.getValue()])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

Card Rules::winningCard(Trick trick, Suit asset)
{
    Card max = trick.getComposition()[0];
    for (int i = 0; i < trick.getComposition().size(); i++)
    {
        if (isGreater(trick.getComposition()[i], max, asset))
        {
            max = trick.getComposition()[i];
        }
    }
    return max;
}

