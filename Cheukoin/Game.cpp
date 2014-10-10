#include "Game.h"

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::setBid(Bid const& bid)
{
    _bid = bid;
}

Bid Game::getBid()
{
    return _bid;
}

void Game::addPlayer(Player& player)
{
    _players.push_back(player);
}

std::vector<Player> Game::getPlayers()
{
    return _players;
}

void Game::addTrick(Trick const& trick)
{
    _tricks.push_back(trick);
}

std::vector<Trick> Game::getTricks()
{
    return _tricks;
}