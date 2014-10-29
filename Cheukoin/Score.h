#ifndef __Cheuckoin_Score__
#define __Cheuckoin_Score__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcePath.h"

class Score {
public:
    Score();
    ~Score();
    std::vector<int> getScores;
    void displayScore(int score1, int score2, std::shared_ptr<sf::RenderWindow> window);

private:
    std::shared_ptr<sf::Texture> _texture;
    std::shared_ptr<sf::Sprite> _sprite;
    std::shared_ptr<sf::Text> _text1;
    std::shared_ptr<sf::Text> _text2;
};

#endif