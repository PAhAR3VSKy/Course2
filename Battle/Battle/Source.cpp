#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800, 800), "it works!");

	Clock clock;

	Image hero_image;
	hero_image.loadFromFile("..\\images\\Logo.png");

	Texture hero_texture;
	hero_texture.loadFromImage(hero_image);

	Sprite hero_sprite;
	hero_sprite.setTexture(hero_texture);
	hero_sprite.setPosition(0, 0);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) { hero_sprite.move(-0.1*time, 0); }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { hero_sprite.move(0.1*time, 0); }
		if (Keyboard::isKeyPressed(Keyboard::Up)) { hero_sprite.move(0, -0.1*time); }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { hero_sprite.move(0, 0.1*time); }

		if (Mouse::isButtonPressed(Mouse::Left)) { hero_sprite.setColor(Color::Red); }
		if (Mouse::isButtonPressed(Mouse::Right)) { hero_sprite.setColor(Color::Green); }

		window.clear();
		window.draw(hero_sprite);
		window.display();
	}
	return 0;
}