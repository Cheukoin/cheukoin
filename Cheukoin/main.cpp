#include <iostream>
#include <memory>

#include "Card.h"
#include "Trick.h"
#include "Game.h"
#include "NetworkManager.h"
#include "ResourcePath.h"
#include "Player.h"
#include "Lobby.h"
#include "Bot.h"

using namespace std;

int main()
{
    Application& app = Application::getInstance();
    shared_ptr<sf::RenderWindow> window = app.getWindow();
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

    Bot bot0;
    Bot bot1;
    Bot bot2;
    Bot bot3;

    Team teamA;
    teamA.addPlayer(bot0);
    teamA.addPlayer(bot2);

    Team teamB;
    teamB.addPlayer(bot1);
    teamB.addPlayer(bot3);

    Lobby lobby("Test lobby", vector<Team>{ teamA, teamB });
    app.startGame(lobby, GameMode::Online);

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

        vector<Team> teams = app.getGame()->getLobby().getTeams();

        int count = 0;
        for (Team team : teams) {
            for (Player player : *team.getPlayers()) {
                vector<Card> cards = player.getCards();
                for (int i = 0; i < cards.size(); i++) {
                    cards[i].flip();
                    cards[i].draw();

                    cards[i].moveTo(20 * i, 100 * count);
                }
                count++;
            }
        }

        window->display();
    }

    return 0;
}
