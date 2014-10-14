#include "Hand.h"

Hand::Hand(std::vector<Card> cards, Position position)
    : _cards(cards)
    , _position(position)
{
}
Hand::Hand()
    : _cards()
    , _position()

{
}
Hand::~Hand()
{
}

void Hand::removeCard(Card const& card)
{
    int i = 0;
    if (_cards.size() != 0)
        for (i = 0; i < _cards.size(); i++)
            if (_cards[i] == card) {
                _cards.erase(_cards.begin() + i);
            }
}

void Hand::addCard(Card const& card)
{
    _cards.push_back(card);
}

bool Hand::isHandValid()
{
    return (_cards.size() <= 8);
}

std::vector<Card> Hand::getCards()
{
    return _cards;
}

std::vector<sf::Sprite> Hand::displayCards() const
{
    int i = 0;
    std::vector<sf::Sprite> vect;
    auto pos = _cards[0].sprites->getPosition();
    if (_position == Left) {
        for (i = 0; i < _cards.size(); i++) {
            _cards[i].sprites->setPosition(pos.x, 100 + i * 40);
            vect.push_back(*_cards[i].sprites);
        }
    }
    if (_position == Right) {
        for (i = 0; i < _cards.size(); i++) {
            _cards[i].sprites->setPosition(700, 100 + i * 40);
            vect.push_back(*_cards[i].sprites);
        }
    }

    if (_position == Up) {
        for (i = 0; i < _cards.size(); i++) {
            _cards[i].sprites->setPosition(100 + i * 50, 10);
            vect.push_back(*_cards[i].sprites);
        }
    }

    if (_position == Down) {
        for (i = 0; i < _cards.size(); i++) {
            _cards[i].sprites->setPosition(100 + i * 50, 450);
            vect.push_back(*_cards[i].sprites);
        }
    }
    return vect;
}

std::vector<Card> Hand::cardsForSuit(Suit suit)
{
    std::vector<Card> cardsForSuit;
    for (auto c : _cards) {
        if (c.getSuit() == suit) {
            cardsForSuit.push_back(c);
        }
    }
    return cardsForSuit;
}

std::vector<Card> cardsForSuit(std::vector<Card> cards, Suit suit)
{
    std::vector<Card> cardsForSuit;
    for (auto c : cards) {
        if (c.getSuit() == suit) {
            cardsForSuit.push_back(c);
        }
    }
    return cardsForSuit;
}

void Hand::displayHand(Position pos, sf::RenderWindow& window)
{
    float width = window.getSize().x;
    float height = window.getSize().y;
    float cardWidth = _cards[0].getSprite().getGlobalBounds().width;
    float cardHeight = _cards[0].getSprite().getGlobalBounds().height;
    float offset = 40;
    float alpha = (width - offset) / (((8 + 1) / 2) * cardWidth + 2 * cardHeight);
    int k = 0;
    if (pos == Up) {
        float beginningTop = (width - (_cards.size() + 1) * cardWidth * alpha / 2) / 2;
        for (auto c : _cards) {
            sf::Sprite sprite = c.getSprite();
            sprite.setScale(alpha, alpha);
            sprite.setPosition(beginningTop + k * cardWidth * alpha / 2, 20);
            k += 1;
            window.draw(sprite);
        }
    }
    else if (pos == Left) {
        float beginningLeft = (height - (_cards.size() + 1) * cardWidth * alpha / 2) / 2;
        for (auto c : _cards) {
            sf::Sprite sprite = c.getSprite();
            sprite.setScale(alpha, alpha);
            sprite.setRotation(-90);
            sprite.setPosition(20, beginningLeft + k * cardWidth * alpha / 2);
            k += 1;
            window.draw(sprite);
        }
    }
}
