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
#include <algorithm>
#include <iostream>
#include <string>

//Define any global variables

bool wireframe = false;
int window_width = 1024;
int window_height = 768;
double aspect = double(window_width) / double(window_height);
const int period = 1000 / 60;


/* Set up game modes
gameMode = 1 --> play game
gameMode = 2 --> duckie beauty mode
gameMode = 3 --> rail gun beauty mode
gameMode = 4 --> balloon beauty mode
gameMode = 5 --> automated play
*/
int gameMode = 2;

//Set up world and viewport

void DisplayFunc()
{
	//keep track of time 
	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;

	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
		break;
		}
	case 2:
		{
		//fancy duck
		glTranslated(0,0,-5);
		glRotated(elapsed_time * 60.0, 0, 1, 0);
		std::unique_ptr<ducky> myDuck(new ducky());
		std::unique_ptr<ducky> myDuck2(new ducky());
		myDuck2->updatePos(2, 0, 0);
		myDuck->updatePos(-2, 0, 0);
		myDuck->drawDuck();
		myDuck2->drawDuck();
		break;
		}
	case 3:
		{
		//fancy gun
		break;
		}
	case 4: 
		{
		//fancy balloon
		break;
		}
	case 5:
		{
		//lazy man's game
		break;
		}
	}
	
	
	// A call to glFlush()  should  NOT  be  needed  with  a single
	// buffered program  such  as this.  However,  AMD  drivers  in
	// particular do not draw properly without this.
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
	glutCreateWindow("Railgun Duckies");
	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialKeyFunc);
	glutDisplayFunc(DisplayFunc);
	glutMainLoop();
}


