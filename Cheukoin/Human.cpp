//
//  Human.cpp
//  Cheukoin
//
//  Created by Corentin on 10/21/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Human.h"

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
void Human::update()
{
}
#warning isPlayblaCard missing
void Human::play()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*Application::getInstance().getWindow());
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int i = 0; (i < _cards.size()); i++) {
            sf::IntRect rectref;
            if (i == (_cards.size() - 1))
                rectref = sf::IntRect(_cards[i].sprite->getPosition().x, _cards[i].sprite->getPosition().y, _cards[i].getGlobalSize().x, _cards[i].getGlobalSize().y);
            else
                rectref = sf::IntRect(_cards[i].sprite->getPosition().x, _cards[i].sprite->getPosition().y, _cards[i + 1].sprite->getPosition().x - _cards[i].sprite->getPosition().x, _cards[i].getGlobalSize().y);

            if (rectref.contains(mousePosition.x, mousePosition.y)) {
                playCard(_cards[i]);
            }
        }
    }
}
