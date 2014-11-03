#include "Player.h"

#include "Bot.h"

using namespace std;

vector<string> const PositionNames = {
    "Left",
    "Right",
    "Top",
    "Bottom"
};

vector<int> Player::ScoreSuitIsBid = {
    11,
    4,
    3,
    20,
    10,
    14,
    0,
    0
};

vector<int> Player::ScoreSuitIsNotBid = {
    11,
    4,
    3,
    2,
    10,
    0,
    0,
    0
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

void Player::initialize()
{
    sf::Vector2u pos;
    sf::Vector2u winSize = Application::getInstance().getWindow()->getSize();
    sf::Vector2u cardSize = _cards.front().getGlobalSize();
    sort(_cards.begin(), _cards.end(), [](const Card& a, const Card& b) {
        if (a.getSuit() == b.getSuit()){
            if (a.getSuit()!= Application::getInstance().getGame()->getBid().getSuit())
                return (ScoreSuitIsNotBid[a.getValue()]<ScoreSuitIsNotBid[b.getValue()]);
            else
                return (ScoreSuitIsBid[a.getValue()]<ScoreSuitIsBid[b.getValue()]);
        }
        else
            return a.getSuit()> b.getSuit();
    });
    switch (_position) {
    case Top:
        pos = sf::Vector2u(winSize.x / 2, 0);
        break;
    case Bottom:
        pos = sf::Vector2u(winSize.x / 2, winSize.y - cardSize.y);
        break;
    case Left:
        pos = sf::Vector2u(cardSize.x * 1.05, winSize.y / 2 - cardSize.y / 2);
        break;
    case Right:
        pos = sf::Vector2u(winSize.x - cardSize.x, winSize.y / 2 - cardSize.y / 2);
        break;
    default:
        pos = sf::Vector2u(0, 0);
        break;
    }

    for (int i = 0; i < _cards.size(); i++) {
        _cards[i].flip();
        _cards[i].moveTo(sf::Vector2u(pos.x + 20 * (i - 4) - cardSize.x / 2, pos.y));
    }
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
    sf::Vector2u cardSize = card.getGlobalSize();
    sf::Vector2u pos(winSize.x / 2 - cardSize.x / 2, winSize.y / 2 - cardSize.y / 2);

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
        pos = sf::Vector2u(0, 0);
        break;
    }

    sf::Vector2f currentPosition = card.getGlobalPosition();
    while (abs(pos.y - currentPosition.y) + abs(pos.x - currentPosition.x) > 5) {
        currentPosition.y += (pos.y - currentPosition.y) / 2;
        currentPosition.x += (pos.x - currentPosition.x) / 2;
        card.moveTo(sf::Vector2u(currentPosition.x, currentPosition.y));
        Application::getInstance().forceWindowRefresh();
    }
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
