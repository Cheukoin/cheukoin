#include <iostream>

#include "Card.h"
#include "Trick.h"
#include "NetworkManager.h"
#include "Hand.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cheukoin !");
    Card card = Card(Clubs, Nine);
    Card card2 = Card(Spades, King);
    Card card3 = Card(Spades, Queen);
    Card card4 = Card(Hearts, Seven);
    Trick trick = Trick(1);

    Hand hand1({ card, card2, card3, card4, card2, card3, card4 }, Left);

    hand1.addCard(card3);

    NetworkManager::createLobby();
    sf::Vector2i v(1, 1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Color(63, 150, 61, 255));

        //display Hand left
        int i = 0;
        std::vector<sf::Sprite> vect = hand1.displayCards();
        for (i = 0; i < vect.size(); i++) {
            window.draw(vect[i]);
        }
        card.turn();
        //play card player left
        hand1.removeCard(card);
        auto pos = card.sprites->getPosition();

        trick.addCard(card);
        sf::Vector2i v(2, 1);
        card.sprites->setPosition(pos.x + v.x, pos.y + v.y);
        if ((pos.x > 200)
            && (pos.y > 100)) {
            v.x = 0;
            v.y = 0;
            card.sprites->setPosition(pos.x, pos.y);
        }
        window.draw(*card.sprites);
        window.display();
    }

    return 0;
}
