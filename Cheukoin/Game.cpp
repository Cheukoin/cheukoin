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

    for (auto bot : getBots()) {

        bot->initialize();
    }
}

void Game::playRound()
{
    cout << "Playing round " << _currentRound << endl;
    Trick trick(_currentRound);
    _tricks.push_back(trick);
    for (auto bot : getBots()) {
        bot->play();
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

vector<shared_ptr<Bot> > Game::getBots()
{
    vector<shared_ptr<Bot> > bots;
    for (auto player : _lobby.getPlayers()) {
        shared_ptr<Bot> bot = static_pointer_cast<Bot>(player);
        if (bot) {
            bots.push_back(bot);
        }
    }

    return bots;
}

void Game::draw()
{
    int count = 0;
    for (auto player : _lobby.getPlayers()) {
        vector<Card> cards = player.get()->getCards();
        for (int i = 0; i < cards.size(); i++) {
            cards[i].draw();
        }
        count++;
    }
}