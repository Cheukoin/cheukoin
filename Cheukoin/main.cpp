#include <iostream>

#include "Card.h"
#include "Trick.h"
#include "NetworkManager.h"
#include "Hand.h"
#include "Player.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cheukoin !");
    Card card = Card(Clubs, Nine);
    Card card2 = Card(Spades, Seven);
    Player player1;

    Hand hand1;
    hand1.addCard(card);

    NetworkManager::createLobby();
    sf::Vector2i v(1, 1);

    while (window.isOpen()) {
        sf::Event event;
        event.type = sf::Event::MouseButtonPressed;
        event.mouseButton.button = sf::Mouse::Left;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Texture clubsNine;
        clubsNine.loadFromFile(resourcePath("ClubsNine.png"));
        card.changeTexture(clubsNine);
        sf::Texture spadesSeven;
        spadesSeven.loadFromFile(resourcePath("SpadesSeven.png"));
        sf::Sprite sprite = card.getSprite();
        sprite.scale(0.2f, 0.2f);
        card2.changeTexture(spadesSeven);
        sf::Sprite sprite2 = card2.getSprite();
        sprite2.scale(0.2f, 0.2f);
        sprite2.setPosition(sprite.getPosition());
        sprite2.move(20, 0);
        window.clear(sf::Color::Color(63, 150, 61, 255));
        window.draw(sprite);
        window.draw(sprite2);
        window.display();
    }

    return 0;
}
