#include <SFML/Graphics.hpp>

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
};

Battle::Battle(String F)
{
	file = F;
	image.loadFromFile("..\\images\\" + file);

}

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 600), "SFML Works!");

	Image map_images;
	map_images.loadFromFile("..\\images\\map.png");

	Texture map_texture;
	map_texture.loadFromImage(map_images);

	Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	map_sprite.setPosition(0, 0);

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
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

		

		// Отрисовка круга
		window.draw(map_sprite);

		// Отрисовка окна
		window.display();
	}

	return 0;
}