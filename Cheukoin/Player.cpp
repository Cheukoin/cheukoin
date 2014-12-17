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
            return b.isGreaterThan(a, a.getSuit());
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
        positionBottomy = winSize.y - cardSize.y;
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

    for (int i = 0; i < (int)_cards.size(); i++) {
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
                     getCards().back().getGlobalPosition().y * 0.9,
                     right,
                     getCards().front().getGlobalSize().y);
    return rect;
}

void Player::playCard(Card const& card)
{
    cout << "-- " << *this << " playing " << card << endl;
    // TODO : verify move is valid with rules
    unsigned int i = 0;

    for (i = 0; i < _cards.size(); i++) {
        if (_cards[i] == card) {
            _cards[i].show();
            _moveCardToCenter(_cards[i]);
            break;
        }
    }

    shared_ptr<Game> game = Application::getInstance().getGame();
    game->getCurrentTrick().addCard(_cards[i]);
    _playedCard = _cards[i];

    _cards.erase(_cards.begin() + i);

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

    card.moveTo(pos, sf::milliseconds(200));
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
void Player::setCards(vector<Card> cards)
{
    _cards = cards;
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

bool Player::hasCard(Card card)
{
    for (auto cardTemp : _cards)
        if (card == cardTemp)
            return true;
    return false;
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

bool Player::isFriendMaster()
{
    vector<Card> trickCards = Application::getInstance().getGame()->getCurrentTrick().getCards();
    int numberPlayedCards = (int)trickCards.size();
    vector<Card> enemyCards;

    if (numberPlayedCards > 1) {
        Card friendlyCard = trickCards[numberPlayedCards - 2];
        Suit askedSuit = trickCards.front().getSuit();

        for (Card card : trickCards) {
            if (card != friendlyCard) {
                enemyCards.push_back(card);
            }
        }

        return friendlyCard.isGreaterThan(enemyCards[0], askedSuit) && (enemyCards.size() > 1 ? friendlyCard.isGreaterThan(enemyCards[1], askedSuit) : true);
    }

    return false;
}

std::vector<Card> Player::getPlayableCards()
{
    Suit asset = Application::getInstance().getGame()->getRules()->getAsset();
    vector<Card> trickCards = Application::getInstance().getGame()->getCurrentTrick().getCards();

    // all cards are playable if the player is first to play
    if (trickCards.size() == 0) {
        return _cards;
    }

    Suit demandedSuit = trickCards.front().getSuit();

    // first, check whether the player has the asked suit in his hand
    if (demandedSuit != asset && cardsForSuit(demandedSuit).size() != 0) {
        return cardsForSuit(demandedSuit);
    }

    // if not, he can still play whatever he wants if his friend is the current master of the trick
    else if (demandedSuit != asset && isFriendMaster()) {
        return getCards();
    }

    // if his friend isn't, and he has assets, he has to play them, and they must be bigger than assets already played
    else if (cardsForSuit(asset).size() != 0) {
        std::vector<Card> playableCards;
        std::vector<Card> assetsInTrick = Application::getInstance().getGame()->getRules()->cardsForSuit(trickCards, asset);

        if (assetsInTrick.size() == 0) {
            return cardsForSuit(asset);
        }

        Card max = assetsInTrick[0];
        for (auto card : assetsInTrick) {
            if (card.isGreaterThan(max, demandedSuit)) {
                max = card;
            }
        }
        for (auto card : cardsForSuit(asset)) {
            if (card.isGreaterThan(max, demandedSuit)) {
                playableCards.push_back(card);
            }
        }
        return (playableCards.size() > 0 ? playableCards : cardsForSuit(asset));
    }

    // if the friend isn't master and he has no cards of the asked suit nor bigger assets, he can play whatever he wants
    return _cards;
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
