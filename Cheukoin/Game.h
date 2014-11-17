#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Constants.h"

class AnimatedObject;
class Rules;
class Trick;
class Player;
class Team;
class Lobby;
class Bot;
class Bid;
class BidMaker;
class Human;
class Score;
class Asset;

class Game {
public:
    Game(std::shared_ptr<Lobby> lobby, GameMode const& mode);

    void startGame();

    void play(bool playerIsPlaying);
    void initializeRound();

    GameMode getMode();

    void setBid(std::shared_ptr<Bid> bid);
    std::shared_ptr<Bid> getBid();

    std::shared_ptr<BidMaker> getBidMaker();

    std::shared_ptr<Lobby> getLobby();

    void addTrick(Trick const& trick);

    Trick& getCurrentTrick();

    std::shared_ptr<Rules> getRules();

    std::vector<std::shared_ptr<Bot> > getBots();
    std::shared_ptr<Human> getHuman();
    std::shared_ptr<Player> getCurrentPlayer();

    void moveToNextGame();

    /**
     * Draw all game entities to the main window
     */
    void draw();

    /**
     * Update all game entities based on elapsed time since the last main loop iteration
     */
    void update(sf::Time elapsed);

    void sortCards();

    void displayNextButton();
    void displayAsset(Suit asset);
    void setCurrentRound(int const& round);

    void goToNextBiddingPlayer();
    std::shared_ptr<Player> getCurrentBiddingPlayer();

private:
    GameMode const& _mode;
    std::shared_ptr<BidMaker> _bidMaker;
    std::shared_ptr<Bid> _bid;
    std::shared_ptr<Asset> _asset;
    std::shared_ptr<Lobby> _lobby;
    std::shared_ptr<Score> _score;
    std::vector<Trick> _tricks;
    int _currentRound;
    int _currentPlayerIndex;
    int _currentBiddingPlayerIndex;
    std::shared_ptr<Rules> _rules;
    void _goToNextPlayer();
};

#endif
