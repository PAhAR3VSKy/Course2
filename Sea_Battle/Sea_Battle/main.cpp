#include <SFML/Graphics.hpp>

using namespace sf; // подключаем пространство имён sf

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 600), "SFML Works!");

	Image map_images;
	map_images.loadFromFile("..\\images\\map.jpg");

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

		map_sprite.setScale(0.5, 0.5);

		// Отрисовка круга
		window.draw(map_sprite);

		// Отрисовка окна
		window.display();
	}

	return 0;
}