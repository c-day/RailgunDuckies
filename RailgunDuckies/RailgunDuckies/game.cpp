#include "game.h"

using namespace std;

bool done;
int points[] = { 10, 20, 30, 40, 50 };

game::game() {
	won = false;
	myGun = new railGun();
	zclose = 25;
	zfar = 75;
	playerScore = 0;
	missed = 0;
	myDuck = new ducky();
	shot = false;
	hit = false;
	shootTime = 0; 
	
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
	this->myDuck->drawDuck();
	glPopMatrix();

	//Draws Gun
	myGun->drawGun();
	

}

void game::updateGame(float inTime) {
	//Create Balloons
	srand(unsigned int(time(NULL)));
	while (balloons.size() < 5) {
		float x, y, z;
		int p;
		z = (float) (this->zclose + (rand()%(this->zfar-this->zclose)));
		x = float(rand()%((int)(tan(.479966)*z)*2) - (int)(tan(.479966)*z));
		y = float(rand()%((int)(tan(.479966)*z)));
		p = rand()%5;
		balloons.push_back(balloon(x, y, z, points[p]));
	}
	if(!shot) {
		this->myDuck->updatePos(this->myGun->getChamber(), glm::vec3(this->myGun->getRot().y, this->myGun->getRot().x + 90, 0));
	} else if(shot && !hit) {
		this->myDuck->fly();
	}
}

railGun* game::getGun() {
	return myGun;
}

int game::getScore() {
	return playerScore;
}


void game::shootDuck(float launchVelocity) {
	this->myDuck->setTraj(launchVelocity * glm::normalize(this->myGun->getBvec()));
	shot = !shot;
	this->myGun->setMove(!this->myGun->getMove());
}

ducky* game::getDuck() {
	return this->myDuck;
}

bool game::getShot() {
	return this->shot;
}