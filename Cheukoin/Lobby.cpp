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

    for (int i = 0; i < cards.size(); i++) {
        getPlayers().at(i % 4).get()->addCard(cards[i]);
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

vector<Team> Lobby::getTeams()
{
    return _teams;
}

vector<shared_ptr<Player> > Lobby::getPlayers()
{
    return {
        _teams[0].getPlayers().at(0),
        _teams[1].getPlayers().at(0),
        _teams[0].getPlayers().at(1),
        _teams[1].getPlayers().at(1)
    };
}

Team& Lobby::getTeamForPlayer(Player player, bool getEnemyTeam)
{
    if (!getEnemyTeam && (*_teams[0].getPlayers().at(0) == player || *_teams[0].getPlayers().at(1) == player)) {
        return _teams[0];
    }
    return _teams[1];
}

Lobby::~Lobby()
{
}