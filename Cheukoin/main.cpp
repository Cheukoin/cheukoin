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
    Card card2 = Card(Spades, King);
    Card card3 = Card(Spades, Queen);
    Card card4 = Card(Hearts, Seven);
    Trick trick = Trick(1);
    Player player1;

    Hand hand1({ card3, card4, card2, card }, Down);
    player1.setHand(hand1);
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
        window.clear(sf::Color::Color(63, 150, 61, 255));

        //display Hand left
        int i = 0;
        std::vector<sf::Sprite> vect = hand1.displayCards();
        for (i = 0; i < vect.size(); i++) {
            window.draw(vect[i]);
        }
        int k = 0;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            std::vector<Card> vect2 = hand1.getCards();
            for (k = 0; k < vect2.size(); k++) {
                if (mousePosition.x >= vect2[k].getLeft() && mousePosition.x <= vect2[k].getRight() && mousePosition.y >= vect2[k].getTop() && mousePosition.y <= vect2[k].getBottom()) {
                    vect2[k].turn();
                    // pb avec la texture 
                    card.turn();
                    //play k + condition valid to play the card
                }
            }
        }

        //play card player left
        //player1.playCard(card);

        hand1.removeCard(card);
        auto pos = card.sprites->getPosition();
        sf::Vector2i v(1, 2);
        if (pos.y >= 200) {
            if (pos.x >= 200)
                card.sprites->setPosition(pos.x - v.x, pos.y - v.y);
            if (pos.x <= 200)
                card.sprites->setPosition(pos.x + v.x, pos.y - v.y);
        }
        else {
            if (pos.x >= 200)
                card.sprites->setPosition(pos.x - v.x, pos.y + v.y);
            else
                card.sprites->setPosition(pos.x + v.x, pos.y + v.y);
        }
        if ((pos.x >= 200)
            && (pos.y > 200) && (pos.y < 400) && (pos.x < 400)) {
            v.x = 0;
            v.y = 0;
            card.sprites->setPosition(pos.x, pos.y);
        }
        //card.turn();
        window.draw(*card.sprites);
        window.setMouseCursorVisible(true);
        window.display();
    }

    return 0;
}
