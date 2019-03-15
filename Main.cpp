#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "rlutil.h"

bool HelloMessage()
{
	int b;
	rlutil::setColor(rlutil::LIGHTCYAN);
	std::cout << "                                                                     " << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "|   Enter 1 if you want to die by touching the walls, 0 otherwise   |" << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "                                                                     " << std::endl;

	std::cin >> b;
	if (b == 1)
		return true;
	else
		return false;
}

void ByeMessage(const int a)
{
	rlutil::saveDefaultColor();
	rlutil::setColor(rlutil::LIGHTCYAN);
	std::cout << "                                      " << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "|            Game Over!!!            |" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "                                      " << std::endl;
	std::cout << "        Your final score is: " << a << std::endl;
	std::cin.get();
}

bool GameOver;
bool walldeath = HelloMessage(); // This should be set as false if you want it to have the "PacMan" effect, like (PBC)
const int width = 20;
const int height = 20;
int x, y, foodx, foody, score;
int tailx[100], taily[100];
int ntail;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void SetUp()
{
	GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodx = rand() % width;
	foody = rand() % height;
	score = 0;
}

void Draw()
{
	const char* wall = "#";
	system("cls");
	for (int i = 0; i < width+2; i++)
		std::cout << wall;
	std::cout << std::endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{ 
				rlutil::setColor(rlutil::LIGHTCYAN);
				std::cout << wall;
			}

			if (i == y && j == x)
			{
				rlutil::setColor(rlutil::LIGHTRED);
				std::cout << "O";
			}

			else if (i == foody && j == foodx)
			{ 
				rlutil::setColor(rlutil::LIGHTGREEN);
				std::cout << "$";
			}

			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					
					if (tailx[k] == j && taily[k] == i)
					{
						rlutil::setColor(rlutil::LIGHTRED);
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
					std::cout << " ";
			}

			if (j == width - 1)
			{
				rlutil::setColor(rlutil::LIGHTCYAN);
				std::cout << wall;
			}

		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width+2; i++)
		std::cout << wall;
	std::cout << std::endl;
	std::cout << " " << std::endl;
	std::cout << "Score = " << score << std::endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			GameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < ntail; i++)
	{
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (walldeath)
	{
		if (x >= width || x < 0 || y >= height || y < 0)
		{
			GameOver = true;
		}
	}

	else
	{
		if (x >= width) x = 0; else if (x < 0) x = width - 1;
		if (y >= width) y = 0; else if (y < 0) y = width - 1;
	}

	for (int i = 0; i < ntail; i++)
	{
		if (tailx[i] == x && taily[i] == y)
		{
			GameOver = true;
		}
	}

	if (x == foodx && y == foody)
	{
		score += 1;
		foodx = rand() % width;
		foody = rand() % height;
		ntail += 1;
	}
}

int main()
{
	SetUp();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(20);

	}
	system("cls");
	ByeMessage(score);
	std::cin.get();
}