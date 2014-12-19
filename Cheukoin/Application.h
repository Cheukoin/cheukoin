#ifndef __Cheukoin_Application__
#define __Cheukoin_Application__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Game.h"

class AnimatedObject;

class Application {
public:
    static Application& getInstance();

    std::shared_ptr<Game> getGame();
    std::shared_ptr<sf::RenderWindow> getWindow();

    void initWindow();
    void initGame();
    void mainLoop();
    void setNewGameLaunched(bool launched);

    void displayNextButton();
    void displayEndButton();

private:
    Application(){};
    Application(Application const&);
    void operator=(Application const&);

    bool _newGameLaunched;

    std::unique_ptr<AnimatedObject> _cheukoin;
    std::unique_ptr<AnimatedObject> _nextGameButton;
    std::unique_ptr<AnimatedObject> _endButton;

    void _makeNextButton();
    void _makeEndButton();

    std::shared_ptr<Game> _game;
    std::shared_ptr<sf::RenderWindow> _window;

    std::unique_ptr<sf::Sprite> _backgroundSprite;
    std::unique_ptr<sf::Texture> _backgroundTexture;

    void _draw();
    void _handleClick();
    void _startNewGame();
    void _computeGameScore();
    void _showGameOver();
};

#endif
