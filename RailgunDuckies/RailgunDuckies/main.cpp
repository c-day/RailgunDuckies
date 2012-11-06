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
#include <stdio.h>
#include <string>
#include <sstream>
#include <glm/glm.hpp>

using namespace std;

//Define any global variables
int window_width = 1024;
int window_height = 768;
int camMode = 1;

float globalRotateX = 0;
float globalRotateY = 0;
float pause_time = 0.0;
float now = 0.0;
float gameTime = 0;
float pausedTime = 0;
float lastFrameTime;
float aspect = float(window_width) / float(window_height);
float launchVelocity = 0;
float lastVel = 0;

bool wireframe = false;
bool paused = false;

const int period = 1000 / 60;

std::unique_ptr<ducky> myDuck(new ducky());
std::unique_ptr<railGun> myGun(new railGun());
std::unique_ptr<game> myGame(new game());
std::unique_ptr<game> myAutoGame(new game());
balloon myBalloon;
glm::vec3 camera;

/* Set up game modes
gameMode = 1 --> balloon beauty mode
gameMode = 2 --> duckie beauty mode
gameMode = 3 --> rail gun beauty mode
gameMode = 4 --> play game
gameMode = 5 --> automated play
*/
int gameMode = 1;

/* 
Set up functions to draw text on screen
*/
//Display the current mode we are in (except when in game).
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

//Display the game runtime on the screen when in game.
void DisplayTime(char * s)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10, 10, -2.5f);
	glScalef(0.25f, 0.25f, 1.0f);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
	glEnable(GL_LIGHTING);
}

//Display the number of balloons missed when in game. 
void DisplayMissed(char * s)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10, 80, -2.5f);
	glScalef(0.25f, 0.25f, 1.0f);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
	glEnable(GL_LIGHTING);
}

//Display the velocity of the to-be-launced duck. 
void DisplayVel(char * s)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(float(window_width/2) - 90, 10, -2.5f);
	glScalef(0.25f, 0.25f, 1.0f);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
	glEnable(GL_LIGHTING);
}

//Display the launch velocity of the previous duck. 
void DisplayLast(char * s)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(float(window_width) - 320, 10, -2.5f);
	glScalef(0.25f, 0.25f, 1.0f);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) s);
	glEnable(GL_LIGHTING);
}

//Check and display GL error on console window for debugging
bool CheckGLErrors(string location) {
	bool error_found = false;
	GLenum  error;
	const GLubyte *errorString;
	while ((error = glGetError()) != GL_NO_ERROR) {
		cout <<"\n";
		cout <<location; 
		error_found = true;
		errorString = gluErrorString(error);
		cout << errorString;
	}

	return error_found;
}

//Display function called in glutMainLoop
void DisplayFunc()
{	
	CheckGLErrors("Beginning of DisplayFunc");

	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//put a light in the world above the gun. 
	GLfloat light_position[] = { 0, 50, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glShadeModel (GL_SMOOTH);

	// Set up Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55, aspect, 1, 150);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	Switch on the game mode.  When in the play game mode, allow the user to
	switch camera modes.  Updates the game status text display with current
	values. 
	*/
	switch (gameMode) {
	case 4:
		{
			//Game
			if(!myGame->gameOver()) {
				switch (camMode) {
				case 1:
					gluLookAt(0, 2, 8, 0, 2, 0, 0, 1, 0);
					break;
				case 2:
					gluLookAt(0, 2, 8, myGame->getDuck()->getDuckPos().x, myGame->getDuck()->getDuckPos().y+1, myGame->getDuck()->getDuckPos().z, 0, 1, 0);				
					break;
				case 3:
					if (!myGame->getShot()) {
						gluLookAt(myGame->getDuck()->getDuckPos().x, myGame->getDuck()->getDuckPos().y, myGame->getDuck()->getDuckPos().z, 
							myGame->getGun()->getBvec().x, myGame->getGun()->getBvec().y + 1, myGame->getGun()->getBvec().z, 0, 1, 0);
					} else {
						gluLookAt(myGame->getDuck()->getDuckPos().x, myGame->getDuck()->getDuckPos().y, myGame->getDuck()->getDuckPos().z-1, 
							myGame->getDuck()->getDuckPos().x, myGame->getDuck()->getDuckPos().y, myGame->getDuck()->getDuckPos().z-2, 0, 1, 0);
					}
					break;
				}
				myGame->drawScene(window_width, window_height);
				char score_string[16];
				char time_string[64];
				char miss_string[16];
				char vel_string[16];
				char last_vel[16];
				char disp_score[16] = "Score: ";
				char disp_miss[16] = "Missed: ";
				char disp_time[64] = "Time: ";
				char disp_vel[32] = "Velocity: ";
				char disp_last[32] = "Last Velocity: ";
				sprintf_s(score_string, "%d", myGame->getScore());
				sprintf_s(time_string, "%.1f", (gameTime/1000));
				sprintf_s(miss_string, "%d", myGame->missed);
				sprintf_s(vel_string, "%.1f", launchVelocity);
				sprintf_s(last_vel, "%.1f", lastVel);
				strcat_s(disp_score, score_string);
				strcat_s(disp_time, time_string);
				strcat_s(disp_miss, miss_string);
				strcat_s(disp_vel, vel_string);
				strcat_s(disp_vel, "%");
				strcat_s(disp_last, last_vel);
				strcat_s(disp_last, "%");
				DisplayMode(disp_score);
				DisplayTime(disp_time);
				DisplayMissed(disp_miss);
				DisplayVel(disp_vel);
				DisplayLast(disp_last);
			} else {  //The user has lost the game, put the replay prompt on screen. 
				lastVel = 0;
				glClearColor(0, 0, 0, 0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0, window_width, 0, window_height, 1, 10);
				glViewport(0, 0, window_width, window_height);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				//Push to display first line
				glPushMatrix();
				glTranslatef(float(window_width/2 - 200), float(window_height/2 + 200), -5.5f);
				glScalef(0.5f, 0.5f, 1.0f);
				glDisable(GL_LIGHTING);
				glColor3f(1, 0, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) "GAME OVER");
				glPopMatrix();

				glColor3d(1, 1, 1);

				//Push to display second line
				glPushMatrix();
				glTranslatef(float(window_width/2 - 150), float(window_height/2 + 100), -5.5f);
				glScalef(0.5f, 0.5f, 1.0f);
				char score_string[16];
				char disp_score[16] = "Score: ";
				sprintf_s(score_string, "%d", myGame->getScore());
				strcat_s(disp_score, score_string);
				glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) disp_score);
				glPopMatrix();

				//Push to display responses
				glPushMatrix();
				glTranslatef(float(window_width/2 - 300), float(window_height/2), -5.5f);
				glScalef(0.5f, 0.5f, 1.0f);
				if (myGame->getScore() == 0) {
					glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) " You are terrible ");
				} else if (myGame->getScore() < 50) {
					glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) "     meh        ");
				} else if (myGame->getScore() < 100) {
					glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) "     aight       ");
				} else {
					glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) "Can u do it again?");
				}
				glPopMatrix();

				//Push to display third line
				glPushMatrix();
				glTranslatef(float(window_width/2 - 175), float(window_height/2) - 100, -5.5f);
				glScalef(0.5f, 0.5f, 1.0f);
				glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) "Play Again?");
				glPopMatrix();

				//Push to display last line
				glPushMatrix();
				glTranslatef(float(window_width/2 - 275), float(window_height/2 - 200), -5.5f);
				glScalef(0.5f, 0.5f, 1.0f);
				glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) "y/n (hit the key)");
				glPopMatrix();
				glEnable(GL_LIGHTING);
			}
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
			myAutoGame->setAuto(true);
			switch (camMode) {
			case 1:
				gluLookAt(0, 2, 8, 0, 2, 0, 0, 1, 0);
				break;
			case 2:
				gluLookAt(0, 2, 8, myAutoGame->getDuck()->getDuckPos().x, myAutoGame->getDuck()->getDuckPos().y+1, myAutoGame->getDuck()->getDuckPos().z, 0, 1, 0);				
				break;
			case 3:
				if (!myAutoGame->getShot()) {
					gluLookAt(myAutoGame->getDuck()->getDuckPos().x, myAutoGame->getDuck()->getDuckPos().y, myAutoGame->getDuck()->getDuckPos().z, 
						myAutoGame->getGun()->getBvec().x, myAutoGame->getGun()->getBvec().y + 1, myAutoGame->getGun()->getBvec().z, 0, 1, 0);
				} else {
					gluLookAt(myAutoGame->getDuck()->getDuckPos().x, myAutoGame->getDuck()->getDuckPos().y, myAutoGame->getDuck()->getDuckPos().z-1, 
						myAutoGame->getDuck()->getDuckPos().x, myAutoGame->getDuck()->getDuckPos().y, myAutoGame->getDuck()->getDuckPos().z-2, 0, 1, 0);
				}
				break;
			}
			myAutoGame->drawScene(window_width, window_height);
			char score_string[16];
			char time_string[64];
			char miss_string[16];
			char vel_string[16];
			char last_vel[16];
			char disp_score[16] = "Score: ";
			char disp_miss[16] = "Missed: ";
			char disp_time[64] = "Time: ";
			char disp_vel[32] = "Velocity: ";
			char disp_last[32] = "Last Velocity: ";
			sprintf_s(score_string, "%d", myAutoGame->getScore());
			sprintf_s(time_string, "%.1f", (gameTime/1000));
			sprintf_s(miss_string, "%d", myAutoGame->missed);
			sprintf_s(vel_string, "%.1f", launchVelocity);
			sprintf_s(last_vel, "%.1f", lastVel);
			strcat_s(disp_score, score_string);
			strcat_s(disp_time, time_string);
			strcat_s(disp_miss, miss_string);
			strcat_s(disp_vel, vel_string);
			strcat_s(disp_vel, "%");
			strcat_s(disp_last, last_vel);
			strcat_s(disp_last, "%");
			DisplayMode(disp_score);
			DisplayTime(disp_time);
			DisplayMissed(disp_miss);
			DisplayVel(disp_vel);
			DisplayLast(disp_last);
			break;
		}
	}

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

	CheckGLErrors("End of DisplayFunc");
}

//Part of GLUT Main Loop. Called when window is resized
void ReshapeFunc(int w, int h)
{
	window_height = h;
	window_width = w;
	aspect = float(w) / float(h);
	glutPostRedisplay();
}

//Part of GLUT Main Loop. Called when a key is pressed.
void KeyboardFunc(unsigned char c, int x, int y)
{

//Detects Restart Choice once Main Game Mode game ends
if(myGame->gameOver()){
	if (c == 'y'){
		myGame->resetGame();
		return;
	} else if(c == 'n') {
		glutLeaveMainLoop();
		return;
	}
}

//Resets game on press of 'r'
if(!myGame->gameOver() && gameMode == 4) {
	if (c == 'r') {
		myGame->resetGame();
	}
}

	//Standard key switches, not dependent on mode
	switch (c)
	{
	case 'c':
		//switch camera modes
		if(gameMode == 4 || gameMode == 5) {
			switch (camMode)
			{
			case 1: 
				camMode = 2;
				break;
			case 2:
				camMode = 3;
				break;
			case 3:
				camMode = 1;
				break;
			default:
				camMode = 1;
			}
		} else {
			camMode = 1;
		}
		break;
	//Toggles pause
	case 'p':
		paused = !paused;
		break;
	//Toggles Wireframe Mode
	case 'w':
		wireframe = !wireframe;
		break;
	//Detects a space press to increment the Launch Velocity
	case 32:
		if(!paused && gameMode == 4) {
			if(!myGame->getShot()){
				if (launchVelocity < 100) {
					launchVelocity += 1.0f;
				} else { 
					launchVelocity = 100.0f;
				}
			} else {
				launchVelocity = 0;
			}
		}
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

//Separate Key Function to detect when the space bar is released. Launches Duck
void KeyUpFunc(unsigned char c, int x, int y)
{
	switch(c) {
	case 32:
		if(!paused && gameMode == 4) {
			if(!myGame->getShot()) {
				myGame->shootDuck(100*(launchVelocity/100));
				lastVel = launchVelocity;
				launchVelocity = 0.0f;
			} else {
				myGame->resetDuck();
			}
		}
		break;
	}
}

//Key Function to detect 'F1'. Switches modes
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

//Handles passive mouse input and rotates Railgun inside of game
void MouseFunc(int x, int y) {
	if(!paused && myGame->getGun()->getMove() && !myGame->getAuto()){
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
}

//Part of GLUT main loop. Called on fixed period. Updates current game time as well as
//	the game state based upon the time interval.
void TimerFunc(int value)
{
	now += period;

	if(!paused) {
		gameTime = now - pausedTime;
		if(gameMode == 4) {
			myGame->updateGame();
		} else if (gameMode == 5) { //If in Auto Game Mode, automatically and randomly shoots

			srand(unsigned int(time(NULL)));

			

			myAutoGame->updateGame();
			if (!myAutoGame->getShot()) {
				int targetBalloon = rand() % myAutoGame->getBalloons().size();

				float x = (myAutoGame->getBalloons()[targetBalloon].getBalPos().x);
				float y = (myAutoGame->getBalloons()[targetBalloon].getBalPos().y);
				float z = (myAutoGame->getBalloons()[targetBalloon].getBalPos().z);
				float autoVel = float((rand() % 86) + 15);

				myAutoGame->getGun()->updateGunX((rand() % 56) - 22.5);
				myAutoGame->getGun()->updateGunY((rand() % 31));
				myAutoGame->shootDuck(autoVel);
				lastVel = autoVel;
				launchVelocity = 0.0f;
			}
			myAutoGame->updateGame();
		}
	} 

	if(paused) {
		pausedTime += now - lastFrameTime;
	}
	lastFrameTime = now;



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
	glEnable(GL_LIGHT1);



	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyUpFunc);
	glutSpecialFunc(SpecialKeyFunc);
	glutPassiveMotionFunc(MouseFunc);
	glutTimerFunc(period, TimerFunc, 0);
	glutDisplayFunc(DisplayFunc);
	glutMainLoop();
}


