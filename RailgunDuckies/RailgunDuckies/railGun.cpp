#include "railGun.h"

/*
Set up the railgun to be drawn with a vertex array and vertex buffer. The
gun is a specified size and contains few elements so the index array can be
easily filled by hand.  
*/
std::vector<glm::vec3> railGun::gunVert;
GLuint railGun::gunIndex[] = {0, 1, 2, 3, 3, 2, 6, 7, 7, 3, 0, 4, 4, 0, 1, 5, 5, 1, 2, 6, 6, 7, 4, 5};
std::vector<glm::vec3> railGun::gunNorm;
		
//Constructor
railGun::railGun() {
	this->pos = glm::vec3(0, 0, 0);
	this->rot = glm::vec3(0, 0, 0);
	this->chamber = glm::vec3(0, 1.1, 1.35);
	this->barrellVec = glm::vec3(0, 0, -6);
	moveable = true;
}

/*
Draws the gun based on project spec.  The barrel has a length of 6 and
width and height of 1.  The pivot point of the gun is at the bottom of the 
barrel and 2 from the back.  At the pivot point we draw a base. 
*/
void railGun::drawGun() {

GLfloat mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

glPushMatrix();

	//move to the pivot point of the gun
	glTranslated(this->pos.x, this->pos.y, this->pos.z);
	glColor3d(0.5, 0.5, 0.5);

	//Draw Base
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, -2);
	glutSolidCone(1.5, 2, 50, 50);
	glPopMatrix();

	//Rotate Gun	

	glRotatef(this->rot.x, 0, 1, 0);
	glRotatef(this->rot.y, 1, 0, 0);

	/*
	store two vectors related to the barrel of the gun.  These will be used
	when the duck is fired and for the "first person" camera mode.  These 
	vectors go in the direction of the barrel and allow us to track its 
	position.  
	*/
	this->barrellVec = glm::rotateY(glm::vec3(0, 0, -6), this->rot.x);
	this->barrellVec = glm::rotateX(this->barrellVec, this->rot.y);
	this->chamber = glm::rotateY(glm::vec3(0, 1.1, 1.35), this->rot.x);
	this->chamber = glm::rotateX(this->chamber, this->rot.y);

	//Draw barrell
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(0, 0, -.25);
	glutSolidCylinder(0.125, 0.5, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.125, 0);
	glScaled(0.5, 0.249, 0.249);
	drawCube();
	glPopMatrix();

	glTranslated(0, .5, 0);

	glPushMatrix();
	glTranslatef(.375f, .375f, -1.0f);
	glScaled(.249, .249, 5.99);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslated(.375, -.375, -1);
	glScaled(.249, .249, 5.99);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.375, -.375, -1);
	glScaled(.249, .249, 5.99);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.375, .375, -1);
	glScaled(.249, .249, 5.99);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1.875);
	glScaled(1, 1,.25);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -3.875);
	glScaled(1, 1, .25);
	drawCube();
	glPopMatrix();

glPopMatrix();
}

/*
Special draw function for beauty mode.  This moves the gun to the center of 
the screen and to a nice distance away.  This will call drawGun and rotate 
the gun with the run time of the game to allow all sides to be visible. 
*/
void railGun::drawBGun(float time) {
	glPushMatrix();
	glTranslated(0, 0, -8);
	glRotated((time/1000) * 30.0, 0.1, 1, 0.1);
	this->drawGun();
	glPopMatrix();
}

/*
Update the rotation angle about the x axis given a new angle. 
*/
void railGun::updateGunX(float rx) {
	this->rot.x = rx;
}

/*
Update the rotation angle about the y axis given a new angle.
*/
void railGun::updateGunY(float ry) {
	this->rot.y = ry;
}

//returns guns current rotation
glm::vec3 railGun::getRot() {
	return this->rot;
}

//return the barrel vector of the gun
glm::vec3 railGun::getBvec() {
	return this->barrellVec;
}

//return a vector along the chamber of the gun
glm::vec3 railGun::getChamber() {
	return this->chamber;
}

/*
The main draw function of the gun.  This draws each part of the gun barrel
as a 1x1x1 cube using a vertex array and buffer and then the returned cube
can be scaled to desired dimensions. 
*/
void railGun::drawCube() {

	if (gunVert.size() == 0) {
		float r = 0.5 ;

		gunVert.push_back(glm::vec3(-r, r, r));
		gunVert.push_back(glm::vec3(r, r, r));
		gunVert.push_back(glm::vec3(r, r, -r));
		gunVert.push_back(glm::vec3(-r, r, -r));

		gunVert.push_back(glm::vec3(-r, -r, r));
		gunVert.push_back(glm::vec3(r, -r, r));
		gunVert.push_back(glm::vec3(r, -r, -r));
		gunVert.push_back(glm::vec3(-r, -r, -r));

		gunNorm.push_back(glm::vec3(-1, 0, 0));
		gunNorm.push_back(glm::vec3(1, 0, 0));
		gunNorm.push_back(glm::vec3(0, -1, 0));
		gunNorm.push_back(glm::vec3(0, 1, 0));
		gunNorm.push_back(glm::vec3(0, 0, -1));
		gunNorm.push_back(glm::vec3(0, 0, 1));
	}
	glVertexPointer(3, GL_FLOAT, 0, &gunVert[0]);

	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_NORMAL_ARRAY);	

	glNormalPointer(GL_FLOAT, 0, &gunNorm[0]);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, gunIndex);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


}

//set the guns ability to move.  
void railGun::setMove(bool in) {
	this->moveable = in;
}

//return the guns ability to move. 
bool railGun::getMove() {
	return this->moveable;
}