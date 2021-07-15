#define GLUT_DISABLE_ATEXIT_HACK
#include<stdlib.h>
#include<windows.h>
#include<GL/glut.h>
#include<tchar.h>
#include<ctime>
/*#include <irrklang/irrKlang.h>
using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();*/
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define MAX 60

int gridX, gridY;
int snake_length = 5;
bool food = true;
int foodX, foodY;
short sDirection = RIGHT;
extern bool gameOver;
extern int score;
int posX[60] = { 20,20,20,20,20 }, posY[60] = { 20,19,18,17,16 };
void initGrid(int, int);
void drawGrid();
void drawSnake();
void drawFood();
void random(int&, int&);
void initGrid(int x, int y)
{
	gridX = x;
	gridY = y;

}
void unit(int, int);
void drawGrid()
{
	for (int x = 5; x < gridX-5 ; x++)
	{
		for (int y = 5; y < gridY-5 ; y++)
		{
			unit(x, y);
		}
	}
}

void unit(int x, int y)
{
	if (x == 5 || y == 5 || x == gridX - 6 || y == gridY - 6)
	{
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(0.0, 1.0, 1.0);
	}


	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
}

void drawFood()
{
	if (food)
		random(foodX, foodY);
	food = false;
	glColor3f(1.0, 0.0, 0.0);
	glRectf(foodX, foodY, foodX + 1, foodY + 1);

}

void drawSnake()
{
	for (int i = snake_length - 1; i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}
	if (sDirection == UP)
		posY[0]++;
	else if (sDirection == DOWN)
		posY[0]--;
	else if (sDirection == RIGHT)
		posX[0]++;
	else if (sDirection == LEFT)
		posX[0]--;
	for (int i = 0; i < snake_length; i++)
	{
		if (i == 0)
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(1.0, 1.0, 0.0);
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);

	}
	if (posX[0] == 5 || posX[0] == gridX - 6 || posY[0] == 5 || posY[0] == gridY - 6)
		gameOver = true;
	if (posX[0] == foodX && posY[0] == foodY)
	{
		sndPlaySound(_T("crunch.wav"), SND_ASYNC);
		//SoundEngine->play2D("crunch.wav", true);
		score++;
		snake_length++;
		if (snake_length > MAX)
			snake_length = MAX;
		food = true;
	}
	


}

void random(int& x, int& y)
{
	int _maxX = gridX - 7;
	int _maxY = gridY - 7;
	int _min = 6;
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);
}

