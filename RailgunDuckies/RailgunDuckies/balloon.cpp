#include <gl/freeglut.h>
#include "balloon.h"
#include <algorithm>
#include <cmath>
#include <iostream>


balloon::balloon() {

}


void balloon::drawBalloon() {
	GLfloat mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat mat_shininess[] = { 100 }; 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	long index = 0;
	
	GLfloat varray[4940];

	for (double cy = 1.0; cy >= -1.65; cy = cy - 0.1) {
		if (cy >= 0) {
			r = sqrt(1 - pow(cy, 2));
		} else {
			r = cos(cy);
		}
		for (double ang = 0; ang <= 360; ang = ang + 6) {
			double rads = 3.14159265/180*ang;

			varray[index] = r*cos(rads);
			++index;
			varray[index] = cy;
			++index;
			varray[index] = r*sin(rads);
			++index;
		}

	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 180, varray);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4940);
	glDisableClientState(GL_VERTEX_ARRAY);


	//WORKING CODE

	/*
	for (double cy = 1.0; cy >= -1.65; cy = cy - 0.1) {
		if (cy >= 0) {
			r = sqrt(1 - pow(cy, 2));
		} else {
			r = cos(cy);
		}

		slice1[index].x = r; 
		slice1[index].y = cy;
		slice1[index].z = 0;
		slice2[index].x = r*cos(0.01745);
		slice2[index].y = cy;
		slice2[index].z = r*sin(0.01745);
		++index;
	}
	
	for (int r = 0; r < 361; ++r) {
		glColor3d(1, 0, 0);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < 80; ++i) {
			glVertex3d(slice1[i].x, slice1[i].y, slice1[i].z);
			glVertex3d(slice2[i].x, slice2[i].y, slice2[i].z);
		}
		glEnd();
		glRotated(1, 0, 1, 0);
	}
	glTranslated(0, -1.6, 0);
	glutSolidSphere(0.06, 10, 10);
	glTranslated(0, -0.07, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.05, 0.09, 20, 20);
	glPopMatrix();
	*/
}
	

