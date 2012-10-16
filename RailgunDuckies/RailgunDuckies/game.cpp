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
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3d(0.2, 0.6, 1.0);

	glutSolidCube(50);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	
	ducks.push_back(ducky());
	ducks[ducks.size()-1].updatePos(0, -1, -2, 0, 90);
	


	//Draws All Ducks
	for(int i = 0; i < ducks.size(); i++) {
		ducks[i].drawDuck();
	}
//*
	myGun[0].updateGun(0, 0, 45);
	glPushMatrix();
	
	glTranslatef(0, -2, -2);
	myGun[0].drawGun();
	glPopMatrix();
//*/
	for (int i = 0; i < 10; i++){
	balloons.push_back(balloon());
	}
	//Draws All Balloons
	glPushMatrix();
	int tempX = (rand() % 20) - 10;
	int tempY =  5 + (rand() % 5);
	int tempZ = (rand() % 30) - 50;
	glTranslatef(tempX, tempY, tempZ);
	for(vector<balloon>::iterator iter = balloons.begin(); iter < balloons.end(); ++iter) {
		iter->drawBalloon();
	}
	glPopMatrix();
}

void game::updateGame(float time) {

}



