#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

using namespace std;

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
    string value;
    string color;
    sf::Sprite sprite;
    shared_ptr<sf::Texture> textureBack;

    void playCard();
    void makeBid();

    Card();
    ~Card();
};
