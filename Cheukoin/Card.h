#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <iostream>

enum Suit {
    Clubs,
    Hearts,
    Diamonds,
    Spades
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
    bool isEqual(Card const& a) const;
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> textureBack;

    Value getValue() const;
    Suit getSuit() const;

    Card(Suit suit, Value value);
    ~Card();

private:
    Suit _suit;
    Value _value;
};

bool operator==(Card const& a, Card const& b);

std::ostream& operator<<(std::ostream& os, const Card& card);
