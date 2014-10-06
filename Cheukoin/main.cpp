#include <SFML/Graphics.hpp>
#include <iostream>
#include "Card.h"
#include "NetworkManager.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cheukoin !");
    Card card = Card::Card();

    NetworkManager::createLobby();
    sf::Vector2i v(1, 1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        auto pos = card.sprite.getPosition();
        if (pos.x > window.getSize().x - card.sprite.getGlobalBounds().width || pos.x < 0) {
            v.x *= -1;
        }
        if (pos.y > window.getSize().y - card.sprite.getGlobalBounds().height || pos.y < 0) {
            v.y *= -1;
        }
        card.sprite.setPosition(pos.x + v.x, pos.y + v.y);

        window.clear(sf::Color::Color(63, 150, 61, 255));
        window.draw(card.sprite);
        window.display();
    }

    return 0;
}