
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Cheukoin !");
	sf::Texture textureBack;
	if (!textureBack.loadFromFile("ressource/cardBack.png")) {
		// handle texture not loaded
		cout << "Texture file fucking not loaded";
	}
	sf::Sprite rectangle;
	rectangle.setTextureRect(sf::IntRect(0, 0, 342, 480));
	rectangle.setTexture(textureBack);
	rectangle.setScale(sf::Vector2f(0.3, 0.3));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Color(63, 150, 61, 255));
		window.draw(rectangle);
		window.display();
	}

	return 0;
}