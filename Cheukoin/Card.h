#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

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
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> textureBack;

    Card();
    ~Card();
};
