#include <gl/freeglut.h>
#include "ducky.h"
#include <algorithm>

		


	
	// std::unique_ptr<GLUquadric> q(gluNewQuadric());
	//Constructor, pass location of duck
	ducky::ducky() {
		x = 0;
		y = 0;
		z = 0;
		rx = 0;
		ry = 0;
	}

	//Draw duck based on current duck coords
	void ducky::drawDuck() {

		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 50.0 }; 
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		//Store Modelview Matrix
		glPushMatrix();
		
		//Move to Object's Current Position
		glTranslated(x, y, z);
		glRotated(rx, 1, 0, 0);
		glRotated(ry, 0, 1, 0);

		//Draw Body
		glPushMatrix();
		glScaled(1, 0.7, 0.7);
		glColor3d(1, 1, 0);
		glutSolidSphere(0.4, 30, 30);
		//gluSphere(q, 0.4, 30, 30);
		glPopMatrix();

		//Draw Head
		glPushMatrix();
		glTranslated(0.3, 0.7*0.4, 0);
		glScaled(1, 0.9, 0.9);
		//gluSphere(q, 0.15, 10, 10);
		glutSolidSphere(0.15, 10, 10);
		glPopMatrix();

		//Draw Left Wing
		glPushMatrix();
		glTranslated(0, 0, 0.4*0.7);
		glScaled(1, 0.4, 0.15);
		glColor3d(.8, .8, 0);
		//gluSphere(q, 0.25, 20, 20);
		glutSolidSphere(0.25, 20, 20);
		glPopMatrix();

		//Draw Right Wing
		glPushMatrix();
		glTranslated(0, 0, -0.4*0.7);
		glScaled(1, 0.4, 0.15);
		glColor3d(.8, .8, 0);
		//gluSphere(q, 0.25, 20, 20);
		glutSolidSphere(0.25, 20, 20);
		glPopMatrix();

		//Draw beak
		glPushMatrix();
		glTranslated(0.4, 0.7*0.4, 0);
		glRotated(90, 0, 1, 0);
		glScaled(1, 0.5, 1);
		glColor3d(1, 0.2, 0);
		//gluCylinder(q, 0.1, 0, .15, 10, 10);
		glutSolidCone(0.1, 0.15, 10, 10);
		glPopMatrix();

		glPopMatrix();

	}
	
	//Update duck position using GLM
	void ducky::updatePos(double xn, double yn, double zn, double rx, double ry) {
		x = xn;
		y = yn;
		z = zn;
		rx = rx;
		ry = ry;
	}

	/*Detects if this duck has collided with a
	  balloon, will destroy duck and balloon
	  on a yes.*/
	//void collision(balloon * balloons[]) {

	//}

	/*Called when duck hits or misses a balloon.
	  Will include a draw animation and finish with
	  the deletion of the instance. NOTE: Smart
	  Pointers may make this unnecessary*/
	void destroyDuck() {

	}
	
