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
    std::shared_ptr<AnimatedObject> getNextButton();
    std::shared_ptr<AnimatedObject> getEndButton();
    
    void initWindow();
    void initGame();
    void mainLoop();

    void computeGameScore();
    void moveToNextGame();
    void startNewGame();
    void setNewGameLaunched(bool boolean);

private:
    Application(){};
    Application(Application const&);
    void operator=(Application const&);

    std::unique_ptr<AnimatedObject> _cheukoin;
    std::shared_ptr<AnimatedObject> _nextButton;
    std::shared_ptr<AnimatedObject> _endButton;

    std::shared_ptr<Game> _game;
    std::shared_ptr<sf::RenderWindow> _window;

    std::unique_ptr<sf::Sprite> _backgroundSprite;
    std::unique_ptr<sf::Texture> _backgroundTexture;

    void _draw();
    void _handleClick();
    bool _newGameLaunched;
};

#endif
