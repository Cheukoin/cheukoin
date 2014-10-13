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

    Hand hand1({ card }, Up);
    Hand hand2({ card4, card2 }, Down);
    Hand hand3({ card5 }, Right);
    Hand hand4({ card3 }, Left);

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
        hand4.displayCards(window);
        hand2.displayCards(window);
        hand3.displayCards(window);
        hand1.displayCards(window);
        hand2.playByClick(window);
        if (hand2.cardPlayed() == true) {
            hand1.playOneCard(window, card);
            hand3.playOneCard(window, card5);
            hand4.playOneCard(window, card3);
        }
        window.setMouseCursorVisible(true);
        window.display();
    }

    return 0;
}
