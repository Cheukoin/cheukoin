//
//  Lobby.cpp
//  Cheukoin
//
//  Created by Corentin on 10/16/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Lobby.h"

using namespace std;

Lobby::Lobby(string const& name, vector<Team> const& teams)
    : _name(name)
    , _teams(teams)
{
}

void Lobby::deal()
{
    vector<Card> cards = Card::getAllCardsShuffled();

    int i = 0;
    vector<vector<Card> > hands{ {}, {}, {}, {} };
    for (Card card : cards) {
        hands[i % 4].push_back(card);
        i++;
    }

    for (int i = 0; i < getPlayers().size(); i++) {
        getPlayers()[i].setCards(hands[i]);
    }
}

string Lobby::getName() const
{
    return _name;
}

void Lobby::setName(string const& name)
{
    _name = name;
}

vector<Player> Lobby::getPlayers()
{
    vector<Player> players = {
        _teams[0].getComposition()[0],
        _teams[0].getComposition()[1],
        _teams[1].getComposition()[0],
        _teams[1].getComposition()[1]
    };

    return players;
}

Lobby::~Lobby()
{
}