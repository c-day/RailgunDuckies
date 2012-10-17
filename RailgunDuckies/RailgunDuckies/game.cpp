#include "game.h"


using namespace std;
bool done;


game::game() {
	won = false;
	this->myGun.push_back(railGun());
}

bool game::hasWon() {
	return won;
}


void game::drawScene(int width, int height) {

	//Draws Skybox
	glDisable(GL_LIGHTING);
	glColor3d(0.2, 0.6, 1.0);

	glutSolidCube(50);
	glEnable(GL_LIGHTING);


	//Draws All Ducks
	for(vector<ducky>::iterator iter = ducks.begin(); iter < ducks.end(); ++iter) {
		iter->drawDuck();
	}

	//Draws Gun
	myGun[0].drawGun();


	//Draws All Balloons
	for(vector<balloon>::iterator iter = balloons.begin(); iter < balloons.end(); ++iter) {
		iter->drawBalloon();
	}
}

void game::updateGame(float time) {

}

railGun game::getGun() {
	return myGun[0];
}



