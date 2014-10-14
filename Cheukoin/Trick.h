#ifndef __Cheukoin_Trick__
#define __Cheukoin_Trick__

#include "Card.h"
#include "Constants.h"

class Trick {
public:
    Trick(int number);
    ~Trick();

    int getNumber();
    void setNumber(int number);

    void addCard(Card const& Card);

#warning TODO: change name to getCards
    std::vector<Card> getComposition();

private:
#warning TODO: see if we can get rid of this
    int _number;
    std::vector<Card> _composition;
};

#endif
