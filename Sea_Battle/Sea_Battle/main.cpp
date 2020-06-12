#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"

using namespace sf; // ���������� ������������ ��� sf

class Battle
{
private:
	int x, y;
public:
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Battle(String);
};

Battle::Battle(String F)
{
	file = F;
	image.loadFromFile("..\\images\\" + file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(50, 50, 50, 50));
}

int main()
{
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(800, 600), "SFML Works!");

	bool isMove = false;
	float dX = 0;
	float dY = 0;

	setRandShip(4, 1);	//��������� �������� � ��������� �����
	setRandShip(3, 2);
	setRandShip(2, 3);
	setRandShip(1, 4);

	Image map_images;
	map_images.loadFromFile("..\\images\\map.png");

	Texture map_texture;
	map_texture.loadFromImage(map_images);

	Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	map_sprite.setPosition(0, 0);

	Battle ship("ship.png");
	Battle ship_rip("ship_rip.png");

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		
		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				window.close(); // ����� ��������� ���

			
		}
		// ��������� ����� ����
		window.clear();

		if (event.type == Event::MouseButtonPressed)//�������� ������ ��������
			if (event.key.code == Mouse::Left)
			{
				if(TileMap[((int)pos.y / 50) - 1][((int)pos.x / 50) - 1] == '1')
					TileMap[((int)pos.y / 50) - 1][((int)pos.x / 50) - 1] = 'x';
			}
		// ��������� ��������
		window.draw(map_sprite);
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '1')
				{
					ship.sprite.setTextureRect(IntRect(50, 50, 50, 50));

					ship.sprite.setPosition(j * 50 + 50, i * 50 + 50);
					window.draw(ship.sprite);
				}
				if (TileMap[i][j] == 'x')
				{
					ship_rip.sprite.setTextureRect(IntRect(50, 50, 50, 50));

					ship_rip.sprite.setPosition(j * 50 + 50, i * 50 + 50);
					window.draw(ship_rip.sprite);
				}
			}
		}

		if (Mouse::isButtonPressed(sf::Mouse::Left))
		{

		}

		// ��������� ����
		window.display();
	}

	return 0;
}