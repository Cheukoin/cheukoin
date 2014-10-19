#include "Game.h"
#include "Bot.h"
#include "Team.h"
#include "Lobby.h"
#include "Player.h"

using namespace std;

Game::Game(Lobby& lobby, GameMode const& mode)
    : _lobby(lobby)
    , _mode(mode)
    , _bid(Bid())
{
}

void Game::startGame()
{
    _lobby.deal();

    for (auto player : _lobby.getPlayers()) {
        player.get().initialize();
    }

    for (int round = 0; round < 8; round++) {
        cout << "Playing round " << round << endl;
        _playRound();
    }
}

void Game::_playRound()
{
    for (auto player : _lobby.getPlayers()) {
        player.get().play();
    }
}

GameMode Game::getMode()
{
    return _mode;
}

Lobby& Game::getLobby()
{
    return _lobby;
}

void Game::setBid(Bid const& bid)
{
    _bid = bid;
}

Bid Game::getBid()
{
    return _bid;
}

void Game::addTrick(Trick const& trick)
{
    _tricks.push_back(trick);
}

std::vector<Trick> Game::getTricks()
{
    return _tricks;
}

Trick Game::getCurrentTrick()
{
    return _tricks.back();
}

void Game::draw()
{
    int count = 0;
    for (auto player : _lobby.getPlayers()) {
        vector<Card> cards = player.get().getCards();
        for (int i = 0; i < cards.size(); i++) {
            cards[i].draw();
        }
        count++;
    }
}