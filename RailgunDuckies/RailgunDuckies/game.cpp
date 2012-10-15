#include "game.h"


using namespace std;
bool done;


game::game() {
	won = false;
	done = false;
}

void KeyboardInput(int c, int x, int y)
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
	

}



