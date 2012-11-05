#include "game.h"

using namespace std;

bool done;
int points[] = { 10, 20, 30, 40, 50 };

game::game() {
	this->won = false;
	this->myGun = new railGun();
	this->zclose = 25;
	this->zfar = 75;
	this->playerScore = 0;
	this->missed = 0;
	this->myDuck = new ducky();
	this->shot = false;
	this->hit = false;
	this->shootTime = 0; 
	this->stop = false;
	this->ENDGAME = false;
	
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
	glRotatef(-90, 1, 0, 0);
	glColor3d(0, 0.4, 0);
	glBegin(GL_QUADS);
	glVertex3f(-50, 100, -20);
	glVertex3f(50, 100, -20);
	glVertex3f(50, -40, -20);
	glVertex3f(-50, -40, -20);
	glEnd();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -49);
	
	glColor3d(0, .5, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-50, -20, 0);
	glVertex3f(-50, 50, 0);
	glVertex3f(50, 50, 0);
	glVertex3f(50, -20, 0);
	glEnd();

	glPopMatrix();
	glEnable(GL_LIGHTING);
	glGetFloatv(GL_MODELVIEW_MATRIX, this->currentMat);
	
	//Draws All Balloons
	for(vector<balloon>::iterator iter = this->balloons.begin(); iter < this->balloons.end(); ++iter) {
		iter->drawBalloon();
	}

	//Draws The Duck
	glPushMatrix();
	this->myDuck->drawDuck();
	glPopMatrix();

	//Draws Gun
	this->myGun->drawGun();
	

}

void game::updateGame(float inTime) {
//Create Balloons
srand(unsigned int(time(NULL)));

if(this->missed >= 3) {
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
			if(tempDist <= 1.25) {
				this->playerScore += this->balloons[i].getPoints();
				this->balloons[i].destroy();
				this->myGun->setMove(true);
				this->shot = false;
				break;
			} 			
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
	while (balloons.size() < 8) {
		float x, y, z;
		int p;
 		z = (float) (this->zclose + (rand()%(this->zfar-this->zclose)));
		x = float(rand()%((int)(tan(.479966)*z)*2) - (int)(tan(.479966)*z));
		y = float(rand()%((int)(tan(.479966)*z)));
		p = rand()%5;
		this->balloons.push_back(balloon(x, y, -z, points[p]));
	}


}

railGun* game::getGun() {
	return this->myGun;
}

int game::getScore() {
	return this->playerScore;
}


void game::shootDuck(float launchVelocity) {
	this->myDuck->setTraj(launchVelocity * glm::normalize(this->myGun->getBvec()));
	this->stop = false;
	this->shot = true;
	this->myGun->setMove(false);
}

ducky* game::getDuck() {
	return this->myDuck;
}

bool game::getShot() {
	return this->shot;
}

void game::resetDuck() {
	this->missed++;
	this->shot = false;
	this->myGun->setMove(true);
}

bool game::gameOver() {
	return this->ENDGAME;
}

void game::resetGame() {
	this->won = false;
	this->myGun = new railGun();
	this->zclose = 25;
	this->zfar = 75;
	this->playerScore = 0;
	this->missed = 0;
	this->myDuck = new ducky();
	this->shot = false;
	this->hit = false;
	this->shootTime = 0; 
	this->stop = false;
	this->ENDGAME = false;
	this->balloons.clear();
}