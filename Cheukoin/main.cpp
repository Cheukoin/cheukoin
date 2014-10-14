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

    Card card = Card(Hearts, Queen); // 12
    Card card2 = Card(Clubs, Nine); // 05
    Card card3 = Card(Hearts, Ten); //14
    Card card4 = Card(Hearts, King); //11
    Card card5 = Card(Hearts, Ten); //14

    Trick trick = Trick(1);
    Player player1;

    Hand hand1({ card }, Up);
    Hand hand2({ card5, card2 }, Down);
    Hand hand3({ card3 }, Right);
    Hand hand4({ card4 }, Left);

    player1.setHand(hand1);
    NetworkManager::createLobby();
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
        //        window.clear(sf::Color::Color(63, 150, 61, 255));
        window->clear();
        window->draw(bgSprite);

        //display Hand left
        hand4.draw();
        hand2.draw();
        hand3.draw();
        hand1.draw();
        //        hand2.playByClick();
        //        hand4.playOneCard(window, card4);
        //        hand3.playOneCard(window, card3);
        //        hand1.playOneCard(window, card);
        window->setMouseCursorVisible(true);
        window->display();
    }

    return 0;
}
