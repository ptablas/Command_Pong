#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };
unsigned int illusionTime = 25;
HANDLE hOut;

class cBall
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;

public:
	cBall(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX; y = posY;
		direction = STOP;
	}

	void Reset()
	{
		x = originalX; y = originalY;
		direction = STOP;
	}

	void changeDirection(eDir d)
	{
		direction = d;
	}

	void randomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
	}

	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }

	void move()
	{
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		}
	}

	friend std::ostream& operator << (std::ostream& o, cBall c)
	{
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]" << std::endl;
		return o;
	}

};

class cPaddle
{
private:
	int x, y;
	int originalX = 0, originalY = 0;
public:
	cPaddle()
	{
		x = y = 0;
	}

	cPaddle(int posX, int posY) : cPaddle()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}

	inline void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }


	friend std::ostream& operator << (std::ostream& o, cPaddle c)
	{
		o << "Paddle [" << c.x << "," << c.y << "]" << std::endl;
		return o;
	}

};

class cGameManager
{
private:
	int width, height;
	int score1, score2;
	int up1, down1, up2, down2, quit_key;
	bool quit;
	cBall* ball;
	cPaddle* player1;
	cPaddle* player2;

public:
	cGameManager(int w, int h)
	{
		srand((unsigned int)time(NULL));
		quit = false;
		quit_key = 0x51;
		up1 = 0x57; up2 = 0x49;
		down1 = 0x53; down2 = 0x4B;
		score1 = score2 = 0;
		width = w; height = h;
		ball = new cBall(w / 2, h / 2);
		player1 = new cPaddle(1, h / 2 - 3);
		player2 = new cPaddle(w - 2, h / 2 - 3);
	}

	~cGameManager()
	{
		delete ball, player1, player2;
	}

	void ScoreUp(cPaddle* player)
	{
		if (player == player1)
		{
			score1++;
		}

		else if (player == player2)
		{
			score2++;
		}

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	void Paint_ASCII(int Ascii)
	{
		static uint8_t c_counter;
		switch (Ascii)
		{
		case 'wall' :
			{
			c_counter++;
			SetConsoleTextAttribute(hOut, c_counter % 64);
			std::cout << "\xB2";
			break;
			}
		case 'pad' :
			{
			SetConsoleTextAttribute(hOut, 500);
			std::cout << "\xDB";
			break;
			}
		case 'ball':
			{
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			std::cout << "O";
			break;
			}
		case 'back':
			{
			SetConsoleTextAttribute(hOut, 0);
			std::cout << " ";
			break;
			}
		case 'scor':
			{
			SetConsoleTextAttribute(hOut, 5);
			std::cout << "Score 1: " << score1 << "		      " << " Score 2: " << score2 << std::endl;
			break;
			}
		}
		
	}

	void Draw()
	{
		//system("cls");

		for (int i = 0; i < width + 2; i++)
			Paint_ASCII('wall');

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();



				if (j == 0)
					Paint_ASCII('wall');

				if (ballx == j && bally == i)
					Paint_ASCII('ball');

				else if (player1x == j && player1y == i)
					Paint_ASCII('pad'); //player 1

				else if (player2x == j && player2y == i)
					Paint_ASCII('pad'); //player2

				else if (player1x == j && player1y + 1 == i)
					Paint_ASCII('pad'); //player 1
				else if (player1x == j && player1y + 2 == i)
					Paint_ASCII('pad'); //player 1
				else if (player1x == j && player1y + 3 == i)
					Paint_ASCII('pad'); //player 1

				else if (player2x == j && player2y + 1 == i)
					Paint_ASCII('pad'); //player 2
				else if (player2x == j && player2y + 2 == i)
					Paint_ASCII('pad'); //player 2
				else if (player2x == j && player2y + 3 == i)
					Paint_ASCII('pad'); //player 2


				else
					Paint_ASCII('back');


				if (j == width - 1)
					Paint_ASCII('wall');
			}
			std::cout << std::endl;
		}

		for (int i = 0; i < width + 2; i++)
		Paint_ASCII('wall');
		std::cout << std::endl;

		Paint_ASCII('scor');
	}

	void clearScreen() // Use Direct implementation of "cls" to clear screen without flickering!
	{
		COORD Position;

		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		Position.X = 0;
		Position.Y = 0;
		SetConsoleCursorPosition(hOut, Position);
	}

	bool keydown(int key)
	{
		return (GetAsyncKeyState(key) & 0x8000) != 0;
	}

	void Input()
	{
		ball->move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

			if (keydown(up1))
				if (player1y > 0)
					player1->moveUp();
			if (keydown(up2))
				if (player2y > 0)
					player2->moveUp();

			if (keydown(down1))
				if (player1y + 4 < height)
					player1->moveDown();
			if (keydown(down2))
				if (player2y + 4 < height)
					player2->moveDown();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (keydown(quit_key))
				quit = true;
				illusionTime = 25;

	}

	void Logic()
	{
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();


		//left paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));

		// right paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		//bottom wall
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		//top wall
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);


		//right wall
		if (ballx == width - 1)
			ScoreUp(player1);

		//left wall
		if (ballx == 0)
			ScoreUp(player2);

	}

	void Run()
	{
		int count = 0;

		while (!quit)
		{
			Draw();
			Input();
			Logic();
			Sleep(illusionTime);
			clearScreen();

			if (illusionTime > 0)
			{
				count++;

				if (count > 25)
				{
					illusionTime--;
					count = 0;
				}
			}
		}
	}
};


int main()
{
	cGameManager c(40, 20);


	c.Run();



	return 0;
}