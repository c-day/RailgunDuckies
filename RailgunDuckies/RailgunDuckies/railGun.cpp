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
	glRotatef(this->rot.x, 0, 1, 0);
	glRotatef(this->rot.y, 1, 0, 0);

	glGetFloatv(GL_MODELVIEW_MATRIX, barrellMat);

	//Draw barrell
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(0, 0, -.25);
	glutSolidCylinder(0.125, 0.5, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.125, 0);
	glScaled(2, 1, 1);
	drawCube(0.25);
	glPopMatrix();

	glTranslated(0, .5, 0);

	glPushMatrix();
	glTranslated(.375, .375, -1);
	glScaled(.25, .25, 6);
	drawCube(0.9167);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.375, -.375, -1);
	glScaled(.25, .25, 6);
	drawCube(0.9167);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.375, -.375, -1);
	glScaled(.25, .25, 6);
	drawCube(0.9167);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.375, .375, -1);
	glScaled(.25, .25, 6);
	drawCube(0.9167);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1.875);
	glScaled(1, 1,.25);
	drawCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -3.875);
	glScaled(1, 1, .25);
	drawCube(1);
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

GLfloat * railGun::getMat() {
	return barrellMat;
}

void railGun::drawCube(float d) {
	float r = d/2;
	glm::vec3 points[8];
	points[0] = (glm::vec3(-r, r, r));
	points[1] = (glm::vec3(r, r, r));
	points[2] = (glm::vec3(r, r, -r));
	points[3] = (glm::vec3(-r, r, -r));

	points[4] = (glm::vec3(-r, -r, r));
	points[5] = (glm::vec3(r, -r, r));
	points[6] = (glm::vec3(r, -r, -r));
	points[7] = (glm::vec3(-r, -r, -r));

	GLuint IndexData [24] = {0, 1, 2, 3, 3, 2, 6, 7, 7, 3, 0, 4, 4, 0, 1, 5, 5, 1, 2, 6, 6, 7, 4, 5};

	glVertexPointer(3, GL_FLOAT, 0, points);

	glEnableClientState(GL_VERTEX_ARRAY);	
	//glEnableClientState(GL_NORMAL_ARRAY);	

	//glNormalPointer(GL_FLOAT, 0, NormalArray);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, IndexData);

	//glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


}

void railGun::drawFace(float d) {
	float r = d/2;

	glBegin(GL_POLYGON);
	glVertex3f(-r, r, -r);
	glVertex3f(r, r, -r);
	glVertex3f(r, -r, -r);
	glVertex3f(-r, -r, -r);
	glEnd();
}