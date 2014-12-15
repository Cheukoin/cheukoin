//
//  Human.cpp
//  Cheukoin
//
//  Created by Corentin on 10/21/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Human.h"
#include "Rules.h"
#include "NetworkManager.h"

using namespace std;

Human::Human(string name, Position position)
    : Player(name, position)
{
}

Human::~Human()
{
}

void Human::initialize()
{
    Player::initialize();

    for (unsigned i = 0; i < _cards.size(); i++) {
        _cards[i].show();
    }
}

void Human::play()
{
    Card card = chooseCard();

    vector<Card> playableCards = getPlayableCards();
    if (find(playableCards.begin(), playableCards.end(), card) != playableCards.end()) {
        playCard(card);
    }
}

Card Human::chooseCard()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*Application::getInstance().getWindow());
    for (unsigned i = 0; i < _cards.size(); i++) {
        sf::IntRect rectref;
        sf::IntRect rectref2;
        if (i == (_cards.size() - 1)) {
            rectref = sf::IntRect(_cards[i].getGlobalPosition().x, _cards[i].getGlobalPosition().y, _cards[i].getGlobalSize().x, _cards[i].getGlobalSize().y);
            rectref2 = rectref;
        }
        else {
            rectref = sf::IntRect(_cards[i].getGlobalPosition().x, _cards[i].getGlobalPosition().y - _cards[i].getGlobalSize().y * 0.1, _cards[i + 1].getGlobalPosition().x - _cards[i].getGlobalPosition().x, _cards[i].getGlobalSize().y);
            rectref2 = rectref;
            // rectref2 ne marche pas ..
            if (_cards[i + 1].getSuit() != _cards[i].getSuit()) {
                rectref2 = sf::IntRect(_cards[i].getGlobalPosition().x, _cards[i].getGlobalPosition().y - _cards[i].getGlobalSize().y * 0.1, _cards[i].getGlobalSize().x, _cards[i].getGlobalSize().y * 0.1);
            }
        }
        if (rectref.contains(mousePosition)) {
            return _cards[i];
        }
    }

    // shouldn't happen, maybe throw an exception?
    return _cards.front();
}

void Human::playCard(const Card& card)
{
    if (Application::getInstance().getGame()->getMode() == Online) {
        // TODO : notify server if multiplayer
    }

    NetworkManager::sendTurn(*Application::getInstance().getGame()->getLobby(), card);

    Player::playCard(card);
}

void Human::chooseBid()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*Application::getInstance().getWindow());
    Application::getInstance().getGame()->getBidMaker()->handleClickAtPosition(mousePosition);
}

void Human::showLegalCards()
{
    // replace all cards at origin position then move to top the legal ones
    vector<Card> playableCards = getPlayableCards();
    sf::Vector2f position;
    for (Card& card : _cards) {
        if (find(playableCards.begin(), playableCards.end(), card) != playableCards.end()) {
            position = sf::Vector2f(card.getGlobalPosition().x,
                                    positionBottomy - card.getGlobalSize().y * 0.1);
        }
        else {
            position = sf::Vector2f(card.getGlobalPosition().x,
                                    positionBottomy);
        }

        card.moveTo(position, sf::milliseconds(100));
    }
}
