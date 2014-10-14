#include "Hand.h"

Hand::Hand(std::vector<Card> cards, Position position)
    : _cards(cards)
    , _position(position)
    , _cardRemoved(true)
    , _cardPlayed(false)
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
            _cards[i].sprites->setPosition(150 + i * 50, 10);
            vect.push_back(*_cards[i].sprites);
        }
    }

    if (_position == Down) {
        for (i = 0; i < _cards.size(); i++) {
            _cards[i].sprites->setPosition(150 + i * 50, 450);
            vect.push_back(*_cards[i].sprites);
        }
    }
}
Hand::Hand()
    : _cards()
    , _position()

{
}
Hand::~Hand()
{
}
bool Hand::cardPlayed()
{
    return _cardPlayed;
}
void Hand::playByClick(sf::RenderWindow& window)
{
    int k = 0;
    std::vector<Card> vect = _cards;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (k = 0; k < vect.size(); k++) {
            if (mousePosition.x >= vect[k].getLeft() && mousePosition.x <= vect[k].getRight() && mousePosition.y >= vect[k].getTop() && mousePosition.y <= vect[k].getBottom()) {
                vect[k].turn();
                moveToTrick(vect[k]);
                _cardPlayed = true;
            }
        }
    }
}
void Hand::playOneCard(sf::RenderWindow& window, Card c)
{
    int i = 0;
    if (_cards.size() != 0)
        for (i = 0; i < _cards.size(); i++)
            if (_cards[i] == c) {
                _cards[i].turn();
                move(_cards[i]);
            }
}

bool Hand::cardRemoved()
{
    return _cardRemoved;
}
void Hand::removeCard(Card const& card)
{
    _cardRemoved = false;
    int i = 0;
    if (_cards.size() != 0) {
        for (i = 0; i < _cards.size(); i++) {
            if (_cards[i] == card) {
                _cards.erase(_cards.begin() + i);
            }
        }
    }

    _cardRemoved = true;
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

void Hand::displayCards(sf::RenderWindow& window) const
{

    std::vector<Card> vect = _cards;
    for (int i = 0; i < vect.size(); i++) {
        window.draw(*vect[i].sprites);
        sf::sleep(sf::milliseconds(3));
    }
}
void Hand::move(Card c)
{
    if (_position == Left)
        c.moveTo(300, 225);
    if (_position == Right)
        c.moveTo(400, 225);
    if (_position == Up)
        c.moveTo(350, 175);
    if (_position == Down)
        c.moveTo(350, 275);
}
void Hand::moveToTrick(Card c)
{
    if (_position == Left)
        c.sprites->setPosition(300, 225);
    if (_position == Right)
        c.sprites->setPosition(400, 225);
    if (_position == Up)
        c.sprites->setPosition(350, 175);
    if (_position == Down)
        c.sprites->setPosition(350, 275);
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
