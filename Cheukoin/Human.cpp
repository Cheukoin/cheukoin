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

    for (int i = 0; i < _cards.size(); i++) {
        _cards[i].flip();
    }
}

void Human::play()
{
    Card card = chooseCard();

    // TODO check the cards that are already in the trick
    vector<Card> playableCards = getPlayableCards();
    if (find(playableCards.begin(), playableCards.end(), card) != playableCards.end()) {
        playCard(card);
    }
}

Card Human::chooseCard()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*Application::getInstance().getWindow());

    for (int i = 0; (i < _cards.size()); i++) {
        sf::IntRect rectref;
        if (i == (_cards.size() - 1)) {
            rectref = sf::IntRect(_cards[i].getGlobalPosition().x, _cards[i].getGlobalPosition().y, _cards[i].getGlobalSize().x, _cards[i].getGlobalSize().y);
        }
        else {
            rectref = sf::IntRect(_cards[i].getGlobalPosition().x, _cards[i].getGlobalPosition().y, _cards[i + 1].getGlobalPosition().x - _cards[i].getGlobalPosition().x, _cards[i].getGlobalSize().y);
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

shared_ptr<Bid> Human::chooseBid()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*Application::getInstance().getWindow());
    for (int i = 0; i < 5; i++) {
        for (int suit = 0; suit < 4; suit++) {
            sf::IntRect rectref;
            Card card = Card();
            card.bidCard();
            rectref = sf::IntRect(card.getGlobalPosition().x + card.getGlobalSize().x * i / 5, card.getGlobalPosition().y + card.getGlobalSize().y * suit / 4, card.getGlobalSize().x / 5, card.getGlobalSize().y / 4);

            if (rectref.contains(mousePosition)) {
                return make_shared<Bid>(Suit(suit), 80 + i * 20);
            }
        }
    }
    return make_shared<Bid>();
}

void Human::showLegalCards()
{
    // replace all cards at origin position then move to top the legal ones
    vector<Card> playableCards = getPlayableCards();
    sf::Vector2f position;

    for (Card& card : _cards) {
        if (find(playableCards.begin(), playableCards.end(), card) != playableCards.end()) {
            position = sf::Vector2f(card.getGlobalPosition().x,
                                    Application::getInstance().getWindow()->getSize().y - card.getGlobalSize().y - 30);
        }
        else {
            position = sf::Vector2f(card.getGlobalPosition().x,
                                    Application::getInstance().getWindow()->getSize().y - card.getGlobalSize().y);
        }

        card.moveTo(position, sf::milliseconds(100));
    }
}
