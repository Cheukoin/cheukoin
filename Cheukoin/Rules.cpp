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

// true if first arg bigger than second arg

bool Rules::isCardGreater(Card card1, Card card2)
{
    if (card1.getSuit() != _asset && card2.getSuit() == _asset) {
        return false;
    }
    else if (card1.getSuit() == _asset && card2.getSuit() != _asset) {
        return true;
    }
    else {
        map<Value, int> order;

        if (card1.getSuit() != card2.getSuit()) {
            return false;
        }
        else if (card1.getSuit() == _asset) {
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

Card Rules::winningCard(Trick trick)
{
    // TODO: check if we can use a lambda with std::max
    Card max = trick.getCards()[0];
    for (int i = 0; i < trick.getCards().size(); i++) {
        if (isCardGreater(trick.getCards()[i], max)) {
            max = trick.getCards()[i];
        }
    }
    return max;
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
        for (auto c : firstCards) {
            if (c != friendlyCard) {
                enemyCards.push_back(c);
            }
        }
        switch (enemyCards.size()) {
        case 0:
            return true;

        case 1:
            return isCardGreater(friendlyCard, enemyCards[0]);

        case 2:
            return isCardGreater(friendlyCard, enemyCards[0]) && isCardGreater(friendlyCard, enemyCards[1]);

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
            if (isCardGreater(card, max)) {
                max = card;
            }
        }
        for (auto card : player.cardsForSuit(_asset)) {
            if (isCardGreater(card, max)) {
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

//void Rules::giveTrickToWinner(Trick& trick, Team& team1, Team& team2)
//{
//    Card best = winningCard(trick);
//    vector<Card> cards = trick.getCards();
//    std::vector<shared_ptr<Player> > players = Application::getInstance().getGame()->getLobby().getTeams.getPlayers();
//    for (shared_ptr<Player> player : players) {
//        if (player->getPlayedCard() == best) {
//            if (team1.getPlayers()->at(0) == player || team1.getPlayers()->at(1) == player) {
//                team1.addTrick(trick);
//            }
//            else {
//                team2.addTrick(trick);
//            }
//        }
//    }
//}

vector<Card> cardsForSuit(vector<Card> cards, Suit suit)
{
    vector<Card> cardsForSuit;
    for (Card card : cards) {
        if (card.getSuit() == suit) {
            cardsForSuit.push_back(card);
        }
    }
    return cardsForSuit;
}
