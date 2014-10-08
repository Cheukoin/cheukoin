#include <string>
#include "Card.h"

class Bid
{
public:
	Bid();
	~Bid();
	int getAmount();
	void setAmount(int amount);
	void setSuit(Suit suit);
	Suit getSuit();
	bool isBidValid(Bid previousBid);

private:
	int _amount;
	Suit _suit;
    

};

