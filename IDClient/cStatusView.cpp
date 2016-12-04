#include "cStatusView.h"
#include "XError.h"
using namespace std;

#define KEY_UP 75
#define KEY_DOWN 77
#define KEY_LEFT 72
#define KEY_RIGHT 80


bool gameOver;
COORD snakeLoc{ 5,1 };
COORD fruitLoc{ 25,25 };
int score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


cStatusView::cStatusView(ThickWrapper& _thick, FileListModel& fl):fileList(fl), thick(_thick)
{
	srand(time(NULL));
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
}

cStatusView::~cStatusView()
{

}

void cStatusView::clearScreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void cStatusView::Setup() {

	gameOver = false;
	dir = STOP;
	randFruit();
	score = 0;
}

void cStatusView::Draw() {

	//Create background play panel
	thick.DrawContainer({ 0, 5 }, (thick.GetWinWidth() * (thick.GetWinHeight() - 9)), BACKGROUND_GREEN);
	clearScreen();
	//Draw Border
	thick.DrawContainer({ 0, 4 }, thick.GetWinWidth(), BACKGROUND_BLUE);
	for (short i = 5; i < thick.GetWinHeight() - 4; i++) {
		thick.DrawContainer({ 0, i }, 1, BACKGROUND_BLUE);
	}
	for (short i = 5; i < thick.GetWinHeight() - 4; i++) {
		thick.DrawContainer({ 69, i }, 1, BACKGROUND_BLUE);
	}
	thick.DrawContainer({ 0, 46 }, thick.GetWinWidth(), BACKGROUND_BLUE);
	
	//Draw snake, snake tail, and food.
	for (short i = 1; i < thick.GetWinWidth(); i++) {
		for (short j = 5; j < thick.GetWinHeight()-4; j++) {
			if (i == snakeLoc.Y && j == snakeLoc.X) {
				thick.DrawContainer({ i, j }, 1, BACKGROUND_RED);
			}
			else if (i == fruitLoc.Y && j == fruitLoc.X) {
				thick.DrawContainer({ i, j }, 1, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
			}
			else {
				bool isPrint = false;
				for (short x = 0; x < nTail; x++) {
					if (tailX[x] == j && tailY[x] == i)
					{
						thick.DrawContainer({ i, j }, 1, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
						isPrint = true;
					}
				}
			}
		}
	}
}

void cStatusView::Input() {
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

void cStatusView::Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = snakeLoc.X;
	tailY[0] = snakeLoc.Y;
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
		snakeLoc.X--;
		break;
	case RIGHT:
		snakeLoc.X++;
		break;
	case UP:
		snakeLoc.Y--;
		break;
	case DOWN:
		snakeLoc.Y++;
		break;
	default:
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0) {
	//	gameOver = true;
	//}

	if (snakeLoc.Y >= thick.GetWinWidth()-1) {
		snakeLoc.Y = 1;
	}
	else if (snakeLoc.Y < 1) {
		snakeLoc.Y = thick.GetWinWidth()-2;
	}

	if (snakeLoc.X >= thick.GetWinHeight()-4) {
		snakeLoc.X = 5;
	}
	else if (snakeLoc.X < 5) {
		snakeLoc.X = thick.GetWinHeight()-5;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == snakeLoc.X && tailY[i] == snakeLoc.Y) {
			gameOver = true;
		}
	}

	if (snakeLoc.X == fruitLoc.X && snakeLoc.Y == fruitLoc.Y) {
		score += 10;
		randFruit();
		nTail++;
	}
}

//Randomize Fruit location
void cStatusView::randFruit() {
	int const MIN_WIDTH = 1;
	int const MIN_HEIGHT = 5;
	fruitLoc.Y = rand() % ((thick.GetWinWidth()- 2) - MIN_WIDTH + 1) + MIN_WIDTH;
	fruitLoc.X = rand() % ((thick.GetWinHeight() - 5) - MIN_HEIGHT + 1) + MIN_HEIGHT;
}

void cStatusView::Update()
{
	//COORD loc{ 0,5 };
	//std::vector<FileInfo>& data = fileList.data;
	//for (auto const& x : data)
	//{
	//	thick.ShowMessage(x.fileName_, loc);
	//	loc.Y++;
	//	if (loc.Y > 45)
	//	{
	//		return;
	//	}
	//}

}