#include "ducky.h"

		
//Constructor, pass location of duck
ducky::ducky() {
}

/*
Ducky draw function.  
This function will draw the duck using predefined GLUT shapes.  

-We first move to the ducks position on screen then set the ducks orientation
 accordingly.  
-The duck is then drawn outward from this point making this point the center of
 the duck body. 

*/
void ducky::drawDuck() {
GLfloat mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	

	//Store Modelview Matrix
	glPushMatrix();

	//Move to Object's Current Position
	glTranslated(this->duckPos.x, this->duckPos.y, this->duckPos.z);
		
	glRotated(this->duckRot.x, 1, 0, 0);
	glRotated(this->duckRot.y, 0, 1, 0);
	

	//Draw Body
	glPushMatrix();
	glScaled(1, 0.7, 0.7);
	glColor3d(1, 1, 0);
	glutSolidSphere(0.4, 50, 50);
	glPopMatrix();

	//Draw Head
	glPushMatrix();
	glTranslated(0.3, 0.7*0.4, 0);
	glScaled(1, 0.9, 0.9);
	glutSolidSphere(0.15, 20, 20);
	glPopMatrix();

	//Draw Left Wing
	glPushMatrix();
	glTranslated(0, 0, 0.4*0.7);
	glScaled(1, 0.4, 0.15);
	glColor3d(.8, .8, 0);
	glutSolidSphere(0.25, 30, 30);
	glPopMatrix();

	//Draw Right Wing
	glPushMatrix();
	glTranslated(0, 0, -0.4*0.7);
	glScaled(1, 0.4, 0.15);
	glColor3d(.8, .8, 0);
	glutSolidSphere(0.25, 30, 30);
	glPopMatrix();

	//Draw beak
	glPushMatrix();
	glTranslated(0.4, 0.7*0.4, 0);
	glRotated(90, 0, 1, 0);
	glScaled(1, 0.5, 1);
	glColor3d(1, 0.2, 0);
	glutSolidCone(0.1, 0.15, 20, 20);
	glPopMatrix();

	//Go back to the modelview matrix
	glPopMatrix();
}
	
/*
One of two updatePos methods.  This method will take individual components to
update the ducks position and orientation. 
*/
void ducky::updatePos(float xn, float yn, float zn, float rxn, float ryn) {
	this->duckPos.x = xn;
	this->duckPos.y = yn;
	this->duckPos.z = zn;
	this->duckRot.x = rxn;
	this->duckRot.y = ryn;
}

/*
Two of two updatePos methods.  This method takes a position and rotation 
vector to update the ducks position and orientation. 
*/
void ducky::updatePos(glm::vec3 position, glm::vec3 rotation) {
	this->duckPos = position;
	this->duckRot = rotation;
}

//Allows other classes to get the ducks position
glm::vec3 ducky::getDuckPos() {
	return this->duckPos;
}

//Allows other classes to get the ducks rotation
glm::vec3 ducky::getDuckRot() {
	return this->duckRot;
}

/*
Special draw method for drawing the duck in beauty mode.  This method takes 
the game time as an argument and uses it to control the ducks rotation.  The 
duck is only moved in the z direction so it remains centered on screen and 
appears large.  
*/
void ducky::drawBDuck(float time) {

	glPushMatrix();
	glTranslated(0,0,-2);
	glRotated((time/1000) * 30.0, 0.1, 1, 0);
	this->drawDuck();
	glPopMatrix();
}
/*
Detects if this duck has collided with a balloon, will destroy duck and balloon
on a yes.
*/
void collision() {

}

/*
Called when duck hits or misses a balloon. Will include a draw animation and 
finish with the deletion of the instance. NOTE: Smart Pointers may make this 
unnecessary. 
*/
void destroyDuck() {

}

/*
Set the trajectory of the duck based on the input vector.  This input vector
will be the vector along the barrel of the gun at time of launch. 
*/
void ducky::setTraj(glm::vec3 in) {
	this->launchVec = in;
}

//Allows other classes to get the trajectory of the duck. 
glm::vec3 ducky::getTraj() {
	return this->launchVec;
}

/*
This method is what makes the duck fly.  It will be called once every time
period of the game (.02 seconds) to update the ducks position.  The updated 
happen in two segments.  If the duck is on the barrel of the gun, we want it to
accelerate along the gun and not sink due to gravity.  Once the duck has 
cleared the barrel, we then apply physics to have the duck fly along a
projectile motion path.  This is done by moving the duck in x and z by the 
relative components and then moving in y by an adjusted factor to compensate 
for gravity. 
*/
void ducky::fly() {
	if (duckPos.z >= -6) {
		this->duckPos.x += (this->launchVec.x*.02f);
		this->duckPos.y += (this->launchVec.y*.02f);
		this->duckPos.z += (this->launchVec.z*.02f);
	} else {
		this->duckPos.x += (this->launchVec.x*.02f);
		this->launchVec.y -= .5f*32.2f*.0004f;
		this->duckPos.y += (this->launchVec.y*.02f);
		this->duckPos.z += (this->launchVec.z*.02f);
	}
}