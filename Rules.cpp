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

bool Rules::isFriendMaster(Player player, vector<Card> firstCards, Suit asset)
{
    bool master = false;
    int numberPlayedCards = firstCards.size();
    std::vector<Card> enemyCards;
    if (numberPlayedCards > 1) {
        Card friendlyCard = firstCards[numberPlayedCards - 2];
        for (auto c : firstCards) {
            if (c != friendlyCard) {
                enemyCards.push_back(c);
            }
        }
        master = isCardGreater(friendlyCard, enemyCards[0], asset) && isCardGreater(friendlyCard, enemyCards[1], asset);
    }
    return master;
}

std::vector<Card> Rules::playableCard(Player player, vector<Card> firstCards, Suit asset)
{

    Suit demandedSuit = firstCards[0].getSuit();
    std::vector<Card> playableCards;
    bool piss = true;
    if (player.getHand().cardsForSuit(demandedSuit).size() != 0) {
        piss = false;
        playableCards = player.getHand().cardsForSuit(demandedSuit);
    }
    else if (isFriendMaster(player, firstCards, asset)) {
        playableCards = player.getHand().getCards();
    }
    else if (player.getHand().cardsForSuit(asset).size() != 0) {
        piss = false;
        std::vector<Card> assets = cardsForSuit(firstCards, asset);
        Card max = assets[0];
        for (auto c : assets) {
            if (isCardGreater(c, max, asset)) {
                max = c;
            }
        }
        for (auto c : player.getHand().cardsForSuit(asset)) {
            if (isCardGreater(c, max, asset)) {
                playableCards.push_back(c);
            }
        }
    }
    else {
        playableCards = playableCards = player.getHand().getCards();
    }
    return playableCards;
}

bool Rules::isTrickvalid(Trick trick)
{
    bool valid = true;
    Suit demandedSuit = trick.getComposition()[0].getSuit();
    if (trick.getComposition().size() != 4) {
        valid = false;
    }
    return valid;
}

void Rules::giveWinnerTrick(Trick& trick, Suit const& asset, Team& team1, Team& team2)
{
    Card best = winningCard(trick, asset);
    int winningIndex = 5;
    int i = 0;
    while (winningIndex == 5) {
        if (trick.getComposition()[i] == best) {
            winningIndex = i;
        }
        else {
            i++;
        }
    }
    if (winningIndex == 1 or i == 3) {
    }
}
