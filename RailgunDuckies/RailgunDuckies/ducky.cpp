#include <gl/freeglut.h>
#include "ducky.h"
#include <algorithm>

		
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
		GLfloat mat_ambient[] = { 1.0, 1.0, 0, 1.0 };
		GLfloat mat_diffuse[] = { 1.0, 1.0, 0, 1.0 };
		//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0 };
		//GLfloat mat_shininess[] = { 100 }; 
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

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

		glPopMatrix();

	}
	
	//Update duck position using GLM
	void ducky::updatePos(double xn, double yn, double zn, double rxn, double ryn) {
		this->x = xn;
		this->y = yn;
		this->z = zn;
		this->rx = rxn;
		this->ry = ryn;
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
	
