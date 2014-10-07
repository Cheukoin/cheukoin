#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <iostream>

enum Suit {
    Spades,
    Hearts,
    Diamonds,
    Clubs
};

enum Value {
    Ace,
    King,
    Queen,
    Jack,
    Ten,
    Nine,
    Eight,
    Seven
};

class Card {
public:
    Value value;
    Suit suit;
    bool isEqual(Card const& a) const;
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> textureBack;
    Card(Suit suit, Value value);
    ~Card();

private:
    Suit _suit;
    Value _value;
};
bool operator==(Card const& a, Card const& b);
