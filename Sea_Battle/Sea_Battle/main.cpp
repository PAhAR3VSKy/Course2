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
}

int main()
{
	srand(time(NULL));
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(1200, 600), "SFML Works!");

	bool isMove = false;
	float dX = 0;
	float dY = 0;

	setRandShipPlayer(4, 1);	//��������� �������� � ��������� �����
	setRandShipPlayer(3, 2);
	setRandShipPlayer(2, 3);
	setRandShipPlayer(1, 4);

	setRandShipBot(4, 1);	//��������� �������� � ��������� �����
	setRandShipBot(3, 2);
	setRandShipBot(2, 3);
	setRandShipBot(1, 4);

	Image map_images;
	map_images.loadFromFile("..\\images\\map.png");

	Texture map_texture;
	map_texture.loadFromImage(map_images);

	Sprite map_sprite;	//������ ����� ������
	map_sprite.setTexture(map_texture);
	map_sprite.setPosition(0, 0);

	Sprite map_sprite_bot;	//������ ����� ����
	map_sprite_bot.setTexture(map_texture);
	map_sprite_bot.setPosition(600, 0);

	Battle ship("ship.png");
	Battle ship_rip("ship_rip.png");
	Battle ship_miss("miss.png");
	ship_miss.texture.setSmooth(true);	//����������� �� ������� �������

	ship_miss.sprite.scale(0.5, 0.5);	//��������� ������ �������

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);	//��������� ��������� �����
		
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

		if (event.type == Event::MouseButtonPressed)//����������� ��������
			if (event.key.code == Mouse::Left)
			{
				if(TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x-600) / 50) - 1] == '1')
					TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x-600) / 50)  - 1] = 'x';
			}
		if (event.type == Event::MouseButtonPressed)//������
			if (event.key.code == Mouse::Left)
			{
				if (TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x-600) / 50) - 1] == '0')
					TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x-600) / 50) - 1] = '-';
			}
		// ��������� �����
		window.draw(map_sprite);
		window.draw(map_sprite_bot);
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
				if (TileMapBot[i][j] == 'x')
				{
					ship_rip.sprite.setTextureRect(IntRect(50, 50, 50, 50));

					ship_rip.sprite.setPosition(j * 50 + 650, i * 50 + 50);
					window.draw(ship_rip.sprite);
				}
				if (TileMapBot[i][j] == '-')
				{
					ship_miss.sprite.setTextureRect(IntRect(50, 50, 50, 50));

					ship_miss.sprite.setPosition(j * 50 + 663, i * 50 + 63);
					window.draw(ship_miss.sprite);
				}
			}
		}

		

		// ��������� ����
		window.display();
	}

	return 0;
}