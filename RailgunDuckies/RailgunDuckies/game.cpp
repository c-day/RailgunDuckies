#include <GL/freeglut.h>
#include <vector>
#include <iostream>

#include "game.h"
#include "ducky.h"
#include "balloon.h"
#include "railGun.h"

using namespace std;
bool done;

game::game() {
	won = false;
	done = false;
}

void KeyboardInput(unsigned char c, int x, int y)
{
	switch (c) {
		case GLUT_KEY_F1:
			done = true;
			break;


	}
	glutPostRedisplay();
}

void GameDisplay() {
	&game::drawScene;
}

void game::drawScene() {

	for (int i = 0;  i <= ducks.size(); ++i) {
		ducks[i]->drawDuck();
	}
	for (int i = 0; i <= balloons.size(); ++i) {
		balloons[i]->drawBalloon();
	}

}

void game::playGame() {


	//Main Game Loop
	while (!won) {
		if(done) {return;}

		unique_ptr<ducky> myDuck(new ducky());
		ducks.push_back(myDuck);

		glutKeyboardFunc(KeyboardInput);
		glutDisplayFunc(GameDisplay);
		glutMainLoop();

	}


}