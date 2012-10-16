#include "game.h"


using namespace std;
bool done;


game::game() {
	won = false;
}

bool game::hasWon() {
	return won;
}


void game::drawScene(int width, int height) {
	//Draws Skybox
	glPushMatrix();

	glColor3d(1, 1, 1);

	glutSolidCube(50);

	glPopMatrix();
	
	glTranslated(0, 0, -10);
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



