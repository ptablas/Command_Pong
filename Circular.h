#pragma once

#include <SDL.h>

struct Circle
{
	int centreX;
	int centreY;
	int radius;

	Circle() = default;

	Circle(int centreX, int centreY, int radius)
		: centreX(centreX), centreY(centreY), radius(radius)
	{
	}

	bool operator==(const Circle& other) const
	{
		return false;
	}
};

void SDL_Circle_Line(SDL_Renderer* renderer, Circle& circle)
{
	int centreX = circle.centreX;
	int centreY = circle.centreY;
	int radius = circle.radius;

	int x = 0;
	int y = radius;
	int m = 2 - 2 * radius;

	int f = 3; // 1 = smooth

	while (x <= y)
	{

		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);


		if (m > 0)
		{
			y--;
			m = m + 4 * (x - y) + 10;
		}
		else
			m = m + 4 * x + 6;
		x++;
	}
}

void SDL_Circle_Line(SDL_Renderer* renderer, Circle& circle, int fact1, int fact2)
{
	int centreX = circle.centreX;
	int centreY = circle.centreY;
	int radius = circle.radius;

	int x = 0;
	int y = radius;
	int m = 2 - 2 * radius;

	int f = 3; // 1 = smooth

	while (x <= y)
	{

		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);


		if (m > 0)
		{
			y -= fact1;
			m = m + 4 * (x - y) + 10;
		}
		else
		m = m + 4 * x + 6;
		x += fact2;
	}
}

void SDL_Circle_Morph(SDL_Renderer* renderer, Circle& circle, int lim_fact1, int lim_fact2)
{
	int centreX = circle.centreX;
	int centreY = circle.centreY;
	int radius = circle.radius;

	bool fact1_dir = 1;	// 1 = up
	bool fact2_dir = 1; // 0 = down

	int inc_fact1 = 1;
	int inc_fact2 = 1;

	int x = 0;
	int y = radius;
	int m = 2 - 2 * radius;

	int f = 3; // 1 = smooth

	while (x <= y)
	{

		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);


		if (m > 0)
		{
			y -= inc_fact1;
			m = m + 4 * (x - y) + 10;
		}
		else
			m = m + 4 * x + 6;
		x += inc_fact2;
	}

	if (radius == y)
		fact1_dir = 1;
	if (y == lim_fact1)
		fact1_dir = 0;

	if (fact1_dir)
		inc_fact1++;
	else
		inc_fact1--;

	if (x == 0)
		fact2_dir = 1;
	if (x == lim_fact1)
		fact2_dir = 0;

	if (fact2_dir)
		inc_fact2++;
	else
		inc_fact2--;
}

void SDL_Circle_Filled(SDL_Renderer* renderer, Circle& circle)
{
	int centreX = circle.centreX;
	int centreY = circle.centreY;
	int radius = circle.radius;

	for (int x = -radius; x < radius; x++)
	{
		int height = (int)std::sqrt(radius * radius - x * x);

		for (int y = -height; y < height; y++)
			SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
	}
}