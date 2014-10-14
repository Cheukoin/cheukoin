#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Constants.h"

class Trick;
class Player;
class Bid;

class Game {
public:
    static Game& getInstance();

    void setMode(GameMode mode);
    GameMode getMode();

    void setBid(Bid* const& bid);
    Bid* getBid();

    void addPlayer(Player*& player);
    std::vector<Player*> getPlayers();

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
    std::vector<Player*> _players;
    std::vector<Trick*> _tricks;
    std::shared_ptr<sf::RenderWindow> _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Cheukoin !");
};

#endif