//
//  Rules.cpp
//  Cheukoin
//
//  Created by Adrien Bruchet on 08/10/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Rules.h"

using namespace std;

Rules::Rules(Suit asset)
    : _asset(asset)
{
}

Rules::~Rules()
{
}

const map<Value, int> Rules::CardValues = {
    { Seven, 0 },
    { Eight, 0 },
    { Nine, 0 },
    { Ten, 10 },
    { Jack, 2 },
    { Queen, 3 },
    { King, 4 },
    { Ace, 11 }
};

const map<Value, int> Rules::CardValuesAsset = {
    { Seven, 0 },
    { Eight, 0 },
    { Nine, 14 },
    { Ten, 10 },
    { Jack, 20 },
    { Queen, 3 },
    { King, 4 },
    { Ace, 11 }
};

void Rules::setAsset(Suit asset)
{
    _asset = asset;
    Application::getInstance().getGame()->displayAsset(asset);
}

bool Rules::isTeamValid(Team team)
{
    return (team.getPlayers().size() == 2) && (team.getPlayers().at(0) != team.getPlayers().at(1));
}

bool Rules::isTrickValid(Trick trick)
{
    bool valid = true;

    if (trick.getCards().size() != 4) {
        valid = false;
    }
    else {
        // au delà de la taille du pli, tout le reste est géré par playableCards, non?
    }
    return valid;
}

vector<Card> Rules::cardsForSuit(vector<Card> cards, Suit suit)
{
    vector<Card> cardsForSuit;
    for (Card card : cards) {
        if (card.getSuit() == suit) {
            cardsForSuit.push_back(card);
        }
    }
    return cardsForSuit;
}
