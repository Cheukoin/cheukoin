//
//  Rules.h
//  Cheukoin
//
//  Created by Adrien Bruchet on 08/10/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__Rules__
#define __Cheukoin__Rules__

#include <map>

#include "Card.h"
#include "Trick.h"
#include "Team.h"
#include "Player.h"
#include "Constants.h"
#include "Game.h"
#include "Lobby.h"

class Rules {
public:
    Rules(Suit asset);
    ~Rules();

    // Returns card1 > card2 for the specified asset
    bool isCardGreater(Card card1, Card card2, Suit askedSuit);
    bool isTrickValid(Trick trick);
    bool isTeamValid(Team team);

    //
    bool isFriendMaster(Player player, std::vector<Card> firstCards);
    std::vector<Card> getPlayableCards(Player player);
    std::vector<Card> getPlayableCards(Player player, std::vector<Card> firstCards);

    std::map<Value, int> getCardValuesAsset();
    std::map<Value, int> getCardValues();

    static std::vector<Card> cardsForSuit(std::vector<Card> cards, Suit suit);

private:
    static const std::map<Value, int> _cardValues;
    static const std::map<Value, int> _cardValuesAsset;
    Suit _asset;
};

// TODO : faire methode statique, instancier rules ds Game

#endif /* defined(__Cheukoin__Rules__) */
