#include <SFML/Graphics.hpp>
#include <iostream>
#include "Card.h"
#include "NetworkManager.h"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Cheukoin !");
	Card card = Card::Card();

    NetworkManager::createLobby();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Color(63, 150, 61, 255));
		window.draw(card.sprite);
		window.display();
	}

	return 0;
}