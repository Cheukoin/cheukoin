#include "Player.h"

#include "Bot.h"

using namespace std;

vector<string> const PositionNames = {
    "Left",
    "Right",
    "Top",
    "Bottom"
};

Player::Player(string name, Position position)
    : _name(name)
    , _position(position)
{
}

Player::Player()
    : _name("Default")
{
}

Player::~Player()
{
}

void Player::sortCards()
{
    sf::Vector2f pos;
    sf::Vector2f winSize = (sf::Vector2f)Application::getInstance().getWindow()->getSize();
    sf::Vector2f cardSize = _cards.front().getGlobalSize();

    sort(_cards.begin(), _cards.end(), [](const Card& a, const Card& b) {
        if (a.getSuit() == b.getSuit()){
            return Application::getInstance().getGame()->getRules()->isCardGreater(b, a, a.getSuit());
        }
        else
            return a.getSuit()> b.getSuit();
    });

    switch (_position) {
    case Top:
        pos = sf::Vector2f(winSize.x / 2, 0);
        break;
    case Bottom:
        pos = sf::Vector2f(winSize.x / 2, winSize.y - cardSize.y);
        break;
    case Left:
        pos = sf::Vector2f(cardSize.x * 1.05, winSize.y / 2 - cardSize.y / 2);
        break;
    case Right:
        pos = sf::Vector2f(winSize.x - cardSize.x, winSize.y / 2 - cardSize.y / 2);
        break;
    default:
        pos = sf::Vector2f(0, 0);
        break;
    }

    for (int i = 0; i < _cards.size(); i++) {
        sf::Vector2f cardPosition(pos.x + 20 * (i - 4) - cardSize.x / 2, pos.y);
        _cards[i].setPosition(cardPosition);
    }
}

void Player::initialize()
{
    sortCards();
}

sf::IntRect Player::getGlobalBounds()
{
    if (_cards.size() == 0) {
        return sf::IntRect(0, 0, 0, 0);
    }

    float right = getCards().back().getGlobalPosition().x
                  - getCards().front().getGlobalPosition().x
                  + getCards().back().getGlobalSize().x;

    sf::IntRect rect(getCards().front().getGlobalPosition().x,
                     getCards().back().getGlobalPosition().y,
                     right,
                     getCards().front().getGlobalSize().y);
    return rect;
}

void Player::playCard(Card const& card)
{
    cout << "-- " << *this << " playing " << card << endl;
    // TODO : verify move is valid with rules

    if (_cards.size() != 0) {
        for (int i = 0; i < _cards.size(); i++) {
            if (_cards[i] == card) {
                _cards[i].flip();
                _moveCardToCenter(_cards[i]);
                _cards.erase(_cards.begin() + i);
            }
        }
    }

    shared_ptr<Game> game = Application::getInstance().getGame();
    game->getCurrentTrick().addCard(card);
    _playedCard = card;

    if (game->getMode() == Online) {
        // TODO : notify server if multiplayer
    }

    for (auto bot : game->getBots()) {
        bot->update();
    }
}

void Player::_moveCardToCenter(Card& card)
{
    sf::Vector2u winSize = Application::getInstance().getWindow()->getSize();
    sf::Vector2f cardSize = card.getGlobalSize();
    sf::Vector2f pos(winSize.x / 2 - cardSize.x / 2, winSize.y / 2 - cardSize.y / 2);

    switch (_position) {
    case Top:
        pos.y -= cardSize.y / 2;
        break;
    case Bottom:
        pos.y += cardSize.y / 2;
        break;
    case Left:
        pos.x -= cardSize.x / 2;
        break;
    case Right:
        pos.x += cardSize.x / 2;
        break;
    default:
        pos = sf::Vector2f(0, 0);
        break;
    }

    card.moveTo(pos, sf::seconds(10));
}

Bid Player::makeBid(int amount, Suit const& asset)
{
    _bid.setAmount(amount);
    _bid.setSuit(asset);
    return _bid;
}

string Player::getName() const
{
    return _name;
}

void Player::setName(string name)
{
    _name = name;
}

Card Player::getPlayedCard()
{
    return _playedCard;
}

Bid Player::getBid() const
{
    return _bid;
}

void Player::setBid(Bid& bid)
{
    _bid = bid;
}

void Player::makeDealer()
{
    _dealer = true;
}

void Player::changeDealer()
{
    _dealer = false;
}

bool Player::isDealer()
{
    return _dealer;
}

// Card management

void Player::addCard(Card card)
{
    _cards.push_back(card);
}

vector<Card> Player::getCards() const
{
    return _cards;
}

void Player::drawCards() const
{
    for (Card card : _cards) {
        card.draw();
    }
}

Position Player::getPosition() const
{
    return _position;
}

void Player::setPosition(Position position)
{
    _position = position;
}

vector<Card> Player::cardsForSuit(Suit suit)
{
    return Application::getInstance().getGame()->getRules()->cardsForSuit(_cards, suit);
}

Card Player::chooseCard()
{
    // TODO fix this
    return Card(Spades, Ace);
}

void Player::update(sf::Time elapsed)
{
    for (auto& card : _cards) {
        card.update(elapsed);
    }
}

bool operator==(Player const& a, Player const& b)
{
    return a.getName() == b.getName();
}

bool operator!=(Player const& a, Player const& b)
{
    return !(a == b);
}

ostream& operator<<(ostream& os, const Player& player)
{
    os << "<Player: " << player.getName() << " at " << PositionNames[player.getPosition()] << ">";
    return os;
}
