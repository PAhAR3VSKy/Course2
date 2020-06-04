#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Player
{
public:
	float x, y, w, h, dx, dy, speed;
	int dir;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String, float, float, float, float);
	void update(float);
};

Player::Player(String F, float X, float Y, float W, float H)
{
	dx = 0; dy = 0; speed = 0; dir = 0;
	file = F;
	w = W; h = H;
	image.loadFromFile("..\\images\\" + file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X; y = Y;
	sprite.setTextureRect(IntRect(0, 0, w, h));
}

void Player::update(float time)
{
	switch (dir)
	{
	case 0:
		dx = speed; dy = 0;
		break;
	case 1:
		dx = -speed; dy = 0;
		break;
	case 2:
		dx = 0; dy = speed;
		break;
	case 3:
		dx = 0; dy = -speed;
		break;
	}

	x += dx * time;
	y += dy * time;

	speed = 0;
	sprite.setPosition(x, y);
}

int main()
{
	RenderWindow window(VideoMode(800, 800), "it works!");

	float CurrentFrame = 0;
	Player p("Logo.png", 0, 300, 100, 100);

	Clock clock;

	

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
			p.dir = 1;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			p.sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 300, 100, 100));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			p.dir = 0; 
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			p.sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 100, 100, 100));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			p.dir = 3;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			p.sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 200, 100, 100));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			p.dir = 2;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			p.sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, 100, 100));
		}

		p.update(time);

		window.clear();
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}