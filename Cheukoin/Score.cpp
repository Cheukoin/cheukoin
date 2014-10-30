#include "Score.h"

using namespace std;

Score::Score()
    : _sprite(make_shared<sf::Sprite>())
    , _text1(make_shared<sf::Text>())
    , _text2(make_shared<sf::Text>())
    , _texture(make_shared<sf::Texture>())
{
    _text1->setString("Team 1: ");
    _text2->setString("Team 2: ");
}

Score::~Score()
{
}

void Score::displayScore(int score1, int score2, std::shared_ptr<sf::RenderWindow> window)
{
    _texture->loadFromFile(resourcePath("scoreBoard.png"));
    _sprite->setTexture(*_texture);
    _sprite->setTextureRect(sf::IntRect(window->getSize().x * 0.9, 20, 70, 30));
    sf::Rect<float> v = _sprite->getGlobalBounds();
    //_sprite->setScale(sf::Vector2f(0.1f, 0.1f));
    //_sprite->setPosition(window->getSize().x - 100, 20);

    sf::Font font;
    if (!font.loadFromFile(resourcePath("sansation.ttf")))
        puts("_texture file not loaded");

    _text1->setPosition(window->getSize().x * 0.1, window->getSize().y * 0.1);
    _text1->setFont(font);
    _text1->setString("Team 1 : " + to_string(score1));
    _text1->setCharacterSize(window->getSize().y * 0.05);
    _text1->setColor(sf::Color::Red);
    _text2->setPosition(window->getSize().x * 0.1, window->getSize().y * 0.15);
    _text2->setFont(font);
    _text2->setString("Team 2 : " + to_string(score2));
    _text2->setCharacterSize(window->getSize().y * 0.05);
    _text2->setColor(sf::Color::Red);
    window->draw(*_text1);
    window->draw(*_text2);
    window->draw(*_sprite);
};
