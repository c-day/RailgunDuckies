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
#include <glm/glm.hpp>

//Define any global variables
float globalRotateX = 0;
float globalRotateY = 0;
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
float launchVelocity = 0;

//std::unique_ptr<balloon> myBalloon(new balloon());


/* Set up game modes
gameMode = 1 --> balloon beauty mode
gameMode = 2 --> duckie beauty mode
gameMode = 3 --> rail gun beauty mode
gameMode = 4 --> play game
gameMode = 5 --> automated play
*/
int gameMode = 1;

/* 
Set up function to draw text on screen
*/


void updateCamera() {
	camera = glm::rotateX(camera, globalRotateX);
	camera = glm::rotateY(camera, globalRotateY);
}


void DisplayMode(char * s)
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10, 45, -5.5f);
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
	glTranslatef(10, 10, -5.5f);
	glScalef(0.25f, 0.25f, 1.0f);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
	glEnable(GL_LIGHTING);
}

void DisplayMissed(char * s)
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10, 80, -5.5f);
	glScalef(0.25f, 0.25f, 1.0f);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
	glEnable(GL_LIGHTING);
}
void DisplayVel(char * s)
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(window_width/2 - 90, 10, -5.5f);
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
	case 4:
		{
		//Game
		//updateCamera();
		//myGame(new game());
		gluLookAt(0, 2, 8, 0, 2, 0, 0, 1, 0);
		//gluLookAt(camera.x, camera.y + 2, camera.z + 8, 0, 2, 0, 0, 1, 0);
		myGame->drawScene(window_width, window_height);
		char score_string[16];
		char time_string[16];
		char miss_string[16];
		char vel_string[16];
		char disp_score[16] = "Score: ";
		char disp_miss[16] = "Missed: ";
		char disp_time[16] = "Time: ";
		char disp_vel[16] = "Velocity: ";
		sprintf(score_string, "%d", myGame->getScore());
		sprintf(time_string, "%.1f", (gameTime/1000));
		sprintf(miss_string, "%d", myGame->missed);
		sprintf(vel_string, "%.1f", launchVelocity);
		strcat(disp_score, score_string);
		strcat(disp_time, time_string);
		strcat(disp_miss, miss_string);
		strcat(disp_vel, vel_string);
		strcat(disp_vel, "%");
		DisplayMode(disp_score);
		DisplayTime(disp_time);
		DisplayMissed(disp_miss);
		DisplayVel(disp_vel);
		break;
		}
	case 1:
		{
		//fancy duck
		myDuck->drawBDuck(gameTime);
		DisplayMode("Duckie Beauty Mode");
		break;
		}
	case 2:
		{
		//fancy gun
		myGun->drawBGun(gameTime);
		DisplayMode("Rail Gun Beauty Mode");
		break;
		}
	case 3: 
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
		launchVelocity += 0.5f; 
		break;
	// Hitting lower case x or the escape key will  exit the
	// glut event loop.
	case 'x':
	case 27:
		glutLeaveMainLoop();
		return;
	case 49:
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
	glutPostRedisplay();
}

void KeyUpFunc(unsigned char c, int x, int y)
{
	switch(c) {
	case 32: 
		myGame->shootDuck(launchVelocity);
		break;
	}
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
		globalRotateX++;
		//glRotatef(globalRotate, 0, 1, 0);
		break;
	case GLUT_KEY_RIGHT: 
		globalRotateX--;
		//glRotatef(globalRotate, 0, 1, 0);
		break;
	case GLUT_KEY_UP: 
		globalRotateY++;
		break;
	case GLUT_KEY_DOWN:
		globalRotateY--;
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
	glutKeyboardUpFunc(KeyUpFunc);
	glutSpecialFunc(SpecialKeyFunc);
	glutPassiveMotionFunc(MouseFunc);
	glutTimerFunc(period, TimerFunc, 0);
	glutDisplayFunc(DisplayFunc);
	glutMainLoop();
}


