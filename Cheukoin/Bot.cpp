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
    playCard(nextCard);
}

Card Bot::chooseCard()
{
    return Card();
}
