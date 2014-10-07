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
    bool isGreater(Card card, Suit suit) const;
    Value getValue() const;
    Suit getSuit() const;

    Card();
    ~Card();
    
private:
    Suit _suit;
    Value _value;
    static std::map<Value, int> _cardValues;
    static std::map<Value, int> _cardValuesAsset;
};
