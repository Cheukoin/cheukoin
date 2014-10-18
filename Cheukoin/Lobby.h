//
//  Lobby.h
//  Cheukoin
//
//  Created by Corentin on 10/16/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__Lobby__
#define __Cheukoin__Lobby__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Team.h"

class Lobby {

public:
    Lobby(std::string const& name, std::vector<Team> const& teams = std::vector<Team>());
    Lobby(){};
    ~Lobby();

    // give cards to all players
    void deal();

    std::string getName() const;
    void setName(std::string const& name);

    std::vector<Player> getPlayers() const;

private:
    std::string _name;
    std::vector<Team> _teams;
};

#endif /* defined(__Cheukoin__Lobby__) */
