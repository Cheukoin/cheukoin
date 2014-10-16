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

    game.startGame();

    sf::Vector2i v(1, 1);

    // init background
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile(resourcePath("table.jpeg"))) {
        puts("Texture table not loaded");
    }
    bgTexture.setRepeated(true);
    sf::Sprite bgSprite;
    bgSprite.setTextureRect(sf::IntRect(0, 0, window->getSize().x, window->getSize().y));
    bgSprite.setTexture(bgTexture);

    // game logic
    while (window->isOpen()) {
        sf::Event event;
        event.type = sf::Event::MouseButtonPressed;
        event.mouseButton.button = sf::Mouse::Left;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(bgSprite);

        window->setMouseCursorVisible(true);
        window->display();
    }

    return 0;
}
