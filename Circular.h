#pragma once

#include <SDL.h>
#include <cmath>	

class Circle
{
public:

	inline Circle(int CentreX, int CentreY, int Radius)
		: mCentreX(CentreX), mCentreY(CentreY), mRadius(Radius) {}

	void Fill(SDL_Renderer* renderer);

protected:

	int mCentreX = 1, mCentreY = 1, mRadius = 1;

public:

	Circle() = default;

	bool operator==(const Circle& other) const
	{
		return mCentreX == other.mCentreX && mCentreY == other.mCentreY && mRadius == other.mRadius;
	}
};

class Bresenham : Circle // Circle perimeter drawing
{
public:

	inline Bresenham() = default;
	inline Bresenham(int CentreX, int CentreY, int Radius)
		: Circle(CentreX, CentreY, Radius) {}

	void Perim(SDL_Renderer* renderer);
	void Polyg(SDL_Renderer* renderer, int fact1, int fact2);
	void Morph(SDL_Renderer* renderer, int inc_fact1, int inc_fact2, int lim1, int lim2);

private:
	int x = 0;
	int y = mRadius;
	int m = 2 - 2 * mRadius;

	static bool fact1_dir, fact2_dir, isFirstCall;
	static int inc_fact1;
	static int inc_fact2;

	void mOctan_Render(SDL_Renderer* renderer);

public:	

	bool operator==(const Bresenham& other) const
	{
		return false;
	}
};

