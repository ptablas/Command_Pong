#pragma once

#include <SDL.h>

class Circle
{
public:

	Circle(int mCentreX, int mCentreY, int mRadius);

	// other inherited class
	void Fill(SDL_Renderer* renderer);

protected:
	int mCentreX, mCentreY, mRadius;
};



class Bresenham : Circle // Circle perimeter drawing
{
public:

	Bresenham(int mCentreX, int mCentreY, int mRadius);

	void Perim(SDL_Renderer* renderer);
	void Polyg(SDL_Renderer* renderer, int fact1, int fact2);
	void Morph(SDL_Renderer* renderer, int lim1, int lim2);

private:
	int x = 0;
	int y = mRadius;
	int m = 2 - 2 * mRadius;

	void mOctan_Render(SDL_Renderer* renderer);
};

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

void Bresenham::Morph(SDL_Renderer* renderer, int lim_fact1, int lim_fact2)
{
	bool fact1_dir = true;	// 1 = up
	bool fact2_dir = true;   // 0 = down

	static int inc_fact1 = 1; // this should be defined outside
	static int inc_fact2 = 1;

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

	if (inc_fact1 == 1)
		fact1_dir = true;
	if (inc_fact1 == lim_fact1)
		fact1_dir = false;

	fact1_dir ? inc_fact1++ : inc_fact1--;

	if (inc_fact2 == 1)
		fact2_dir = true;
	if (inc_fact2 == lim_fact2)	
		fact2_dir = false;

	fact2_dir ? inc_fact2++ : inc_fact2--;
}

void Circle::Fill(SDL_Renderer* renderer)
{
	for (int x = -mRadius; x < mRadius; x++)
	{
		int height = (int)std::sqrt(mRadius * mRadius - x * x);

		for (int y = -height; y < height; y++)
			SDL_RenderDrawPoint(renderer, mCentreX + x, mCentreY + y);
	}
}

// THIS NEEDS TO BE A PROPER CLASS