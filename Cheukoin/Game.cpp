#include "Game.h"

using namespace std;

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::setMode(GameMode mode)
{
    _mode = mode;
}

GameMode Game::getMode()
{
    return _mode;
}

void Game::setBid(Bid* const& bid)
{
    _bid = bid;
}

Bid* Game::getBid()
{
    return _bid;
}

void Game::addPlayer(Player*& player)
{
    _players.push_back(player);
}

std::vector<Player*> Game::getPlayers()
{
    return _players;
}

void Game::addTrick(Trick* const& trick)
{
    _tricks.push_back(trick);
}

std::vector<Trick*> Game::getTricks()
{
    return _tricks;
}

Trick* Game::getCurrentTrick()
{
    return _tricks.back();
}

shared_ptr<sf::RenderWindow> Game::getWindow()
{
    return _window;
}
void Game::setWindow(shared_ptr<sf::RenderWindow> window)
{
    _window = window;
}