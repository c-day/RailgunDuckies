#include "railGun.h"


		
//Constructor
railGun::railGun() {
	this->pos.x = 0;
	this->pos.y = 0;
	this->pos.z = 0;
	this->rot.x = 0;
	this->rot.y = 0;
	this->rot.z = 0;
}

//Draw gun based on current gun coords
void railGun::drawGun() {

	GLfloat mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glPushMatrix();


	glTranslated(this->pos.x, this->pos.y, this->pos.z);
	glColor3d(0.5, 0.5, 0.5);

	//Draw Base
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, -2);
	glutSolidCone(1.5, 2, 50, 50);
	glPopMatrix();

	//Rotate Gun
	glRotatef(this->rot.y, 1, 0, 0);
	glRotatef(this->rot.x, 0, 1, 0);

	//Draw barrell
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(0, 0, -.25);
	glutSolidCylinder(0.125, 0.5, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.125, 0);
	glScaled(2, 1, 1);
	glutSolidCube(0.25);
	glPopMatrix();

	glTranslated(0, .5, 0);

	glPushMatrix();
	glTranslated(.375, .375, -1);
	glScaled(.25, .25, 6);
	glutSolidCube(0.9167);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.375, -.375, -1);
	glScaled(.25, .25, 6);
	glutSolidCube(0.9167);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.375, -.375, -1);
	glScaled(.25, .25, 6);
	glutSolidCube(0.9167);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.375, .375, -1);
	glScaled(.25, .25, 6);
	glutSolidCube(0.9167);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1.875);
	glScaled(1, 1,.25);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -3.875);
	glScaled(1, 1, .25);
	glutSolidCube(1);
	glPopMatrix();




	glPopMatrix();
}

void railGun::drawBGun(float time) {
	glPushMatrix();
	glTranslated(0, 0, -8);
	glRotated((time/1000) * 30.0, 0.1, 1, 0.1);
	this->drawGun();
	glPopMatrix();
}

void railGun::updateGunX(float rx) {
	this->rot.x = rx;
}
void railGun::updateGunY(float ry) {
	this->rot.y = ry;
}


glm::vec3 railGun::getRot() {
	return this->rot;
}