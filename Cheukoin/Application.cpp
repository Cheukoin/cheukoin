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
    if (!_game) {
        _initGame();
        return;
    }

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

void Application::_initGame()
{
    // init game
    Bot bot1("Bot 1", Position::Top);
    Bot bot2("Bot 2", Position::Left);
    Human human("Human", Position::Bottom);
    Bot bot3("Bot 3", Position::Right);
    std::vector<Player> players = { bot1, bot2, human, bot3 };

    Team teamA("Team A", bot1, human);
    Team teamB("Team B", bot2, bot3);

    Lobby lobby("Test lobby", vector<Team>{ teamA, teamB });

    _game = make_shared<Game>(lobby, GameMode::Offline);
    _game->startGame();
}

void Application::_draw()
{
    _window->clear();

    _window->draw(*_backgroundSprite.get());

    if (_game) {
        _game->draw();
    }
    else {
        // TODO Corentin: clean up this mess
        auto cheukoin = new sf::Sprite();
        auto texture = new sf::Texture();
        if (!texture->loadFromFile(resourcePath("cheukoin.png"))) {
            puts("_texture file not loaded");
        }
        texture->setSmooth(true);
        cheukoin->setTexture(*texture);
        cheukoin->setScale(sf::Vector2f(0.3, 0.3));
        cheukoin->setPosition(
            _window->getSize().x / 2 - cheukoin->getGlobalBounds().width / 2,
            _window->getSize().y / 2 - cheukoin->getGlobalBounds().height / 2);

        _window->draw(*cheukoin);
    }

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