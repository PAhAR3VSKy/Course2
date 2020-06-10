#include <SFML/Graphics.hpp>

using namespace sf; // ���������� ������������ ��� sf

int main()
{
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(800, 600), "SFML Works!");

	Image map_images;
	map_images.loadFromFile("..\\images\\map.jpg");

	Texture map_texture;
	map_texture.loadFromImage(map_images);

	Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	map_sprite.setPosition(0, 0);

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
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

		map_sprite.setScale(0.5, 0.5);

		// ��������� �����
		window.draw(map_sprite);

		// ��������� ����
		window.display();
	}

	return 0;
}