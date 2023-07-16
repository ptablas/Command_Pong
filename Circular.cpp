#include "Circular.h"
#include "iostream"

void Circle::Fill(SDL_Renderer* renderer)
{
	for (int x = -mRadius; x < mRadius; x++)
	{
		int height = (int)std::sqrt(mRadius * mRadius - x * x);

		for (int y = -height; y < height; y++)
			SDL_RenderDrawPoint(renderer, mCentreX + x, mCentreY + y);
	}
}

void Bresenham::mOctan_Render(SDL_Renderer* renderer)
{
	//  Each of the following renders an octant of the circle
	SDL_RenderDrawPoint(renderer, mCentreX + x, mCentreY - y);
	SDL_RenderDrawPoint(renderer, mCentreX + x, mCentreY + y);
	SDL_RenderDrawPoint(renderer, mCentreX - x, mCentreY - y);
	SDL_RenderDrawPoint(renderer, mCentreX - x, mCentreY + y);
	SDL_RenderDrawPoint(renderer, mCentreX + y, mCentreY - x);
	SDL_RenderDrawPoint(renderer, mCentreX + y, mCentreY + x);
	SDL_RenderDrawPoint(renderer, mCentreX - y, mCentreY - x);
	SDL_RenderDrawPoint(renderer, mCentreX - y, mCentreY + x);
}

void Bresenham::Perim(SDL_Renderer* renderer)
{
	while (x <= y)
	{
		mOctan_Render(renderer);

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

void Bresenham::Polyg(SDL_Renderer* renderer, int fact1, int fact2)
{
	while (x <= y)
	{
		mOctan_Render(renderer);

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

void Bresenham::Morph(SDL_Renderer* renderer, int min_fact1, int min_fact2, int lim_fact1, int lim_fact2)
{

	if (isFirstCall)
	{
		inc_fact1 = min_fact1;
		inc_fact2 = min_fact2;
		isFirstCall = false;
	}

	while (x <= y)
	{
		mOctan_Render(renderer);

		if (m > 0)
		{
			y -= inc_fact1;
			m = m + 4 * (x - y) + 10;
		}
		else
			m = m + 4 * x + 6;
		x += inc_fact2;
	}

	inc_fact1 += (fact1_dir ? 1 : -1);
	inc_fact2 += (fact2_dir ? 1 : -1);

	// Check if inc_fact1 reaches the limits and adjust the direction accordingly
	if (inc_fact1 == min_fact1 || inc_fact1 == lim_fact1)
		fact1_dir = !fact1_dir;

	// Update inc_fact1 based on the direction
	

	// Check if inc_fact2 reaches the limits and adjust the direction accordingly
	if (inc_fact2 == min_fact2 || inc_fact2 == lim_fact2)
		fact2_dir = !fact2_dir;

	// Update inc_fact2 based on the direction
	
}

bool Bresenham::isFirstCall = true;
int Bresenham::inc_fact1 = 1;
int Bresenham::inc_fact2 = 1;
