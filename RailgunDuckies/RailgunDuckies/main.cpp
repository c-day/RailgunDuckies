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
float globalRotate = 0;
bool wireframe = false;
int window_width = 1024;
int window_height = 768;
bool paused = false;
double pausedTime = 0;
double lastFrameTime;
double aspect = double(window_width) / double(window_height);
const int period = 1000 / 60;
float pause_time = 0.0;
float now = 0.0;
float gameTime = 0;
std::unique_ptr<ducky> myDuck(new ducky());
std::unique_ptr<railGun> myGun(new railGun());
std::unique_ptr<game> myGame(new game());
balloon myBalloon;
glm::vec3 camera;

//std::unique_ptr<balloon> myBalloon(new balloon());


/* Set up game modes
gameMode = 1 --> play game
gameMode = 2 --> duckie beauty mode
gameMode = 3 --> rail gun beauty mode
gameMode = 4 --> balloon beauty mode
gameMode = 5 --> automated play
*/
int gameMode = 1;

/* 
Set up function to draw text on screen
*/

/*
void updateCamera() {
	camera = glm::rotateX(glm::vec3(0, 2, 8), myGame->getGun()->rx);
	camera = glm::rotateY(camera, myGame->getGun()->ry);
}
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
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
	glEnable(GL_LIGHTING);
}

void DisplayTime(char * s)
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10, 40, -5.5f);
	glScalef(0.25f, 0.25f, 1.0f);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
	glEnable(GL_LIGHTING);
}

//Set up world and viewport

void DisplayFunc()
{	
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
		//Draw Game
		//updateCamera();
		gluLookAt(0, 2, 8, 0, 2, 0, 0, 1, 0);
		myGame->drawScene(window_width, window_height);
		char int_string[32];
		char disp_string[64] = "Score: ";
		sprintf(int_string, "%d", myGame->getScore());
		strcat(disp_string, int_string);
		char float_string[32];
		char disp_time[64] = "Time: ";
		sprintf(float_string, "%g", (gameTime/1000));
		strcat(disp_time, float_string);
		DisplayMode(disp_string);
		DisplayTime(disp_time);
		break;
		}
	case 2:
		{
		//fancy duck
		myDuck->drawBDuck(gameTime);
		DisplayMode("Duckie Beauty Mode");
		break;
		}
	case 3:
		{
		//fancy gun
		myGun->drawBGun(gameTime);
		DisplayMode("Rail Gun Beauty Mode");
		break;
		}
	case 4: 
		{
		//fancy balloon
		myBalloon.drawBBalloon(gameTime);
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
	case GLUT_KEY_LEFT:
		globalRotate++;
		//glRotatef(globalRotate, 0, 1, 0);
		break;
	case GLUT_KEY_RIGHT: 
		globalRotate--;
		//glRotatef(globalRotate, 0, 1, 0);
		break;
	}
}

void MouseFunc(int x, int y) {
	float ycenter = ((float)window_height)/2;
	float xcenter = ((float)window_width)/2;
	float ydegp = ycenter/25;
	float ydegn = ycenter/25;
	float xdeg = xcenter/55;
	float yr, xr;
	if(y < ycenter) {
		yr = ((ycenter-y)/ydegp);
		myGame->getGun()->updateGunY(yr+25);
	} else {
		yr = ((y-ycenter)/ydegn);
		myGame->getGun()->updateGunY(25-yr);
	}
	if(x < xcenter) {
		xr = ((xcenter-x)/xdeg);
		myGame->getGun()->updateGunX(xr);
	} else {
		xr = -((x-xcenter)/xdeg);
		myGame->getGun()->updateGunX(xr);
	}
}

void TimerFunc(int value)
{
	now += period;

	if(!paused) {
		gameTime = now - pausedTime; 
	} 

	if(paused) {
		pausedTime += now - lastFrameTime;
	}
	lastFrameTime = now;

	myGame->updateGame(gameTime);

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
	glutPassiveMotionFunc(MouseFunc);
	glutTimerFunc(period, TimerFunc, 0);
	glutDisplayFunc(DisplayFunc);
	glutMainLoop();
}


