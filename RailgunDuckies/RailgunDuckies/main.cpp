///////////////////////////////////////////////////////////////////////////////
/////*********************************************************************/////
//   CS 559                                                                  //
//   Project 1: Railgun Duckies                                              //
//                                                                           //
//   Authors:                                                                //
//    Craig Day                                                              //
//    Adam Hart                                                              //
//                                                                           //
//   University of Wisconsin-Madison                                         //
/////*********************************************************************/////
///////////////////////////////////////////////////////////////////////////////



//Include any necessary libraries

#include <gl/freeglut.h>
#include "ducky.h"
#include "balloon.h"
#include "railGun.h"
#include "game.h"
#include <algorithm>
#include <iostream>
#include <string>

//Define any global variables

bool wireframe = false;
int window_width = 1024;
int window_height = 768;
bool paused = false;
double pausedTime = 0;
double lastFrameTime;
double aspect = double(window_width) / double(window_height);
const int period = 1000 / 60;
double pause_time = 0.0;
double now = 0.0;
double gameTime = 0;


/* Set up game modes
gameMode = 1 --> play game
gameMode = 2 --> duckie beauty mode
gameMode = 3 --> rail gun beauty mode
gameMode = 4 --> balloon beauty mode
gameMode = 5 --> automated play
*/
int gameMode = 2;

/* 
Set up function to draw text on screen
*/
void DisplayMode(char * s)
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10, 10, -5.5f);
	glScalef(0.25f, 0.25f, 1.0f);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
}

//Set up world and viewport

void DisplayFunc()
{
	//keep track of time 
	now = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;

	if(!paused) {
		gameTime = now - pausedTime; 
	} 

	if(paused) {
		pausedTime += now - lastFrameTime;
	}
	lastFrameTime = now;
	
	
	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat light_position[] = { 0.5, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glShadeModel (GL_SMOOTH);

	// Set up Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55, aspect, 1, 100);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	switch (gameMode) {
	case 1:
		{
		//Play game
		std::unique_ptr<game> myGame(new game());
		myGame->playGame();
		break;
		}
	case 2:
		{
		//fancy duck
		glPushMatrix();
		glTranslated(0,0,-2);
		glRotated(gameTime * 30.0, 0.1, 1, 0);
		std::unique_ptr<ducky> myDuck(new ducky());
		myDuck->drawDuck();
		glPopMatrix();
		DisplayMode("Duckie Beauty Mode");
		break;
		}
	case 3:
		{
		//fancy gun
		glPushMatrix();
		glTranslated(0, 0, -8);
		glRotated(gameTime * 30.0, 0.1, 1, 0.1);
		std::unique_ptr<ducky> myDuck3(new ducky());
		std::unique_ptr<railGun> myGun(new railGun());
		myDuck3->updatePos(0, 1, 1.35, 0, 90);
		myDuck3->drawDuck();
		myGun->drawGun();
		glPopMatrix();
		DisplayMode("Rail Gun Beauty Mode");
		break;
		}
	case 4: 
		{
		//fancy balloon
		glPushMatrix();
		glTranslated(0, 0, -5);
		glRotated(gameTime * 45.0, 0.1, 1, 0.1);
		std::unique_ptr<balloon> myBalloon(new balloon());
		myBalloon->drawBalloon();
		glPopMatrix();
		DisplayMode("Balloon Beauty Mode");
		break;
		}
	case 5:
		{
		//lazy man's game
		break;
		}
	}
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void ReshapeFunc(int w, int h)
{
	window_height = h;
	window_width = w;
	aspect = double(w) / double(h);
	glutPostRedisplay();
}

void KeyboardFunc(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'c':
		//switch camera modes
		break;
	case 'p':
		paused = !paused;
		break;
	case 'w':
		wireframe = !wireframe;
		break;
	case 32:
		//FIRE DUCK!!!!!!!!!
		break;
	// Hitting lower case x or the escape key will  exit the
	// glut event loop.
	case 'x':
	case 27:
		glutLeaveMainLoop();
		return;
	}
	glutPostRedisplay();
}

void SpecialKeyFunc(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_F1:
		//cycle through the game modes
		switch (gameMode)
		{
		case 1: 
			gameMode = 2;
			break;
		case 2:
			gameMode = 3;
			break;
		case 3:
			gameMode = 4;
			break;
		case 4:
			gameMode = 5;
			break;
		case 5:
			gameMode = 1;
			break;
		default:
			gameMode = 1;
			break;
		}

	}
}

void TimerFunc(int value)
{

	glutTimerFunc(period, TimerFunc, value);
	glutPostRedisplay();
}



/*/ MAIN METHOD   //////////////////////////
//
//  -Initialize the skybox
//  -place the railgun in the world
//  -place any lights in the world
//  -create/shoot ducks as needed
//  -create/move baloons as needed
//  -keep track of score
//////////////////////////////////////////*/

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Rail Gun Duckies");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialKeyFunc);
	glutDisplayFunc(DisplayFunc);
	glutMainLoop();
}


