#include <gl/freeglut.h>
#include "balloon.h"
#include <algorithm>
#include <cmath>


balloon::balloon() {

}

void balloon::drawBalloon() {


	glPushMatrix();

	glTranslated(x, y, z);

	glPushMatrix();
	balloon::topHalf();
	balloon::bottomHalf();
	glPopMatrix();

	glPopMatrix();
}

void balloon::topHalf() {
	/*
	float vertices[10][16][3];
	int Latitudes =10;
	int Longitudes = 16;
	double M_PI = 3.14159265;

	for(int latCount=0; latCount<Latitudes; latCount++){ // along z axis
		for(int longCount=0; longCount<Longitudes; longCount++){ // x and y
			z = sin(M_PI*latCount/((float) (Latitudes-1))-M_PI/2.0f)/5;
			r = cos(M_PI*latCount/((float) (Latitudes-1))-M_PI/2.0f);
			x = (cos(M_PI*longCount/(float) (Longitudes-1))*r) /5;
			y = (sin(M_PI*longCount/(float) (Longitudes-1))*r *2) /5;

			vertices[latCount][longCount][0] = x; //x
			vertices[latCount][longCount][1] = y; //y
			vertices[latCount][longCount][2] = z; //z
		}
	}
	for(int latCount=0; latCount<Latitudes-1; latCount++){ // along z axis
		glBegin(GL_QUAD_STRIP);
        for(int longCount=0; longCount<=Longitudes; longCount++){
            glVertex3f(vertices[latCount][longCount][0], vertices[latCount][longCount][1], vertices[latCount][longCount][2]);
            glVertex3f(vertices[latCount+1][longCount][0], vertices[latCount+1][longCount][1], vertices[latCount+1][longCount][2]);
        }

		glEnd();
	 }
	*/
	int index = 0;
	
	for (double cy = -1.0; cy <= 1.0; cy = cy + 0.05) {
		if (cy >= 0) {
			r = sqrt(1 - pow(cy, 2));
		} else {
			r = cos(cy);
		}
		slice1[index].x = r; 
		slice1[index].y = cy;
		slice1[index].z = 0;
		slice2[index].x = r*cos(0.1745);
		slice2[index].y = cy;
		slice2[index].z = r*sin(0.1745);
		++index;
	}

	for (int r = 0; r < 37; ++r) {
		glColor3d(1, 0, 0);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(slice1[0].x, slice1[0].y, slice1[0].z);
		for (int i = 0; i < 41; ++i) {
			glVertex3d(slice1[i].x, slice1[i].y, slice1[i].z);
			glVertex3d(slice2[i].x, slice2[i].y, slice2[i].z);
		}
		glEnd();
		glRotated(10, 0, 1, 0);
	}

}
	
void balloon::bottomHalf() {

}
