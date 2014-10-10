//
//  Rules.cpp
//  Cheukoin
//
//  Created by Adrien Bruchet on 08/10/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Rules.h"


using namespace std;

Rules::Rules()
    : _cardValuesAsset({ { Seven, 0 }, { Eight, 0 }, { Nine, 14 }, { Ten, 10 }, { Jack, 20 }, { Queen, 3 }, { King, 4 }, { Ace, 11 } })
    , _cardValues({ { Seven, 0 }, { Eight, 0 }, { Nine, 0 }, { Ten, 10 }, { Jack, 2 }, { Queen, 3 }, { King, 4 }, { Ace, 11 } })
{
}

Rules::~Rules()
{
}

bool Rules::isCardGreater(Card card1, Card card2, Suit asset)
{
    if (card1.getSuit() != asset && card2.getSuit() == asset) {
        return false;
    }
    else if (card1.getSuit() == asset && card2.getSuit() != asset) {
        return true;
    }
    else {
        map<Value, int> order;

        if (card1.getSuit() != card2.getSuit()) {
            return false;
        }
        else if (card1.getSuit() == asset) {
            order = _cardValuesAsset;
        }
        else {
            order = _cardValues;
        }

        if (order[card1.getValue()] > order[card2.getValue()]) {
            return true;
        }
        else {
            return false;
        }
    }
}

Card Rules::winningCard(Trick trick, Suit asset)
{
    Card max = trick.getComposition()[0];
    for (int i = 0; i < trick.getComposition().size(); i++) {
        if (isCardGreater(trick.getComposition()[i], max, asset)) {
            max = trick.getComposition()[i];
        }
    }
    return max;
}

bool Rules::isTeamValid(Team team)
{
    return (team.getComposition().size() == 2) && (team.getComposition()[0].getName() != team.getComposition()[1].getName());
}

std::vector<Card> Rules::playableCard(Player player, Card firstCard, Suit asset)
{
    Suit demandedSuit = firstCard.getSuit();
    std::vector<Card> playableCards;
    bool piss = true;
    for (auto c : player.getHand().getCards()) {
        if (c.getSuit() == demandedSuit) {
            piss = false;
            playableCards.push_back(c);
        }
        else if (c.getSuit() == asset) {
            piss = false;
            playableCards.push_back(c);
        }
    }
    if (piss) {
        return player.getHand().getCards();
    }
    else {
        return playableCards;
    }
}

bool Rules::isTrickvalid(Trick trick)
{
    Suit demandedSuit = trick.getComposition()[0].getSuit();
}
