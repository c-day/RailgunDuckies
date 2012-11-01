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
	stop = false;
	ENDGAME = false;
	
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

if(missed >= 3) {
	this->ENDGAME = true; 
} else {
	if(!shot) {
		this->myDuck->updatePos(this->myGun->getChamber(), glm::vec3(this->myGun->getRot().y, this->myGun->getRot().x + 90, 0));
	} else if (shot)   {
		int start = balloons.size();
		for(int i = 0; i < start; ++i) {
			float tempDist = float(sqrt(  pow(this->myDuck->getDuckPos().x - this->balloons[i].getBalPos().x, 2)
										+ pow(this->myDuck->getDuckPos().y - this->balloons[i].getBalPos().y, 2)
										+ pow(this->myDuck->getDuckPos().z - this->balloons[i].getBalPos().z, 2)
										));
			std::cout << tempDist << endl;
			if(tempDist <= 5) {
				this->playerScore += this->balloons[i].getPoints();
				this->balloons[i].destroy();
				this->shot = false;
			} 
			std::cout << endl;
			std::cout << "LOOP" << endl;
		}
		if(-this->myDuck->getDuckPos().z < this->zfar && this->myDuck->getDuckPos().y > -5){
			this->myDuck->fly();
		} else {
			this->shot = false;
			this->myGun->setMove(true);
			this->missed++;
		}
	}

}
	while (balloons.size() < 1) {
		float x, y, z;
		int p;
 		z = (float) (this->zclose + (rand()%(this->zfar-this->zclose)));
		x = float(rand()%((int)(tan(.479966)*z)*2) - (int)(tan(.479966)*z));
		y = float(rand()%((int)(tan(.479966)*z)));
		p = rand()%5;
		balloons.push_back(balloon(x, y, z, points[p]));
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
	this->stop == false;
	shot = true;
	this->myGun->setMove(false);
}

ducky* game::getDuck() {
	return this->myDuck;
}

bool game::getShot() {
	return this->shot;
}

void game::resetDuck() {
	this->shot = false;
	this->myGun->setMove(true);
}