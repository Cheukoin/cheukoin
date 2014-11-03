#include "Game.h"
#include "Bot.h"
#include "Team.h"
#include "Lobby.h"
#include "Player.h"
#include "Human.h"
#include "Rules.h"

using namespace std;

Game::Game(shared_ptr<Lobby> lobby, GameMode const& mode)
    : _lobby(lobby)
    , _mode(mode)
    , _bid(Bid())
    , _currentRound(-1)
    , _tricks(vector<Trick>())
    , _currentPlayerIndex(0)
{
    initializeRound();
}

void Game::startGame()
{
    _lobby->deal();

    // FOR TEST PURPOSE
    _bid.setAmount(120);
    _bid.setSuit(Hearts);

    _rules = make_shared<Rules>(_bid.getSuit());

    for (auto player : _lobby->getPlayers()) {
        player->initialize();
    }
}

void Game::play(bool playerIsPlaying)
{
    if (_currentRound > 7) {
        cout << "Game finished!" << endl;
        return;
    }

    if (getHuman() == getCurrentPlayer() && !playerIsPlaying) {
        cout << "Waiting for player's move" << endl;
        return;
    }
    if ((playerIsPlaying) && (getCurrentPlayer()->getCards().size() == 7 - _currentRound)) {
        _goToNextPlayer();
        if (_tricks.back().getCards().back() != getCurrentPlayer()->getPlayedCard()) {
            // be sure last card played is by current player
            return;
        }
    }

    if (getHuman() != getCurrentPlayer()) {
        getCurrentPlayer()->play();
        _goToNextPlayer();
        getHuman()->showLegalCards();
    }
    if (_tricks.back().getCards().back() != getCurrentPlayer()->getPlayedCard()) {
        // be sure last card played is by current player
        return;
    }
}

void Game::_goToNextPlayer()
{
    _currentPlayerIndex = (_currentPlayerIndex + 1) % PLAYER_COUNT;
}

void Game::initializeRound()
{
    if (_currentRound >= 0) {
        _currentPlayerIndex = (_currentPlayerIndex + _tricks.back().getWinnerCardIndex()) % PLAYER_COUNT;
    }
    if (getHuman()->getCards().size()) {
        getHuman()->showLegalCards();
    }

    Trick trick(_currentRound);
    _tricks.push_back(trick);
    _currentRound++;
    cout << "Playing round " << _currentRound << endl;
}

shared_ptr<Human> Game::getHuman()
{
    for (auto player : _lobby->getPlayers()) {
        auto human = dynamic_pointer_cast<Human>(player);
        if (human) {
            return human;
        }
    }

    return nullptr;
}

shared_ptr<Player> Game::getCurrentPlayer()
{
    return _lobby->getPlayers().at(_currentPlayerIndex);
}

GameMode Game::getMode()
{
    return _mode;
}

shared_ptr<Lobby> Game::getLobby()
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

shared_ptr<Rules> Game::getRules()
{
    return _rules;
}

void Game::addTrick(Trick const& trick)
{
    _tricks.push_back(trick);
}

Trick& Game::getCurrentTrick()
{
    return _tricks.back();
}

vector<shared_ptr<Bot> > Game::getBots()
{
    vector<shared_ptr<Bot> > bots;
    for (auto player : _lobby->getPlayers()) {
        auto bot = dynamic_pointer_cast<Bot>(player);
        if (bot) {
            bots.push_back(bot);
        }
    }

    return bots;
}

void Game::draw()
{
    for (auto player : _lobby->getPlayers()) {
        player->drawCards();
    }

    if (_tricks.size() > 0) {
        _tricks.back().draw();
    }
    _score.displayScore(Application::getInstance().getGame()->getLobby()->getTeams()[0]->getScore(), Application::getInstance().getGame()->getLobby()->getTeams()[1]->getScore(), Application::getInstance().getWindow());
}
