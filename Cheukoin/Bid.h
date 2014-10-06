#include <string>

class Bid
{
public:
	Bid();
	~Bid();
	int getBidValue(); // getter valeur du bid
	void setBidValue(int value); // setter valeur du bid
	void setBidColor(std::string color); //setter couleur du bid
	std::string getBidColor(); // couleur (Sans Att? Tout Att?), représentée par string?
	bool isBidValid(); // supérieur à 80, au précédent, couleur correcte,etc...

private:
	int m_bidValue;
	std::string m_bidColor;

};

