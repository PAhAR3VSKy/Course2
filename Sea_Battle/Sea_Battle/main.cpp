#pragma comment(lib, "ws2_32.lib")
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "game.h"
#include "windows.h"
#include <winsock2.h>
#pragma warning(disable: 4996)

using namespace sf; // подключаем пространство имён sf

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
	Battle() {};
	void setX(int);
	void setY(int);
	int getX();
	int getY();
};

Battle::Battle(String F)
{
	file = F;
	image.loadFromFile("..\\images\\" + file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

void Battle::setX(int x) { this->x = x; }
void Battle::setY(int y) { this->y = y; }
int Battle::getX() { return this->x; }
int Battle::getY() { return this->y; }

int clientSend(Battle data)
{

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); //Версия библиотеки
	if (WSAStartup(DLLVersion, &wsaData) != 0) //Загрузка библиотеки
	{
		std::cout << "Error" << std::endl;
		exit(1);
	};
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(11111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) { // Проверка успешности соединения
		std::cout << "Client: failed connect to server \n";
		return 1;
	};
	std::cout << "Connected" << std::endl;

	int sender = 1;
	int x, y;
	send(Connection, (char*)&sender, sizeof(sender), NULL);

	recv(Connection, (char*)&x, sizeof(x), NULL);
	recv(Connection, (char*)&y, sizeof(y), NULL);

	data.setX(x);
	data.setY(y);
	return 0;
}


int main()
{
	srand(time(NULL));
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(1200, 600), "SFML Works!");

	Battle data;

	bool isMove = false;
	bool turn = true;
	float dX = 0;
	float dY = 0;

	setRandShipPlayer(4, 1);	//установка кораблей для игрока в рандомном месте
	setRandShipPlayer(3, 2);
	setRandShipPlayer(2, 3);
	setRandShipPlayer(1, 4);

	setRandShipBot(4, 1);	//установка кораблей для бота в рандомном месте
	setRandShipBot(3, 2);
	setRandShipBot(2, 3);
	setRandShipBot(1, 4);

	Image map_images;
	map_images.loadFromFile("..\\images\\map.png");

	Texture map_texture;
	map_texture.loadFromImage(map_images);

	Sprite map_sprite;	//спрайт карты игрока
	map_sprite.setTexture(map_texture);
	map_sprite.setPosition(0, 0);

	Sprite map_sprite_bot;	//спрайт карты бота
	map_sprite_bot.setTexture(map_texture);
	map_sprite_bot.setPosition(600, 0);

	Battle ship("ship.png");
	Battle ship_rip("ship_rip.png");
	Battle ship_miss("miss.png");
	ship_miss.texture.setSmooth(true);	//сглаживание на спрайте промаха

	ship_miss.sprite.scale(0.5, 0.5);	//уменьшили спрайт промаха

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);	//получение координат мышки
		
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем его

			
		}
		// Установка цвета фона
		window.clear();
		switch (turn)
		{
		case true:
			if (event.type == Event::MouseButtonPressed)//уничтожение кораблей
				if (event.key.code == Mouse::Left)
				{
					if (TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x - 600) / 50) - 1] == '1')
						TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x - 600) / 50) - 1] = 'x';
					turn = false;
					Sleep(100);
				}
			if (event.type == Event::MouseButtonPressed)//промах
				if (event.key.code == Mouse::Left)
				{
					if (TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x - 600) / 50) - 1] == '0')
						TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x - 600) / 50) - 1] = '-';
					turn = false;
					Sleep(100);
				}
			
			break;
		case false:
			int x, y;
			do
			{
				clientSend(data);
				x = data.getX();
				y = data.getY();
			} while (TileMap[x][y] == 'x' || TileMap[x][y] == '-');
			if (TileMap[x][y] == '1')
				TileMap[x][y] = 'x';
			if (TileMap[x][y] == '0')
				TileMap[x][y] = '-';
			turn = true;
			break;
		default:
			break;
		}
		
		// Отрисовка карты
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
				if (TileMap[i][j] == 'x')
				{
					ship_rip.sprite.setTextureRect(IntRect(50, 50, 50, 50));

					ship_rip.sprite.setPosition(j * 50 + 50, i * 50 + 50);
					window.draw(ship_rip.sprite);
				}
				if (TileMap[i][j] == '-')
				{
					ship_miss.sprite.setTextureRect(IntRect(50, 50, 50, 50));

					ship_miss.sprite.setPosition(j * 50 + 63, i * 50 + 63);
					window.draw(ship_miss.sprite);
				}
				////////////////////////////////////////////////////////////////////
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

		

		// Отрисовка окна
		window.display();
	}

	return 0;
}