#ifndef __Cheukoin_Trick__
#define __Cheukoin_Trick__

#include "Card.h"
#include "Constants.h"

class Trick {
public:
    Trick();
    ~Trick();

    void addCard(Card const& Card);

    std::vector<Card> getCards();

    void draw();

    int getWinnerCardIndex();

    Card getWinningCard();

private:
    std::vector<Card> _cards;
};

#endif
