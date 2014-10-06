#pragma once
#include <vector>
#include "Card.h"

class Hand
{
public:
	Hand();
	~Hand();
	void removeCard(); // retrait carte � la main lors du jeu
	void addCard(Card card);// ajout lors de la donne
	std::vector <int, string> getCards(); // donne la composition de la main
	bool ishandValid(); // vrai si 8 cartes distinctes et non pr�sentes dans les autres mains

private:
	std::vector <int, string> m_cards; // pas compris ce qu'est List<Card>

};

