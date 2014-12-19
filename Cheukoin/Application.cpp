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
    if (_game->getBid()->getAmount() == 0) {
        _game->makeBid();
        return;
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    sf::IntRect humanBounds = _game->getHuman()->getGlobalBounds();
    bool gameIsOver = (_game->getLobby()->getTeams()[0]->computeTotalScore() > 1000
                       || (_game->getLobby()->getTeams()[1]->computeTotalScore() > 1000));

    _game->addTrickToWinnerTeam();

    bool playerIsPlaying = (_game->getCurrentRound() != 8)
                           && (_game->getBid()->getAmount() != 0)
                           && (_game->getCurrentPlayer() == _game->getHuman()
                               && humanBounds.contains(mousePosition));

    if (playerIsPlaying) {
        _game->getCurrentPlayer()->play();
    }
    _game->play(playerIsPlaying);

    if (_game->getCurrentRound() > 7 && !_newGameLaunched) {
        moveToNextGame();
        _newGameLaunched = true;
        return;
    }

    else if (_game->getCurrentRound() > 7 && _newGameLaunched) {
        mousePosition = sf::Mouse::getPosition(*Application::getInstance().getWindow());
        AnimatedObject button = displayNextButton();
        sf::IntRect rect = sf::IntRect(button.getGlobalPosition().x,
                                       button.getGlobalPosition().y,
                                       button.getGlobalSize().x,
                                       button.getGlobalSize().y);

        if (rect.contains(mousePosition)) {
            cout << "next button clicked!" << endl;
            shared_ptr<Lobby> lobby = _game->getLobby();
            _game = make_shared<Game>(lobby, Offline);
            _game->startGame();
        }
    }

    if (gameIsOver) {
        AnimatedObject button = displayEndButton();
        sf::IntRect rect2 = sf::IntRect(button.getGlobalPosition().x,
                                        button.getGlobalPosition().y,
                                        button.getGlobalSize().x,
                                        button.getGlobalSize().y);

        if (rect2.contains(mousePosition)) {
            cout << "game over" << endl;
        }
    }
}

void Application::setNewGameLaunched(bool boolean)
{
    _newGameLaunched = boolean;
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
    AnimatedObject button = AnimatedObject("nextButton.png", sf::Vector2f(530, 152));
    button.setPosition(winSize.x / 2 - button.getGlobalSize().x / 2,
                       winSize.y / 2 - button.getGlobalSize().y / 2);
    return button;
}

AnimatedObject Application::displayEndButton()
{
    sf::Vector2u winSize = Application::getInstance().getWindow()->getSize();
    AnimatedObject button = AnimatedObject("endButton.png", sf::Vector2f(396, 231));
    button.setPosition(winSize.x / 2 - button.getGlobalSize().x / 2,
                       winSize.y / 2 - button.getGlobalSize().y / 2);
    return button;
}

void Application::moveToNextGame()
{
    cout << "Game finished!" << endl;
    computeGameScore();
    for (auto team : _game->getLobby()->getTeams()) {

        //team->updateTotalScore(team->getScore());
        team->setScore(0);
        cout << team->getName() << " has " << team->computeTotalScore() << " points" << endl;
    }
}
void Application::startNewGame()
{
    cout << "Game finished!" << endl;
    displayNextButton();
    moveToNextGame();
    return;
}

void Application::computeGameScore()
{

    shared_ptr<Player> biddingPlayer = _game->getCurrentBiddingPlayer();
    cout << "Bidder was " << biddingPlayer->getName() << endl;
    shared_ptr<Team> biddingTeam = _game->getLobby()->getTeamForPlayer(*biddingPlayer);
    cout << "Bidding team is " << biddingTeam->getName() << endl;
    shared_ptr<Team> otherTeam = _game->getLobby()->getTeamForPlayer(*biddingPlayer, true);
    cout << "the other team is " << otherTeam->getName() << endl;
    if (biddingTeam->getScore() >= _game->getBid()->getAmount()) {
        cout << biddingTeam->getName() + " has won and adds " << _game->getBid()->getAmount() << " points to its " << biddingTeam->getScore() << " points" << endl;
        biddingTeam->updateTotalScore(_game->getBid()->getAmount() + biddingTeam->getScore());
        cout << otherTeam->getName() << " keeps its " << otherTeam->getScore() << " points" << endl;
        otherTeam->updateTotalScore(otherTeam->getScore());
    }
    else {
        cout << biddingTeam->getName() + " has lost" << endl;
        cout << biddingTeam->getName() << " loses its " << biddingTeam->getScore() << " points" << endl;
        biddingTeam->updateTotalScore(0);
        cout << otherTeam->getName() << " has won the bet and adds " << _game->getBid()->getAmount() << " points to its " << otherTeam->getScore() << " points" << endl;
        otherTeam->updateTotalScore(_game->getBid()->getAmount() + otherTeam->getScore());
    }
}
