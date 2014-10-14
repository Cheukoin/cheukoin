#include "Hand.h"

Hand::Hand(std::vector<Card> cards, Position position)
    : _cards(cards)
    , _position(position)
{
    sf::Vector2f pos = _cards[0].sprite->getPosition();
#warning TODO : search another way
    switch (_position) {
    case Left:
        for (int i = 0; i < _cards.size(); i++) {
            _cards[i].sprite->setPosition(pos.x, 100 + i * 40);
        }

    case Right:
        for (int i = 0; i < _cards.size(); i++) {
            _cards[i].sprite->setPosition(700, 100 + i * 40);
        }

    case Down:
        for (int i = 0; i < _cards.size(); i++) {
            _cards[i].sprite->setPosition(150 + i * 50, 10);
        }

    case Up:
        for (int i = 0; i < _cards.size(); i++) {
            _cards[i].sprite->setPosition(150 + i * 50, 450);
        }

    default:
        break;
    }
}

Hand::~Hand()
{
}

Hand::Hand()
{
}

void Hand::playByClick(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (auto card : _cards) {
            if (card.sprite->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                card.flip();
                moveToTrick(card);
            }
        }
    }
}
void Hand::playCard(sf::RenderWindow& window, Card c)
{
    int i = 0;
    if (_cards.size() != 0)
        for (i = 0; i < _cards.size(); i++)
            if (_cards[i] == c) {
                _cards[i].flip();
                move(_cards[i]);
            }
}

void Hand::removeCard(Card const& card)
{
    int i = 0;
    if (_cards.size() != 0) {
        for (i = 0; i < _cards.size(); i++) {
            if (_cards[i] == card) {
                _cards.erase(_cards.begin() + i);
            }
        }
    }
}

void Hand::addCard(Card const& card)
{
    _cards.push_back(card);
}

std::vector<Card> Hand::getCards()
{
    return _cards;
}

void Hand::draw() const
{
    for (auto card : _cards) {
        card.draw();
    }
}

#warning TODO : bouge le dans card
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
        c.sprite->setPosition(300, 225);
    if (_position == Right)
        c.sprite->setPosition(400, 225);
    if (_position == Up)
        c.sprite->setPosition(350, 175);
    if (_position == Down)
        c.sprite->setPosition(350, 275);
}

std::vector<Card> Hand::cardsForSuit(Suit suit)
{
#warning TODO : appeler l'equivalent ds rules
    std::vector<Card> cardsForSuit;
    for (auto c : _cards) {
        if (c.getSuit() == suit) {
            cardsForSuit.push_back(c);
        }
    }
    return cardsForSuit;
}