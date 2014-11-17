#ifndef __Cheuckoin_Score__
#define __Cheuckoin_Score__

#include <iostream>
#include "ResourcePath.h"
#include "AnimatedObject.h"

class Score : public AnimatedObject {
public:
    Score();
    ~Score();

    void draw();

    void setScore(int score1, int score2);

private:
    sf::Text _text;
    sf::Font _font;
};

#endif
