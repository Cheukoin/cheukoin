#include "Game.h"
#include "Bot.h"
#include "Team.h"
#include "Lobby.h"

using namespace std;

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::startGame()
{
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

    Lobby lobby("My great lobby", vector<Team>{ teamA, teamB });

    lobby.deal();
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
