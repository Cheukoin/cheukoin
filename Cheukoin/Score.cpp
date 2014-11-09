#include "Score.h"

using namespace std;

Score::Score()
    : _sprite(make_shared<sf::Sprite>())
    , _texture(make_shared<sf::Texture>())
{
    shared_ptr<sf::Text> _text1 = make_shared<sf::Text>();
    _text.push_back(_text1);
    shared_ptr<sf::Text> _text2 = make_shared<sf::Text>();
    _text.push_back(_text2);
}

Score::~Score()
{
}

void Score::displayScore(int score1, int score2, std::shared_ptr<sf::RenderWindow> window)
{
    vector<int> score = { score1, score2 };
    _texture->loadFromFile(resourcePath("scoreBoard.png"));
    _sprite->setTexture(*_texture);
    _sprite->setTextureRect(sf::IntRect(window->getSize().x, window->getSize().y, window->getSize().x * 0.2, window->getSize().y * 0.2));
    //_sprite->setScale(sf::Vector2f(0.1f, 0.1f));
    //_sprite->setPosition(window->getSize().x - 100, 20);
    _sprite->setScale(1.4, 0.6);
    _sprite->setPosition(window->getSize().x * 0.7, 20);

    window->draw(*_sprite);

    sf::Font font;
    if (!font.loadFromFile(resourcePath("sansation.ttf")))
        puts("_texture file not loaded");

    for (int k = 0; k < 2; k++) {
        _text[k]->setPosition(_sprite->getPosition().x * (1.05), _sprite->getPosition().y*1.1 + k * window->getSize().y * 0.05 );
        _text[k]->setFont(font);
        _text[k]->setString("Team " + to_string(k + 1) + ": " + to_string(score[k]));
        _text[k]->setCharacterSize(window->getSize().y * 0.05);
        _text[k]->setColor(sf::Color::Red);
        window->draw(*_text[k]);
    }
};
