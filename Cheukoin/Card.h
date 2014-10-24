#ifndef __Cheukoin_Card__
#define __Cheukoin_Card__

#include <math.h>
#include <iostream> // std::cout
#include <algorithm> // std::shuffle
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "Application.h"
#include "ResourcePath.h"

class Card {
public:
    Card();
    Card(Suit suit, Value value);
    ~Card();

    Value getValue() const;
    Suit getSuit() const;
    sf::Vector2f getGlobalPosition() const;
    sf::Texture getTexture() const;
    sf::Vector2u getGlobalSize() const;

    void draw() const;

    void flip();
    void moveTo(sf::Vector2u const& position);

    static std::vector<Card> getAllCards();
    static std::vector<Card> getAllCardsShuffled();

    static const std::vector<std::string> SuitNames;
    static const std::vector<std::string> ValueNames;

private:
    Suit _suit;
    Value _value;
    sf::Vector2u _size;

    std::string _getFilename();

    std::shared_ptr<sf::Sprite> _sprite;
    std::shared_ptr<sf::Texture> _texture;
};

bool operator==(Card const& a, Card const& b);
bool operator!=(Card const& a, Card const& b);

std::ostream& operator<<(std::ostream& os, const Card& card);

#endif