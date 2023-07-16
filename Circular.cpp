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

void Bresenham::Morph(SDL_Renderer* renderer, int strt1, int end1, int strt2, int end2)
{

	if (isFirstCall)
	{
		fact1 = strt1;
		fact2 = strt2;

		if (strt1 > end1)
			dir1 = false;

		if (strt2 > end2)
			dir2 = false;

		//if (strt1 == end1 && strt2 == end2) // if they are both the same it returns 0 + create flag that it should not add anything
			//throw std::runtime_error("If limits are equal, use non-morphing Polyg function instead");

		if (strt1 == end1)
			morph_not1 = true;

		if (strt2 == end2)
			morph_not2 = true;

		isFirstCall = false;
	}

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

	// Update Factors
	if (!morph_not1)
	fact1 += (dir1 ? 1 : -1);

	if (!morph_not2)
	fact2 += (dir2 ? 1 : -1);

	// Check if factors reach limits and change direction
	if (fact1 == strt1 || fact1 == end1)
		dir1 = !dir1;

	if (fact2 == strt2 || fact2 == end2)
		dir2 = !dir2;
	
}

bool Bresenham::isFirstCall = true, Bresenham::dir1 = true, Bresenham::dir2 = true, Bresenham::morph_not1 = false, Bresenham::morph_not2 = false;
int Bresenham::fact1, Bresenham::fact2;
