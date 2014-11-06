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

const map<Value, int> Rules::_cardValues = {
    { Seven, 0 },
    { Eight, 0 },
    { Nine, 0 },
    { Ten, 10 },
    { Jack, 2 },
    { Queen, 3 },
    { King, 4 },
    { Ace, 11 }
};

const map<Value, int> Rules::_cardValuesAsset = {
    { Seven, 0 },
    { Eight, 0 },
    { Nine, 14 },
    { Ten, 10 },
    { Jack, 20 },
    { Queen, 3 },
    { King, 4 },
    { Ace, 11 }
};

std::map<Value, int> Rules::getCardValuesAsset()
{
    return _cardValuesAsset;
};

std::map<Value, int> Rules::getCardValues()
{
    return _cardValues;
};
void Rules::setAsset(Suit asset)
{
    _asset = asset;
}

// true if card1 wins over card2

bool Rules::isCardGreater(Card card1, Card card2, Suit askedSuit)
{
    if (card1.getSuit() != _asset && card2.getSuit() == _asset) {
        return false;
    }
    else if (card1.getSuit() == _asset && card2.getSuit() != _asset) {
        return true;
    }
    else if (card1.getSuit() != askedSuit && card2.getSuit() == askedSuit) {
        return false;
    }
    else if (card1.getSuit() == askedSuit && card2.getSuit() != askedSuit) {
        return true;
    }
    else if (card1.getSuit() != card2.getSuit()) {
        return true;
    }
    else {
        // 2 cards are from same suit
        map<Value, int> order = (card1.getSuit() == _asset ? _cardValuesAsset : _cardValues);
        return order[card1.getValue()] > order[card2.getValue()];
    }
}

bool Rules::isTeamValid(Team team)
{
    return (team.getPlayers().size() == 2) && (team.getPlayers().at(0) != team.getPlayers().at(1));
}

bool Rules::isFriendMaster(Player player, vector<Card> firstCards)
{
    unsigned long numberPlayedCards = firstCards.size();
    std::vector<Card> enemyCards;
    if (numberPlayedCards > 1) {
        Card friendlyCard = firstCards[numberPlayedCards - 2];
        Suit askedSuit = firstCards.front().getSuit();
        for (auto c : firstCards) {
            if (c != friendlyCard) {
                enemyCards.push_back(c);
            }
        }
        switch (enemyCards.size()) {
        case 0:
            return true;

        case 1:
            return isCardGreater(friendlyCard, enemyCards[0], askedSuit);

        case 2:
            return isCardGreater(friendlyCard, enemyCards[0], askedSuit) && isCardGreater(friendlyCard, enemyCards[1], askedSuit);

        default:
            return false;
        }
    }
    return false;
}

std::vector<Card> Rules::getPlayableCards(Player player)
{
    return getPlayableCards(player, Application::getInstance().getGame()->getCurrentTrick().getCards());
}
std::vector<Card> Rules::getPlayableCards(Player player, vector<Card> firstCards)
{
    if (firstCards.size() == 0) {
        return player.getCards();
    }

    Suit demandedSuit = firstCards[0].getSuit();

    // first, look wether the player have the demanded suit in his hand

    if (demandedSuit != _asset && player.cardsForSuit(demandedSuit).size() != 0) {
        return player.cardsForSuit(demandedSuit);
    }

    // if not, he can still play whatever he wants if his friends is the current master of the trick

    else if (demandedSuit != _asset && isFriendMaster(player, firstCards)) {
        return player.getCards();
    }

    // if his friend isn't, and he has assets, he has to play them, and they must be bigger than assets already played

    else if (player.cardsForSuit(_asset).size() != 0) {
        std::vector<Card> playableCards;
        std::vector<Card> assets = cardsForSuit(firstCards, _asset);

        if (assets.size() == 0) {
            return player.cardsForSuit(_asset);
        }

        Card max = assets[0];
        for (auto card : assets) {
            if (isCardGreater(card, max, demandedSuit)) {
                max = card;
            }
        }
        for (auto card : player.cardsForSuit(_asset)) {
            if (isCardGreater(card, max, demandedSuit)) {
                playableCards.push_back(card);
            }
        }
        return (playableCards.size() > 0 ? playableCards : player.cardsForSuit(_asset));
    }

    // if the friend isn't master and he hasn't got neither asked suit nor bigger assets, he can play whatever he wants

    return player.getCards();
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
