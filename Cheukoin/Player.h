#ifndef __Cheukoin_Player__
#define __Cheukoin_Player__

#include <string>

#include "Bid.h"
#include "Card.h"
#include "Application.h"
#include "Trick.h"
#include "Constants.h"

class Bot;

enum Position {
    Left,
    Right,
    Top,
    Bottom
};

class Player {
public:
    Player(std::string name, Position position = Top);
    Player();
    virtual ~Player();

    Bid makeBid(int amount, Suit const& asset);

    virtual void play(){};
    void sortCards();
    std::string getName() const;
    void setName(std::string name);

    Card getPlayedCard();

    Bid getBid() const;
    void setBid(Bid& bid);

    void makeDealer();
    void changeDealer();
    bool isDealer();
    void playByClick();

    Position getPosition() const;
    void setPosition(Position position);

    // Card management
    virtual void initialize();
    void update(sf::Time elapsed);
    void addCard(Card card);
    void playCard(Card const& card);
    std::vector<Card> getCards() const;
    sf::IntRect getGlobalBounds();
    void drawCards() const;
    std::vector<Card> cardsForSuit(Suit suit);

    static std::vector<std::string> PositionNames;
    Card chooseCard();

    bool isFriendMaster();
    std::vector<Card> getPlayableCards(Trick tricks);

protected:
    std::string _name;
    Bid _bid;
    bool _dealer;
    Card _playedCard;
    std::vector<Card> _cards;
    Position _position;

    void _moveCardToCenter(Card& card);
};

bool operator==(Player const& a, Player const& b);
bool operator!=(Player const& a, Player const& b);

std::ostream& operator<<(std::ostream& os, const Player& player);

#endif