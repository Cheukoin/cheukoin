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
    app.initWindow();
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

    Bot bot0("Bot 0", Position::Top);
    Bot bot1("Bot 1", Position::Left);
    Bot bot2("Bot 2", Position::Bottom);
    Human player("Player", Position::Right);
    std::vector<Player> bots = { bot0, bot1, bot2, player };

    Team teamA("Team A");
    teamA.addPlayer(bot0);
    teamA.addPlayer(bot2);

    Team teamB("Team B");
    teamB.addPlayer(bot1);
    teamB.addPlayer(player);

    Lobby lobby("Test lobby", vector<Team>{ teamA, teamB });
    app.startGame(lobby, GameMode::Offline);

    // main game loop
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                app.getGame()->play();
                break;
            default:
                break;
            }
        }

        window->clear();
        window->draw(bgSprite);

        app.getGame()->draw();

        window->display();
    }

    return 0;
}
