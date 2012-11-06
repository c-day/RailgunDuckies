#include "game.h"

using namespace std;

//define possible point values for each balloon
int points[] = { 10, 20, 30, 40, 50 };

/*
Constructor for the game.  Sets all used variable in the game to the 
correct initial values for game functionality. 
*/
game::game() {
	this->myGun = new railGun();
	this->zclose = 25;
	this->zfar = 75;
	this->playerScore = 0;
	this->missed = 0;
	this->myDuck = new ducky();
	this->shot = false;
	this->hit = false;
	this->shootTime = 0; 
	this->ENDGAME = false;
	this->automated = false;
	this->totalHit = 0;
	this->numBalloons = 5;
}

/*
Draws the scene of game.
	- Draw the skybox with a grass bottom and darker backend for depth perception
	- Draw each balloon in the balloon vector
	- Draw the railgun 
	- Draw the duck at its current position
*/
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

/*
Make the game playable.  If no balloons currently exist, the correct number 
of balloons will be created.  Each balloon has a position randomly generated
in a field  of view expanding from the gun to the back end of our skybox.  If
the balloons already exist then use the existing balloons and don't recompute. 

*/
void game::updateGame() {
	//Create Balloons
	srand(unsigned int(time(NULL)));
	
	while (int(balloons.size()) < numBalloons) {
		float x, y, z;
		int p;
		z = (float) (this->zclose + (rand()%(this->zfar-this->zclose)));
		x = float(rand()%((int)(tan(.479966)*z)*2) - (int)(tan(.479966)*z));
		y = float(rand()%((int)(tan(.479966)*z)));
		p = rand()%5;
		this->balloons.push_back(balloon(x, y, -z, points[p]));
	}
	
	/*
	Check the conditions that would end the game.  If the game has not ended 
	and there are still balloons to shoot at, let the user continue to play.
	If the user hits the ending condition (3 misses) then prompt for replay or
	quit.  If all balloons have been hit, generate a new set of balloons to 
	shoot at.
	*/
	if(this->missed >= 3 && !this->automated) {
		this->ENDGAME = true;
	} else if (this->totalHit == numBalloons) {
		this->balloons.clear();
		this->totalHit = 0;
	} else {

		/*
		The game is playable at this stage.  If the duck has not been shot,
		place the duck on the gun in the ready to shoot position.  Once the 
		duck is shot, get the launch vector from the position of the gun and 
		move the duck along that vector in time and adjust the position to 
		follow gravity and give the duck a ballistic flight path.
		*/

		if(!shot) {
			this->myDuck->updatePos(this->myGun->getChamber(), glm::vec3(this->myGun->getRot().y, this->myGun->getRot().x + 90, 0));
		} else if (shot)   {
			int start = balloons.size();
			for(int i = 0; i < start; ++i) {
				float tempDist = float(sqrt(  pow(this->myDuck->getDuckPos().x - this->balloons[i].getBalPos().x, 2)
					+ pow(this->myDuck->getDuckPos().y - this->balloons[i].getBalPos().y, 2)
					+ pow(this->myDuck->getDuckPos().z - this->balloons[i].getBalPos().z, 2)
					));

				/*
				Check the duck against each balloon and compare the bounding
				spheres for intersection to determine if a balloon will be hit.
				If the balloon is hit, destroy the balloon and make the duck 
				shootable again. 
				*/

				if(tempDist <= 1.3) {
					this->playerScore += this->balloons[i].getPoints();
					this->balloons[i].destroy();
					this->myGun->setMove(true);
					this->shot = false;
					this->totalHit++;
					break;
				} 			
			}

			/*
			Monitor the ducks flight and destroy the duck if it will not hit a 
			balloon allow the user to fire again.  
			*/
			if(-this->myDuck->getDuckPos().z < this->zfar && this->myDuck->getDuckPos().y > -5){
				this->myDuck->fly();
			} else {
				this->shot = false;
				this->myGun->setMove(true);
				this->missed++;
			}
		}

	}

}

//return a pointer to the current gun
railGun* game::getGun() {
	return this->myGun;
}

//return the players score
int game::getScore() {
	return this->playerScore;
}

/*
Shoot the duck with projectile motion.  
	- Get the launch vector from the gun at time of launch
	- Set the status of the duck to shot
	- Disable the gun from moving while duck in flight
*/
void game::shootDuck(float launchVelocity) {
	this->myDuck->setTraj(launchVelocity * glm::normalize(this->myGun->getBvec()));
	this->shot = true;
	this->myGun->setMove(false);
}

//return a pointer to the current duck
ducky* game::getDuck() {
	return this->myDuck;
}

//return the ducks flight status
bool game::getShot() {
	return this->shot;
}

//reset the duck and increment miss. Also makes the gun movable. 
void game::resetDuck() {
	this->missed++;
	this->shot = false;
	this->myGun->setMove(true);
}

//return the status of the game. 
bool game::gameOver() {
	return this->ENDGAME;
}

/*
reset the entire game.  reset all values to initial game status, delete
the pointer to the current gun and create a new one.  delete the pointer 
to the current duck and make a new one. 
*/
void game::resetGame() {
	delete myGun;
	this->myGun = new railGun();
	this->zclose = 25;
	this->zfar = 75;
	this->playerScore = 0;
	this->missed = 0;
	delete myDuck;
	this->myDuck = new ducky();
	this->shot = false;
	this->hit = false;
	this->shootTime = 0; 
	this->ENDGAME = false;
	this->balloons.clear();
	this->automated = false;
	this->totalHit = 0;
}

//allow others to automate the game. 
void game::setAuto(bool in) {
	this->automated = in;
}

//return if the game is automated
bool game::getAuto() {
	return this->automated;
}

std::vector<balloon> game::getBalloons() {
	return this->balloons;
}