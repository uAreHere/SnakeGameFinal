#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 30;
const int height = 30;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum direction { STOP = 0, Left, Right, Up, Down };
direction dir;

void setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void draw()
{
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	for (int i = 0; i < width+2; i++)
		cout << "%";
	cout << endl;

	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++) 
		{
			if (j == 0)
				cout << "%";
			if (i == y && j == x)
				cout << "B)";
			else if (i == fruitY && j == fruitX)
				cout << "@";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print=true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "%";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "%";
	cout << endl;

	cout << "Score:" << score << endl;
}

void input()
{
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'w':
			dir = Up;
			break;
		case 's':
			dir = Down;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case Left:
		x--;
		break;;
	case Right:
		x++;
		break;
	case Up:
		y--;
		break;
	case Down:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	int game;
	cout << "Welcome to the Snake Game! \n How much fruit can your snake eat? It's all up to you! \n The more you eat the bigger your snake gets but be careful not to wrap into your tail \n or move back on yourself or the game is over! Use the W A S D keys to change direction and if possible, \n make your console window bigger to make the flicker a bit more tolerable. ";
	cout << "Are you ready to play? Enter any character to begin" << endl;
	cin >> game;
	
	
		setup();
		while (!gameOver)
		{
			draw();
			input();
			logic();
			Sleep(10);
		}
}
	
