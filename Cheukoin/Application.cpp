#include "Application.h"
#include "Bot.h"
#include "Team.h"
#include "Lobby.h"
#include "Player.h"

using namespace std;

Application& Application::getInstance()
{
    static Application instance;
    return instance;
}

void Application::_handleClick()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    sf::IntRect rect = _game->getHuman()->getGlobalBounds();
    bool playerIsPlaying = (_game->getCurrentPlayer() == _game->getHuman()) && (rect.contains(mousePosition));

    if (_game->getCurrentTrick().getCards().size() == PLAYER_COUNT) {
        Card winCard = _game->getCurrentTrick().getWinningCard();

        for (auto player : _game->getLobby().getPlayers()) {
            if (player->getPlayedCard() == winCard) {
                if (_game->getLobby().getTeams()[0].isPlayerInTeam(*player)) {
                    _game->getLobby().getTeams()[0].addWonTrick(_game->getCurrentTrick());
                }
                else {
                    _game->getLobby().getTeams()[1].addWonTrick(_game->getCurrentTrick());
                }
            }
        }
        _game->initializeRound();
    }
    if (playerIsPlaying) {
        _game->getCurrentPlayer()->play();
    }
    _game->play(playerIsPlaying);
}

void Application::startGame(Lobby& lobby, GameMode const& mode)
{
    _game = make_shared<Game>(lobby, mode);
    _game->startGame();
}

shared_ptr<sf::RenderWindow> Application::getWindow()
{
    return _window;
}

void Application::initWindow()
{
    _window = make_shared<sf::RenderWindow>(sf::VideoMode(1024, 768), "Cheukoin !");
    _window->setFramerateLimit(60);

    // init background
    _backgroundTexture = unique_ptr<sf::Texture>(new sf::Texture);
    if (!_backgroundTexture.get()->loadFromFile(resourcePath("table.jpeg"))) {
        puts("Texture table not loaded");
    }
    _backgroundTexture.get()->setRepeated(true);

    _backgroundSprite = unique_ptr<sf::Sprite>(new sf::Sprite);
    _backgroundSprite.get()->setTextureRect(sf::IntRect(0, 0, _window->getSize().x, _window->getSize().y));
    _backgroundSprite.get()->setTexture(*_backgroundTexture.get());
}

void Application::_draw()
{
    _window->clear();

    _window->draw(*_backgroundSprite.get());
    _game->draw();

    _window->display();
}

void Application::mainLoop()
{
    sf::Event event;

    while (_window->isOpen()) {
        while (_window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                _window->close();
                break;
            case sf::Event::MouseButtonPressed:

                _handleClick();
                break;
            default:
                break;
            }
        }

        _draw();
    }
}

std::shared_ptr<Game> Application::getGame()
{
    return _game;
}