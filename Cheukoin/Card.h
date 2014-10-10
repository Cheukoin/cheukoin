#ifndef __Cheukoin_Card__
#define __Cheukoin_Card__

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <map>
#include <string>

#include "ResourcePath.h"
#include "Constants.h"

class Card {
public:
    bool isEqual(Card const& a) const;
    std::shared_ptr<sf::Sprite> sprites; //est-ce que ça marche?
    Value getValue() const;
    Suit getSuit() const;
    sf::Texture getTexture() const;
    void turn();
    Card(Suit suit, Value value);
    ~Card();
    void changeTexture(sf::Texture texture2);
    std::string getFileName();
    sf::Sprite _sprite;

private:
    Suit _suit;
    Value _value;
    sf::Texture _texture;
};

bool operator==(Card const& a, Card const& b);
bool operator!=(Card const& a, Card const& b);

std::ostream& operator<<(std::ostream& os, const Card& card);

#endif