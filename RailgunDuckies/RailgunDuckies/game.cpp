#include "game.h"


using namespace std;
bool done;


game::game() {
	won = false;
	myGun = new railGun();
	zclose = 25;
	zfar = 100;
	playerScore = 0;
	missed = 0;
	myDuck = new ducky();
	shot = false;
	hit = false;
}

bool game::hasWon() {
	return won;
}


void game::drawScene(int width, int height) {

	//Draws Skybox
	glDisable(GL_LIGHTING);
	glColor3d(0.2, 0.6, 1.0);
	glPushMatrix();
	glTranslatef(0, 0, -40);
	glutSolidCube(100);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glGetFloatv(GL_MODELVIEW_MATRIX, this->currentMat);
	
	//Draws All Balloons
	for(vector<balloon>::iterator iter = balloons.begin(); iter < balloons.end(); ++iter) {
		iter->drawBalloon();
	}

	//Draws The Duck
	glPushMatrix();
	if(!shot){
		this->myDuck->setTraj(this->myGun->getMat());
		this->myDuck->updatePos(0, 1.1, 1.35, 0, 90);
		this->myDuck->drawDuck();
	} else {
		this->myDuck->setTraj(this->myDuck->getTraj());
		this->myDuck->updatePos(0, 0, -(this->launchVel), 0, 0);
		myDuck->drawDuck();
	}
	glPopMatrix();
	//Draws Gun
	myGun->drawGun();
	

}

void game::updateGame(float inTime) {
	//Create Balloons
	srand(time(NULL));
	while (balloons.size() < 5) {
		float x, y, z;
		z = (float) (this->zclose + (rand()%(this->zfar-this->zclose)));
		x = rand()%((int)(tan(.479966)*z)*2) - (int)(tan(.479966)*z);
		y = rand()%((int)(tan(.479966)*z));
		balloons.push_back(balloon(x, y, z));
	}
	
	
}

railGun* game::getGun() {
	return myGun;
}

int game::getScore() {
	return playerScore;
}


void game::shootDuck(float launchVelocity) {
	this->myDuck->setTraj(myGun->getMat());
	shot = true;
	this->launchVel = launchVelocity;
}