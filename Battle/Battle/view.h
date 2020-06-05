#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void getPlayerCordView(float x, float y)
{
	float tempX = x, tempY = y;

	if (x < 320) tempX = 320;
	if (x > 960) tempX = 960;
	if (y < 240) tempY = 240;
	if (y > 554) tempY = 554;

	view.setCenter(tempX, tempY);
}