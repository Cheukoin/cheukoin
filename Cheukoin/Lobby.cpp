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

    for (int i = 0; i < cards.size(); i += 4) {
        _teams[0].getPlayers()->at(0).addCard(cards[i]);
        _teams[0].getPlayers()->at(1).addCard(cards[i + 1]);
        _teams[1].getPlayers()->at(0).addCard(cards[i + 2]);
        _teams[1].getPlayers()->at(1).addCard(cards[i + 3]);
    }
    cout << _teams[0].getPlayers()->at(0).getCards().size() << endl;
}

string Lobby::getName() const
{
    return _name;
}

void Lobby::setName(string const& name)
{
    _name = name;
}

std::vector<Team> Lobby::getTeams()
{
    return _teams;
}

Lobby::~Lobby()
{
}