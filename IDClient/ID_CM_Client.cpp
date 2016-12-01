#include <iostream>
#include <conio.h>
using namespace std;

#include <IDLib\IDLib.hpp>
using namespace IDSocket;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <crtdbg.h>
#endif

bool gameOver;
const int width = 30;
const int height = 30;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void clearScreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	clearScreen();
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "X";
			}
			else {
				bool isPrint = false;
				for (int x = 0; x < nTail; x++) {
					if (tailX[x] == j && tailY[x] == i)
					{
						cout << "o";
						isPrint = true;
					}
				}
				if (!isPrint) {
					cout << " ";
				}
			}


			if (j == width-1) {
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score:" << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case KEY_LEFT:
			dir = LEFT;
			break;
		case KEY_RIGHT:
			dir = RIGHT;
			break;
		case KEY_UP:
			dir = UP;
			break;
		case KEY_DOWN:
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
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

	//if (x > width || x < 0 || y > height || y < 0) {
	//	gameOver = true;
	//}

	if (x >= width) {
		x = 0;
	}
	else if (x < 0) {
		x = width - 1;
	}

	if (y >= height) {
		y = 0;
	}
	else if (y < 0) {
		y = height - 1;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main() {
#if defined(_DEBUG)
	int dbgFlags = ::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	// bitwise or checks the block integrity on every memory call
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	//don't always remove blocks on delete
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	//check for memory leaks at process terminatio
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(dbgFlags);
#endif // _DEBUG
	cout << "This is my client..." << endl;
	try {
		std::string const ip = "127.0.0.1";
		UDPSocket sock(8080, ip);

		cout << "Press a key to send packet." << endl;
		char ch;
		cin >> ch;

		std::string str = "Hello World!";
		sock.Send(str, ip, 49153);
	}
	catch (SocketError const& e) {
		wcout << e.GetErrorMessage() << endl;
	}

	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(100);
	}

	return 0;
}