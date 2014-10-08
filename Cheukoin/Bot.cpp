#include "Bot.h"

using namespace std;

Bot::Bot()
{
}

Bot::~Bot()
{
}

void Bot::play()
{
    Card nextCard = Bot::chooseCard();
    Player::playCard(nextCard);
}

Card Bot::chooseCard()
{
    return _hand.getCards()[0];
}
