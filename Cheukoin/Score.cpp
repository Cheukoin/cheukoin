#include "Score.h"

using namespace std;

Score::Score()
    : AnimatedObject("scoreBoard.png", sf::Vector2f(200.0f, 100.0f))
    , _text(sf::Text())
    , _font(sf::Font())
{
    if (!_font.loadFromFile(resourcePath("sansation.ttf"))) {
        puts("Font file not loaded");
    }

    _sprite->setPosition(Application::getInstance().getWindow()->getSize().x - getGlobalSize().x, 0);
    _text.setString("");
    _text.setFont(_font);
    _text.setCharacterSize(getGlobalSize().y * 0.2);
    _text.setColor(sf::Color::Black);
    _text.setPosition(getGlobalPosition().x + 35,
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

void Score::setScore(int score1, int totalScore1, int score2, int totalScore2)
{
    _text.setString("Team 1: " + to_string(score1) + " (" + to_string(totalScore1) + ")"
                    + "\nTeam 2: " + to_string(score2) + " (" + to_string(totalScore2) + ")");
};
