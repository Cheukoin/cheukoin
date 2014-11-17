#include "Game.h"
#include "Bid.h"
#include "Bot.h"
#include "Team.h"
#include "Lobby.h"
#include "Player.h"
#include "Human.h"
#include "Rules.h"
#include "Asset.h"
#include "Score.h"

using namespace std;

Game::Game(shared_ptr<Lobby> lobby, GameMode const& mode)
    : _lobby(lobby)
    , _mode(mode)
    , _currentRound(-1)
    , _tricks(vector<Trick>())
    , _currentPlayerIndex(0)
    , _asset(make_shared<Asset>())
    , _score(make_shared<Score>())
{
    initializeRound();

    _bid = make_shared<Bid>(Spades, 0);
    _rules = make_shared<Rules>(Spades);
}

void Game::startGame()
{
    _lobby->deal();

    for (auto player : _lobby->getPlayers()) {
        player->initialize();
    }
}

void Game::play(bool playerIsPlaying)
{
    if (_currentRound > 7) {
        cout << "Game finished!" << endl;
        displayNextButton();
        moveToNextGame();
        return;
    }

    if (getHuman() == getCurrentPlayer() && !playerIsPlaying) {
        cout << "Waiting for player's move" << endl;
        return;
    }
    if ((playerIsPlaying)
        && (getCurrentPlayer()->getCards().size()
            == static_cast<unsigned>(7 - _currentRound))) {
        _goToNextPlayer();
        if (_tricks.back().getCards().back() != getCurrentPlayer()->getPlayedCard()) {
            // make sure last card played is by current player
            return;
        }
    }

    if (getHuman() != getCurrentPlayer()) {
        getCurrentPlayer()->play();
        _goToNextPlayer();
        getHuman()->showLegalCards();
    }
    if (_tricks.back().getCards().back() != getCurrentPlayer()->getPlayedCard()) {
        // make sure last card played is by current player
        return;
    }
}

void Game::update(sf::Time elapsed)
{
    for (auto player : _lobby->getPlayers()) {
        player->update(elapsed);
    }

    for (auto card : getCurrentTrick().getCards()) {
        card.update(elapsed);
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

    Trick trick(_currentRound);
    _tricks.push_back(trick);
    _currentRound++;

    if (getHuman()->getCards().size()) {
        getHuman()->showLegalCards();
    }

    _score->setScore(
        _lobby->getTeams()[0]->getScore(),
        _lobby->getTeams()[1]->getScore());

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

void Game::setBid(shared_ptr<Bid> bid)
{
    _bid = bid;
    _rules = make_shared<Rules>(_bid->getSuit());

    for (auto& player : _lobby->getPlayers()) {
        player->sortCards();
    }

    cout << "Current bid is " << _bid->getAmount() << " " << SuitNames.at(_bid->getSuit()) << endl;
    AnimatedObject bidDisplay("scoreBoard.png", sf::Vector2f(100, 100));
    bidDisplay.draw();
}

shared_ptr<Bid> Game::getBid()
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
    if (_bid->getAmount() == 0) {
        AnimatedObject bids("c.png", sf::Vector2f(320, 240));
        bids.setPosition(Application::getInstance().getWindow()->getSize().x / 3,
                         Application::getInstance().getWindow()->getSize().y / 3);
        bids.draw();
    }

    for (auto player : _lobby->getPlayers()) {
        player->drawCards();
    }

    if (_tricks.size() > 0) {
        _tricks.back().draw();
    }

    if (_asset->isSet()) {
        _asset->draw();
    }

    if (_score) {
        _score->draw();
    }
}

void Game::displayNextButton()
{

    shared_ptr<sf::Texture> texture = make_shared<sf::Texture>();
    shared_ptr<sf::Sprite> sprite = make_shared<sf::Sprite>();
    if (!texture->loadFromFile(resourcePath("next-arrow.png"))) {
        puts("texture file not loaded");
    }
    sf::Vector2u winSize = Application::getInstance().getWindow()->getSize();

    texture->setSmooth(true);
    sprite->setTextureRect(sf::IntRect(0, 0, 960, 720));
    sprite->setTexture(*texture);
    sprite->setScale(0.3, 0.3);
    sf::Vector2u pos = sf::Vector2u(winSize.x / 3, winSize.y / 3);
    sprite->setPosition(pos.x, pos.y);
}

void Game::displayAsset(Suit asset)
{
    _asset->setSuit(asset);
    _asset->setPosition(10, 10);
}

void Game::setCurrentRound(int const& round)
{
    _currentRound = round;
}

void Game::moveToNextGame()
{
    for (auto team : getLobby()->getTeams()) {
        team->updateTotalScore(team->getScore());
        team->setScore(0);
        cout << team->getName() << " has " << team->computeTotalScore() << " points" << endl;
    }
    setCurrentRound(0);
    startGame();
}
