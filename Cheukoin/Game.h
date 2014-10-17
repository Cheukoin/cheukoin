#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Constants.h"

class Trick;
class Player;
class Team;
class Bot;
class Bid;
class Lobby;

class Game {
public:
    static Game& getInstance();

    void startGame();

    void setMode(GameMode mode);
    GameMode getMode();

    void setBid(Bid* const& bid);
    Bid* getBid();

    std::shared_ptr<Lobby> getLobby();

    void addTrick(Trick* const& trick);
    std::vector<Trick*> getTricks();
    Trick* getCurrentTrick();

    std::shared_ptr<sf::RenderWindow> getWindow();
    void initWindow();

private:
    Game(){};
    Game(Game const&);
    void operator=(Game const&);

    GameMode _mode;
    Bid* _bid;
    std::shared_ptr<Lobby> _lobby;
    std::vector<Player*> _players;
    std::vector<Trick*> _tricks;
    std::shared_ptr<sf::RenderWindow> _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Cheukoin !");
};

#endif