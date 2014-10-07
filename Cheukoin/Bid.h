#include <string>
#include "Card.h"

class Bid
{
public:
	Bid();
	~Bid();
	Value getValue();
	void setValue(Value value);
	void setSuit(Suit suit);
	Suit getSuit();
	bool isBidValid(Bid previousBid);

private:
	Value _value;
	Suit _suit;
    

};

