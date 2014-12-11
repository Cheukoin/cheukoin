#include "Score.h"

using namespace std;

Score::Score()
    : AnimatedObject("scoreBoard.png", sf::Vector2f(200.0, 100.0))
    , _text(sf::Text())
    , _font(sf::Font())
{
    if (!_font.loadFromFile(resourcePath("sansation.ttf"))) {
        puts("Font file not loaded");
    }

    _sprite->setPosition(Application::getInstance().getWindow()->getSize().x - getGlobalSize().x, 0);
    _text.setString("");
    _text.setFont(_font);
    _text.setCharacterSize(getGlobalSize().y * 0.3);
    _text.setColor(sf::Color::White);
    _text.setPosition(getGlobalPosition().x + 20,
                      getGlobalPosition().y + 10);
}

Score::~Score()
{
}

void Score::draw()
{
    AnimatedObject::draw();
    Application::getInstance().getWindow()->draw(_text);
}

void Score::setScore(int score1, int score2)
{
    _text.setString("Team 1: " + to_string(score1) + "\nTeam 2: " + to_string(score2));
};

