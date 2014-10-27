#include "Score.h"

using namespace std;

Score::Score()
    : _texture(make_shared<sf::Texture>())
    , _sprite(make_shared<sf::Sprite>())
    , _text1(make_shared<sf::Text>())
    , _text2(make_shared<sf::Text>())
{
    _texture->loadFromFile(resourcePath("scoreBoard.jpg"));
    _text1->setString("Team 1: ");
    _text2->setString("Team 2: ");
}

Score::~Score()
{
}

void Score::displayScore(int score1, int score2)
{
    _sprite->setTexture(*_texture);
    _sprite->setOrigin(Application::getInstance().getWindow()->getSize().x - 70, 20);
    Application::getInstance().getWindow()->draw(*_sprite);
};
