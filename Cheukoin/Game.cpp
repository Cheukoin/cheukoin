#include "Game.h"

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::setCurrentBid(Bid* const& bid)
{
    _currentBid = bid;
}

Bid* Game::getCurrentBid()
{
    return _currentBid;
}
