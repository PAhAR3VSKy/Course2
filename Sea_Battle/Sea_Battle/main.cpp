#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "map.h"
#include "windows.h"


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
Battle Client(Battle data)
{
	IpAddress ip = IpAddress::getLocalAddress();
	TcpSocket socket;
	std::size_t received;
	int x;
	int y;
	int shoot = 1;
	socket.connect(ip, 2000);

	socket.send((char*)&shoot, sizeof(shoot));

	socket.receive((char*)&x, sizeof(x), received);
	socket.receive((char*)&y, sizeof(x), received);
	data.setX(x);
	data.setY(y);
	return data;
}
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

void menu(RenderWindow& window)
{
	Texture newGameTexture, exitGameTexture, aboutTexture, textureBackground;
	newGameTexture.loadFromFile("..\\images\\new_game.png");
	aboutTexture.loadFromFile("..\\images\\about_game.png");
	exitGameTexture.loadFromFile("..\\images\\exit_game.png");
	textureBackground.loadFromFile("..\\images\\background.jpg");
	Sprite	menuNewGame(newGameTexture),
			menuExitGame(exitGameTexture),
			menuAbout(aboutTexture),
			menuBackground(textureBackground);

	menuNewGame.scale(0.3, 0.3);
	menuExitGame.scale(0.3, 0.3);
	menuAbout.scale(0.3, 0.3);
	menuBackground.scale(0.23, 0.28);

	bool isMenu = true;
	int menuNum = 0;
	menuNewGame.setPosition(100, 30);
	menuExitGame.setPosition(100, 90);
	menuAbout.setPosition(100, 300);
	menuBackground.setPosition(345, 0);

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text text("", font, 20);

	while (isMenu)
	{
		menuNewGame.setColor(Color::White);
		menuExitGame.setColor(Color::White);
		menuAbout.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 150, 50).contains(Mouse::getPosition(window))) { menuNewGame.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 300, 300, 150).contains(Mouse::getPosition(window))) { menuAbout.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 90, 150, 50).contains(Mouse::getPosition(window))) { menuExitGame.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			

			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2)
			{ 
				text.setString("Игра морской бой.\n"
					"Создана студентами Гаськовым Николаем и Захаровым Богданом, группы АВТ - 813, НГТУ.\n"
					"Правила игры:\n"
					"-Если выстрел пришёлся в клетку, не занятую ни одним кораблём противника,\n"
					"то  стрелявший игрок ставит на чужом квадрате в этом месте точку.\n"
					"Право хода переходит к сопернику.\n"
					"-Если выстрел пришёлся в клетку, где находится многопалубный корабль\n"
					"(размером больше чем 1 клетка),\n"
					"то стрелявший игрок ставит на чужом поле в эту клетку красный квадратик.\n"
					"Стрелявший игрок получает право на ещё один выстрел.\n"
					"-Если выстрел пришёлся в клетку, где находится однотрубный корабль,\n"
					"или последнюю непоражённую клетку многопалубного корабля,\n"
					"то  стрелявший игрок получает право на ещё один выстрел.\n"
					"\nЧтобы вернуться назад нажмите Esc =)\n");
				text.setPosition(360, 100);
				window.draw(text);
				window.draw(menuAbout); 
				window.display(); 				
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			if (menuNum == 3) { window.close(); isMenu = false; }
		}
		window.draw(menuBackground);
		window.draw(menuNewGame);
		window.draw(menuAbout);
		window.draw(menuExitGame);

		window.display();
	}
}

int main()
{
	int count_ships_player = 20;
	int count_ships_bot = 20;
	srand(time(NULL));
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(1200, 600), "Sea battle");
	menu(window);
	Battle data;
	bool isMove = false;
	bool turn = true;
	float dX = 0;
	float dY = 0;

	setRandShipPlayer(4, 1);	//установка кораблей для игрока в рандомном месте
	setRandShipPlayer(3, 2);
	setRandShipPlayer(2, 3);
	setRandShipPlayer(1, 4);

	setRandShipBot(4, 1);		//установка кораблей для бота в рандомном месте
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
	Battle win("win.jpg");
	Battle lose("lose.jpg");
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
		if (count_ships_bot == 19)
		{
			count_ships_bot = 20;
			Sleep(1000);
			newGameMap();
			setRandShipPlayer(4, 1);	//установка кораблей для игрока в рандомном месте
			setRandShipPlayer(3, 2);
			setRandShipPlayer(2, 3);
			setRandShipPlayer(1, 4);

			setRandShipBot(4, 1);		//установка кораблей для бота в рандомном месте
			setRandShipBot(3, 2);
			setRandShipBot(2, 3);
			setRandShipBot(1, 4);

			win.sprite.setPosition(350, 0);
			window.draw(win.sprite);
			window.display();
			Sleep(2500);

			menu(window);
			
		}
		else if (count_ships_player == 19)
		{
			count_ships_player = 20;

			Sleep(1000);
			newGameMap();
			setRandShipPlayer(4, 1);	//установка кораблей для игрока в рандомном месте
			setRandShipPlayer(3, 2);
			setRandShipPlayer(2, 3);
			setRandShipPlayer(1, 4);

			setRandShipBot(4, 1);		//установка кораблей для бота в рандомном месте
			setRandShipBot(3, 2);
			setRandShipBot(2, 3);
			setRandShipBot(1, 4);

			lose.sprite.setPosition(260, 0);
			window.draw(lose.sprite);
			window.display();
			Sleep(2500);
			
			menu(window);
		}
		switch (turn)
		{
		case true:
			if (event.type == Event::MouseButtonPressed)//уничтожение кораблей
				if (event.key.code == Mouse::Left)
				{
					if (pos.y > 550 || pos.y < 50 || pos.x < 650 || pos.x > 1150)
						break;
					if (TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x - 600) / 50) - 1] == '1')
					{
						TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x - 600) / 50) - 1] = 'x';
						count_ships_bot--;
					}
					
					Sleep(100);
				}
			if (event.type == Event::MouseButtonPressed)//промах
				if (event.key.code == Mouse::Left)
				{
					if (pos.y > 550 || pos.y < 50 || pos.x < 650 || pos.x > 1150)
						break;
					if (TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x - 600) / 50) - 1] == '0')
					{
						TileMapBot[((int)pos.y / 50) - 1][(((int)pos.x - 600) / 50) - 1] = '-';
						turn = false;
					}
					Sleep(100);
				}

			break;
		case false:
			int x, y;
			do{
				data=Client(data);
				x = data.getX();
				y = data.getY();
			} while (TileMap[x][y] == 'x' || TileMap[x][y] == '-');
			if (TileMap[x][y] == '1')
			{
				TileMap[x][y] = 'x';
				count_ships_player--;
				Sleep(500);
			}
			if (TileMap[x][y] == '0')
			{
				TileMap[x][y] = '-';
				turn = true;
				Sleep(500);
			}
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