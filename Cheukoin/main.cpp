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
    Card card = Card(Clubs, King);
    Card card2 = Card(Clubs, Nine);
    Card card3 = Card(Spades, Queen);
    Card card4 = Card(Hearts, Seven);
    Card card5 = Card(Hearts, Ten);
    Trick trick = Trick(1);
    Player player1;

    Hand hand1({ card, card4, card2, card5 }, Left);
    Hand tric({ card3 }, Up);
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
        std::vector<sf::Sprite> vect = hand1.displayCards();
        for (int i = 0; i < vect.size(); i++) {
            window.draw(vect[i]);
            sf::sleep(sf::milliseconds(3));
        }
        std::vector<sf::Sprite> vect1 = tric.displayCards();
        for (int i = 1; i < vect1.size(); i++) {
            window.draw(vect1[i]);
            sf::sleep(sf::milliseconds(3));
        }

        int k = 0;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        int b = 0;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            std::vector<Card> vect2 = hand1.getCards();

            for (k = 0; k < vect2.size(); k++) {
                if (mousePosition.x >= vect2[k].getLeft() && mousePosition.x <= vect2[k].getRight() && mousePosition.y >= vect2[k].getTop() && mousePosition.y <= vect2[k].getBottom()) {
                    vect2[k].turn();
                    //hand1.removeCard(card)
                    //vect2[k] move

                    b = k;

                    //play k + condition valid to play the card
                    // remove card hand , add to current trick move & display the current trick
                }
            }
        }

        //play card player left
        //player1.playCard(card);
        hand1.removeCard(card);
        auto pos = card.sprites->getPosition();
        sf::Vector2i v(1, 1);
        if (pos.y > 200) {
            if (pos.x > 200)
                card.sprites->setPosition(pos.x - v.x, pos.y - v.y);
            if (pos.x < 200)
                card.sprites->setPosition(pos.x + v.x, pos.y - v.y);
        }
        else {
            if (pos.x > 200)
                card.sprites->setPosition(pos.x - v.x, pos.y + v.y);
            else
                card.sprites->setPosition(pos.x + v.x, pos.y + v.y);
        }
        if ((pos.x > 200)
            && (pos.y > 200) && (pos.y < 300) && (pos.x < 400)) {
            v.x = 0;
            v.y = 0;
            card.sprites->setPosition(pos.x, pos.y);
        }
        card.turn();

        window.draw(*card.sprites);
        window.setMouseCursorVisible(true);
        window.display();
    }

    return 0;
}
