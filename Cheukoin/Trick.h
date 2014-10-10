#ifndef __Cheukoin_Trick__
#define __Cheukoin_Trick__

#include <vector>
#include <map>
#include "Card.h"

class Trick {
public:
    Trick();
    Trick(int number);
    ~Trick();
    void setNumber(int number);
    int getNumber();
    void addCard(Card const& Card);
    std::vector<Card> getComposition();
    Card winningCard(Suit const& suit);
    bool isGreater(Card card1, Card card2, Suit suit) const;

private:
    int _number;
    std::vector<Card> _composition;
    std::map<Value, int> _cardValues;
    std::map<Value, int> _cardValuesAsset;
};

#endif