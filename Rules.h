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
#include "Hand.h"
#include "Constants.h"

class Rules {
public:
    Rules();
    ~Rules();

    bool isCardGreater(Card card1, Card card2, Suit asset);
    Card winningCard(Trick trick, Suit asset);
    bool isTrickvalid(Trick trick);
    bool isTeamValid(Team team);
    bool isFriendMaster(Player player, std::vector<Card> firstCards, Suit asset);
    std::vector<Card> playableCard(Player player, std::vector<Card> firstCards, Suit asset);
    void giveWinnerTrick(Trick& trick, Suit const& asset, Team& team1, Team& team2);

private:
    static const std::map<Value, int> _cardValues;
    static const std::map<Value, int> _cardValuesAsset;
};

#warning TODO : faire methode statique, instancier rules ds Game
std::vector<Card> cardsForSuit(std::vector<Card> cards, Suit suit);

#endif /* defined(__Cheukoin__Rules__) */
