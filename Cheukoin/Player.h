#include <string>
#include "Bid.h"
#include "Hand.h"

class Player
{
public:
	Player();
	~Player();
	void playCard(); // retrait carte de la main pour l'insérer dans le trick
	Bid makeBid(int amount, string asset);
	string getName(); 
	void setName(string name);


private:
	string _name;
	Hand _hand;
	Bid _bid;
};

