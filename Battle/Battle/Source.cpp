#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800, 800), "it works!");

	float CurrentFrame = 0;

	Clock clock;

	Image hero_image;
	hero_image.loadFromFile("..\\images\\Logo.png");

	Texture hero_texture;
	hero_texture.loadFromImage(hero_image);

	Sprite hero_sprite;
	hero_sprite.setTexture(hero_texture);
	hero_sprite.setTextureRect(IntRect(0, 100, 100, 100));
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

		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			hero_sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 300, 100, 100));
			hero_sprite.move(-0.1 * time, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			hero_sprite.move(0.1*time, 0); 
			hero_sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 100, 100, 100));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			hero_sprite.move(0, -0.1*time); 
			hero_sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 200, 100, 100));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			hero_sprite.move(0, 0.1*time); 
			hero_sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, 100, 100));
		}

		window.clear();
		window.draw(hero_sprite);
		window.display();
	}
	return 0;
}