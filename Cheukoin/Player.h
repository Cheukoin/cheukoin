#ifndef __Cheukoin_Player__
#define __Cheukoin_Player__

#include <string>

#include "Bid.h"
#include "Card.h"
#include "Application.h"
#include "Trick.h"
#include "Constants.h"
#include "BidMaker.h"

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

    virtual void play(){}; // LJ : Je ne vois pas l'intérêt que cette fontion soit virtuelle. Elle n'est pas sensée faire autre chose que
						   // LJ : chooseCard (qui est virtuelle) puis playCard (qui ne n'est pas)

    void sortCards();
    std::string getName() const;
    void setName(std::string name);

    Card getPlayedCard();

    Bid getBid() const;
    void setBid(Bid& bid);
    virtual void chooseBid(){};

    void makeDealer(); // LJ : Pas utilisé
    void changeDealer();
    bool isDealer();
    void playByClick(); // LJ : Fonction pas définie, ni utilisée. À nettoyer

    void setCards(std::vector<Card> cards);
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
    bool hasCard(Card card);

    static std::vector<std::string> PositionNames;
    Card chooseCard();

    bool isFriendMaster();
    std::vector<Card> getPlayableCards();
    float positionBottomy;

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
