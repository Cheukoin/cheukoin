#include "Application.h"
#include "Bot.h"
#include "Team.h"
#include "Lobby.h"
#include "Player.h"
#include "AnimatedObject.h"

using namespace std;

Application& Application::getInstance()
{
    static Application instance;
    return instance;
}

void Application::_handleClick()
{
    if (!_game) {
        initGame();
        return;
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    sf::IntRect humanBounds = _game->getHuman()->getGlobalBounds();

    bool playerIsPlaying = (_game->getCurrentPlayer() == _game->getHuman())
                           && (humanBounds.contains(mousePosition));

    if (_game->getCurrentTrick().getCards().size() == PLAYER_COUNT) {
        Card winCard = _game->getCurrentTrick().getWinningCard();

        for (auto player : _game->getLobby()->getPlayers()) {
            if (player->getPlayedCard() == winCard) {
                if (_game->getLobby()->getTeams()[0]->isPlayerInTeam(*player)) {
                    _game->getLobby()->getTeams()[0]->addWonTrick(_game->getCurrentTrick());
                }
                else {
                    _game->getLobby()->getTeams()[1]->addWonTrick(_game->getCurrentTrick());
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

void Application::initGame()
{
    auto bot1 = make_shared<Bot>("Bot 1", Position::Top);
    auto bot2 = make_shared<Bot>("Bot 2", Position::Left);
    auto human = make_shared<Human>("Human", Position::Bottom);
    auto bot3 = make_shared<Bot>("Bot 3", Position::Right);

    auto teamA = make_shared<Team>("Team A", bot1, human);
    auto teamB = make_shared<Team>("Team B", bot2, bot3);

    auto lobby = make_shared<Lobby>("Test lobby", teamA, teamB);

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
        _cheukoin->draw();
    }

    _window->display();
}

void Application::mainLoop()
{
    sf::Event event;
    sf::Clock clock;
    sf::Time elapsed = clock.restart();

    _cheukoin = unique_ptr<AnimatedObject>(new AnimatedObject("cheukoin.png", sf::Vector2f(700, 700)));
    _cheukoin->setPosition(sf::Vector2f(
        _window->getSize().x / 2 - _cheukoin->getGlobalSize().x / 2,
        _window->getSize().y / 2 - _cheukoin->getGlobalSize().y / 2));

    while (_window->isOpen()) {
        elapsed = clock.restart();
        if (_game) {
            _game->update(elapsed);
        }

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

AnimatedObject Application::displayNextButton()
{
    sf::Vector2u winSize = Application::getInstance().getWindow()->getSize();
    sf::Vector2f pos = sf::Vector2f(winSize.x / 3, winSize.y / 3);
    AnimatedObject button = AnimatedObject("nextButton.png", pos);
    button.setPosition(winSize.x / 3, winSize.y / 3);
    return button;
}

void Application::moveToNextGame()
{
    for (auto team : _game->getLobby()->getTeams()) {
        team->updateTotalScore(team->getScore());
        team->setScore(0);
        cout << team->getName() << " has " << team->computeTotalScore() << " points" << endl;
    }
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*Application::getInstance().getWindow());
    sf::IntRect rect = sf::IntRect(displayNextButton().getGlobalPosition().x, displayNextButton().getGlobalPosition().y, displayNextButton().getGlobalSize().x, displayNextButton().getGlobalSize().y);

    if (rect.contains(mousePosition)) {
        _game->setCurrentRound(0);
        shared_ptr<Bid> bidZero = make_shared<Bid>();
        _game->setBid(bidZero);
        _game->startGame();
    }
}
