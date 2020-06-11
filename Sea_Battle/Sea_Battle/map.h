#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int HEIGHT_MAP = 10;
const int WIDTH_MAP = 10;

String TileMap[HEIGHT_MAP] = {
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000"
};

void setRandShip(int sizeShip, int numShips)
{
	srand(time(NULL));
	int x, y;
	int dir = 0;
	int countShip = 0;
	int countTact = 0;
	while (countShip < numShips)
	{
		countTact++;

		if (countTact > 1000)
			break;

		x = rand() % 10;
		y = rand() % 10;

		int temp_x = x;
		int temp_y = y;

		dir = rand() % 4;

		bool settings_is_possible = 1;

		for (int i = 0; i < sizeShip; i++)
		{
			if (x <= 0 || y <= 0 || x >= 10 || y >= 10)
			{
				settings_is_possible = 0;
				break;
			}

			if (TileMap[x    ][y    ] == '1' ||
				TileMap[x    ][y + 1] == '1' ||
				TileMap[x    ][y - 1] == '1' ||
				TileMap[x + 1][y    ] == '1' ||
				TileMap[x + 1][y + 1] == '1' ||
				TileMap[x + 1][y - 1] == '1' ||
				TileMap[x - 1][y    ] == '1' ||
				TileMap[x - 1][y + 1] == '1' ||
				TileMap[x - 1][y - 1] == '1')
			{
				settings_is_possible = 0;
				break;
			}

			switch (dir)
			{
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}

		if (settings_is_possible == 1)
		{
			x = temp_x;
			y = temp_y;
			for (int i = 0; i < sizeShip; i++)
			{
				TileMap[x][y] = '1';
				switch (dir)
				{
				case 0:
					x++;
					break;
				case 1:
					y++;
					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
				default:
					break;
				}
			}
			countShip++;
		}
	}
}

