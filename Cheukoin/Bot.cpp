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
    Card nextCard = chooseCard();
    Player::playCard(nextCard);
}

Card Bot::chooseCard()
{
    return _cards[0];
}

void Bot::guessHands() {}