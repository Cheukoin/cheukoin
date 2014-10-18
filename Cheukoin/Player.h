#ifndef __Cheukoin_Player__
#define __Cheukoin_Player__

#include <string>

#include "Bid.h"
#include "Card.h"
#include "Application.h"
#include "Trick.h"
#include "Constants.h"

enum Position {
    Left,
    Right,
    Top,
    Bottom
};

class Player {
public:
    Player();
    ~Player();

    Bid makeBid(int amount, Suit const& asset);

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
    void setCards(std::vector<Card>& cards);
    void playCard(Card const& card);
    std::vector<Card> getCards() const;

    void drawCards() const;

    std::vector<Card> cardsForSuit(Suit suit);

protected:
    std::string _name;
    Bid _bid;
    std::shared_ptr<Game> _game = Application::getInstance().getGame();
    bool _dealer;
    Card _playedCard;
    std::vector<Card> _cards;
    Position _position;
};

bool operator==(Player const& a, Player const& b);
bool operator!=(Player const& a, Player const& b);

#endif