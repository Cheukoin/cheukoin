#ifndef __Cheukoin_Trick__
#define __Cheukoin_Trick__

#include "Card.h"
#include "Constants.h"

class Trick {
public:
    Trick(int number);
    ~Trick();
    void setNumber(int number);
    int getNumber();
    std::string getBeginner();
    void setBeginner(std::string);
    void addCard(Card const& Card);
    std::vector<Card> getComposition();
    Card winningCard(Suit const& suit);
    bool isGreater(Card card1, Card card2, Suit suit) const;

private:
    int _number;
    std::string _beginner;
    std::vector<Card> _composition;
};

#endif
