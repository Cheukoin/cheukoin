#include <iostream>

#include "Card.h"
#include "Trick.h"
#include "NetworkManager.h"
#include "Hand.h"
#include "Player.h"
#include <cmath>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cheukoin !");
    Card card = Card(Clubs, Nine);
    Card card2 = Card(Spades, Seven);
    Card card3 = Card(Clubs, Nine);
    Card card4 = Card(Spades, Seven);
    Card card5 = Card(Clubs, Nine);
    Card card6 = Card(Spades, Seven);
    Player player1;

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

        float width = window.getSize().x;
        float height = window.getSize().y;
        sf::Texture clubsNine;
        clubsNine.loadFromFile(resourcePath("ClubsNine.png"));
        sf::Texture spadesSeven;
        spadesSeven.loadFromFile(resourcePath("SpadesSeven.png"));
        sf::Texture spadesEight;
        spadesEight.loadFromFile(resourcePath("SpadesEight.png"));
        sf::Texture spadesNine;
        sf::Texture spadesTen;
        spadesNine.loadFromFile(resourcePath("SpadesNine.png"));
        spadesTen.loadFromFile(resourcePath("SpadesTen.png"));
        card.changeTexture(spadesSeven);
        card2.changeTexture(spadesEight);
        card3.changeTexture(spadesNine);
        card4.changeTexture(spadesTen);
        card5.changeTexture(spadesSeven);
        card6.changeTexture(spadesSeven);
        window.clear(sf::Color::Color(63, 150, 61, 255));

        /*Hand hand1;
        hand1.addCard(card);
        hand1.addCard(card2);
        hand1.addCard(card3);
        hand1.addCard(card4);
        hand1.addCard(card5);
        hand1.addCard(card6);
        hand1.addCard(card6);
        hand1.addCard(card6);
        hand1.displayHand(Up, window);
        hand1.displayHand(Left, window);*/
        std::vector<Card> top = { card, card2, card3, card4, card5, card6, card6, card6 };
        std::vector<Card> left = { card, card2, card3, card4, card5, card6, card6, card6 };
        float cardWidth = card.getSprite().getGlobalBounds().width;
        float cardHeight = card.getSprite().getGlobalBounds().height;
        float alpha = 0.136;
        int k = 0;
        int sizeTop = top.size();
        float beginningTop = (width - (sizeTop + 1) * cardWidth * alpha / 2) / 2;
        int sizeLeft = left.size();
        float beginningLeft = (height - (sizeLeft + 1) * cardWidth * alpha / 2) / 2;
        for (auto c : top) {
            sf::Sprite sprite = c.getSprite();
            sprite.setScale(0.136f, 0.136f);
            sprite.setPosition(beginningTop + k * cardWidth * alpha / 2, 20);
            k += 1;
            window.draw(sprite);
        }
        for (auto c : left) {
            sf::Sprite sprite = c.getSprite();
            sprite.scale(0.136, 0.136);
            sprite.setPosition(beginningLeft + k * cardWidth * alpha / 2, 20);
            sprite.setRotation(-90);
            window.draw(sprite);
        }
        window.display();
    }

    return 0;
}
