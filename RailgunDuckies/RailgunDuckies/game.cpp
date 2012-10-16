#include "game.h"


using namespace std;
bool done;


game::game() {
	won = false;
	done = false;
}


void game::drawScene(int width, int height) {
	//Draws Skybox
	glPushMatrix();

	glColor3d(0, 1, 0);

	glTranslated(0, 0, -20);
	glutSolidCube(21);

	glPopMatrix();
	
	glTranslated(0, -5, -10);
	ducks.push_back(new ducky());
	balloons.push_back(new balloon());

	//Draws All Ducks
	for(int i = 0; i < ducks.size(); i++) {
		ducks[i]->drawDuck();
	}

	glTranslated(0, 10, -15);
	//Draws All Balloons
	for(int i = 0; i < balloons.size(); i++) {
		balloons[i]->drawBalloon();
	}
}

void game::updateGame(float time) {

}



