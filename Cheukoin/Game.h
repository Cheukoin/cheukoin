#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Score.h"

class Rules;
class Trick;
class Player;
class Team;
class Lobby;
class Bot;
class Bid;
class Human;
class Score;

class Game {
public:
    Game(std::shared_ptr<Lobby> lobby, GameMode const& mode);

    void startGame();

    GameMode getMode();

    void setBid(std::shared_ptr<Bid> bid);
    std::shared_ptr<Bid> getBid();

    std::shared_ptr<Lobby> getLobby();

    void addTrick(Trick const& trick);

    Trick& getCurrentTrick();

    std::shared_ptr<Rules> getRules();

    std::vector<std::shared_ptr<Bot> > getBots();
    std::shared_ptr<Human> getHuman();
    std::shared_ptr<Player> getCurrentPlayer();

    void draw();
    void sortCards();
    void play(bool playerIsPlaying = false);

    void initializeRound();
    
    void displayNextButton();

private:
    GameMode const& _mode;
    std::shared_ptr<Bid> _bid;
    std::shared_ptr<Lobby> _lobby;
    std::vector<Trick> _tricks;
    int _currentRound;
    int _currentPlayerIndex;
    std::shared_ptr<Rules> _rules;
    void _goToNextPlayer();
    Score _score;
};

#endif