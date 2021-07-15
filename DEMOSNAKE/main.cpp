#define GLUT_DISABLE_ATEXIT_HACK
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<tchar.h>
/*#include <irrklang/irrKlang.h>
using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();
*/
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define MAX 60
#define COLUMNS 40
#define ROWS 40
//#define FPS 7
int FPS = 7;
int id;
extern short sDirection;
bool gameOver = false;
int score = 0;
void intro();
void lastd();
void display_callback();
void reshape_callback(int, int);
void timer_callback(int);
void keyboard_callback(int, int, int);
void initGrid(int, int);
void drawGrid();
void drawSnake();
void drawFood();
void dmsg();
void tree();
void round();
void grass();
void random(int&, int&);
float r=0.0, g=1.0, b=1.0;
void init()
{
	glClearColor(0.0, 0.5, 0.0, 0.0);
	initGrid(COLUMNS, ROWS);
	
}
void grass()
{
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2f(6, 6);
	glVertex2f(6, 34);
	glVertex2f(34, 34);
	glVertex2f(34, 6);
	glEnd();
}

void round() {
	float theta;
	glColor3f(0.2, 0.92, 0.33);				//top
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(400 + 0.5 * cos(theta), 300 + 0.5 * sin(theta));
	}
	glEnd();
}

void tree()
{
	//tree 1
	glColor3f(0.57, .17, 0.017);
	glBegin(GL_POLYGON);
	glVertex2d(2, 2);
	glVertex2d(3, 2);
	glVertex2d(3, 7);
	glVertex2d(2, 7);
	glEnd();
	float theta;
	glColor3f(0.2, 0.92, 0.33);				//top
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(2.5+ 1.8 * cos(theta), 7 + 1.8* sin(theta));
	}
	glEnd();
	glColor3f(0.2, 0.92, 0.33);				//left
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(1.8 + 1.5 * cos(theta), 6 + 1.5 * sin(theta));
	}
	glEnd();
	glColor3f(0.2, 0.92, 0.33);				//bottom
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(2.5 + 1 * cos(theta), 5.2 + 1 * sin(theta));
	}
	glEnd();
	glColor3f(0.2, 0.92, 0.33);					//right
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(3.5 + 1.2 * cos(theta), 6 + 1.2 * sin(theta));
	}
	glEnd();



	//tree 2
	glColor3f(0.57, .17, 0.017);
	glBegin(GL_POLYGON);
	glVertex2d(2, 12);
	glVertex2d(3, 12);
	glVertex2d(3, 17);
	glVertex2d(2, 17);
	glEnd();
	
	glColor3f(0.2, 0.92, 0.33);				//top
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(2.5 + 1.8 * cos(theta), 17 + 1.8 * sin(theta));
	}
	glEnd();
	glColor3f(0.2, 0.92, 0.33);				//left
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(1.8 + 1.5 * cos(theta),16 + 1.5 * sin(theta));
	}
	glEnd();
	glColor3f(0.2, 0.92, 0.33);				//bottom
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(2.5 + 1 * cos(theta), 15.2 + 1 * sin(theta));
	}
	glEnd();
	glColor3f(0.2, 0.92, 0.33);					//right
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;
		glVertex2f(3.5 + 1.2 * cos(theta), 16 + 1.2 * sin(theta));
	}
	glEnd();

}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5, 0.5, 1.0, 0.0);
	grass();
	drawGrid();
	tree();
	drawSnake();
	drawFood();
	round();
	glutSwapBuffers();
	if (gameOver)
	{
		
		char _score[10];
		_itoa_s(score, _score, 10);
		char text[50] = "Your score: ";
		strcat_s(text, _score);
		MessageBoxA(NULL, text, "GAME OVER", 0x00000005L);
		/*switch (id)
			{
			case IDRETRY:
				glutDisplayFunc(intro);
				break;
			case IDCANCEL:
				exit(0);
				break;
			}*/
			/*if (MessageBoxA(NULL, text, "GAME OVER", 0x00000005L) == IDRETRY)
			{
				glutDisplayFunc(intro);

			}
			else {
				exit(0);
			}*/
		exit(0);


	}
}
/*void dmsg()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	char _score[10];
	_itoa_s(score, _score, 10);
	char text[50] = "Your score: ";
	strcat_s(text, _score);

	glColor3f(1.0, 1.0, 0.0);
	glRasterPos3f(12, 20, 0);
	char msg8[] = "Your score is _score ";
	for (int i = 0; i < strlen(msg8); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg8[i]);
	glBegin(GL_POLYGON);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glVertex2i(12, 12);
	glVertex2i(12, 20);
	glVertex2i(20, 20);
	glVertex2i(20, 12);
	glEnd();


}
/*void lastd()
{
	char _score[10];
	_itoa_s(score, _score, 10);
	//char text[50] = "Your score: ";
	//strcat_s(text, _score);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(12, 35, 0);
	char msg7[] = "YOUR SCORE IS: ";
	strcat_s(msg7, _score);
	for (int i = 0; i < strlen(msg7); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg7[i]);



}*/
/*void reshape(int w, int h)
{
	glClearColor(0.0, 0.5, 0.0, 0.0);
	initGrid(COLUMNS, ROWS);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		//gluOrtho2D(0, 500, 0, 500* (float)h / w);
		glOrtho(0.0, COLUMNS, 0.0, ROWS * (float)h / w, -1.0, 1.0);
	}
	else
	{
		//gluOrtho2D(0, 500 * (float)w / h, 0, 500);
		glOrtho(0.0, COLUMNS* (float)w / h, 0.0, ROWS, -1.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
}*/
void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}

void keyboard_callback(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (sDirection != DOWN)
			sDirection = UP;
		break;
	case GLUT_KEY_DOWN:
		if (sDirection != UP)
			sDirection = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		if (sDirection != LEFT)
			sDirection = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if (sDirection != RIGHT)
			sDirection = LEFT;
		break;

	}
}
void intro()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(12, 35, 0);
	char msg1[] = "||  SLYTHERIN (snake game)  ||";
	for (int i = 0; i < strlen(msg1); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

	glRasterPos3f(6, 29, 0);
	char msg2[] = "SUBMITTED BY:    REVISHA SHAREEN VAS   (4SO18CS096)";
	for (int i = 0; i < strlen(msg2); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg2[i]);

	glRasterPos3f(6, 25, 0);
	char msg3[] = "AND:    RHEA BENEDICTA D'SOUZA   (4SO18CS097)";
	for (int i = 0; i < strlen(msg3); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg3[i]);
	/*glRasterPos3f(16, 25, 0);
	char msg4[] = "RHEA BENEDICTA D'SOUZA   (4SO18CS097)";
	for (int i = 0; i < strlen(msg4); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg4[i]);*/
	glRasterPos3f(6, 21, 0);
	char msg6[] = "UNDER THE GUIDANCE OF:    MR ROHAN DON SALINS";
	for (int i = 0; i < strlen(msg6); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg6[i]);


	glRasterPos3f(12, 12, 0);
	char msg5[] = "PRESS X TO START THE GAME ";
	for (int i = 0; i < strlen(msg5); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg5[i]);

	glutSwapBuffers();
}
void keys(unsigned char key, int x, int y)
{
	if (key == 'x')
	{
		glutDisplayFunc(display_callback);
	}
	glutPostRedisplay();
}
void myMenu(int option)
{
	if (option == 1)
	{
		FPS = FPS + 3;
	}
	else if (option == 2)
	{
		r = 0.0;
		g = 0.0;
		b = 0.0;
	}
	else if (option == 3)
	{
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_START, 1.0);
		glFogf(GL_FOG_END, 40.0);
		float color[] = { 0.5,0.5,0.5,1.0 };
		glFogfv(GL_FOG_COLOR, color);
	}
	
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("SNAKE");
	//glutDisplayFunc(display_callback);
	glutDisplayFunc(intro);
	//bool played = PlaySound(_T("breakout.wav"), NULL, SND_SYNC);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutSpecialFunc(keyboard_callback);
	glutKeyboardFunc(keys);
	init();
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Speed up", 1);
	glutAddMenuEntry("Go black", 2);
	glutAddMenuEntry("Fog effect", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	sndPlaySound(_T("breakout.wav"), SND_ASYNC);
	//SoundEngine->play2D("breakout.wav", true);
	glutMainLoop();

	//glutInitWindowPosition(0,0);
	return 0;
}


