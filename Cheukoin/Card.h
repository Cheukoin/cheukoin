#ifndef __Cheukoin_Card__
#define __Cheukoin_Card__

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "ResourcePath.h"

class Card {
public:
    bool isEqual(Card const& a) const;
    std::shared_ptr<sf::Sprite> sprites;
    std::shared_ptr<sf::Texture> _texture;
    Value getValue() const;
    Suit getSuit() const;
    sf::Texture getTexture() const;
    void turn();
    Card(Suit suit, Value value);
    ~Card();
    std::string getFileName();
    sf::Sprite _sprite;
    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
    void moveTo(float x,float y);
    

private:
    Suit _suit;
    Value _value;
};

bool operator==(Card const& a, Card const& b);
bool operator!=(Card const& a, Card const& b);

std::ostream& operator<<(std::ostream& os, const Card& card);

#endif