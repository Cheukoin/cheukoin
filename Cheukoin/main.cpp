#include <iostream>
#include <memory>

#include "Card.h"
#include "Trick.h"
#include "Game.h"
#include "NetworkManager.h"
#include "ResourcePath.h"
#include "Hand.h"
#include "Player.h"

using namespace std;

int main()
{
    Game& game = Game::getInstance();
    shared_ptr<sf::RenderWindow> window = game.getWindow();
    window->setFramerateLimit(60);

    sf::Vector2i v(1, 1);
    sf::Event event;

    // init background
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile(resourcePath("table.jpeg"))) {
        puts("Texture table not loaded");
    }
    bgTexture.setRepeated(true);
    sf::Sprite bgSprite;
    bgSprite.setTextureRect(sf::IntRect(0, 0, window->getSize().x, window->getSize().y));
    bgSprite.setTexture(bgTexture);

    vector<Card> cards = Card::getAllCardsShuffled();

    // main game loop
    while (window->isOpen()) {

        event.type = sf::Event::MouseButtonPressed;
        event.mouseButton.button = sf::Mouse::Left;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear();
        window->draw(bgSprite);

        for (int i = 0; i < cards.size(); i++) {
            cards[i].flip();
            cards[i].draw();

            cards[i].moveTo(20 * i, 50);
        }

        window->display();
    }

    return 0;
}
