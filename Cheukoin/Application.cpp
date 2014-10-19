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

void Application::startGame(Lobby& lobby, GameMode const& mode, std::vector<Bot> bots)
{
    _game = make_shared<Game>(lobby, mode, bots);
    _game->startGame();
}

shared_ptr<sf::RenderWindow> Application::getWindow()
{
    return _window;
}

std::shared_ptr<Game> Application::getGame()
{
    return _game;
}