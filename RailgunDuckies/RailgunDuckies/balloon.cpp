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
	glTranslated(0, 0.5, 0);
	balloon::topHalf();
	balloon::bottomHalf();
	glPopMatrix();

	glPopMatrix();
}

void balloon::topHalf() {
	
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
	/*int index = 0;
	for(double cy = 0; cy <= 1; cy=cy+.1) {
		double bound = 1 - pow(cy, 2);
		for(double cx = -bound; cy <=bound; cx=cx+.1) {
			double cz = sqrt(1-pow(cx, 2)-pow(cy, 2));
			vertices[index].x = cx;
			vertices[index+1].x = cx;
			vertices[index].y = cy;
			vertices[index+1].x = cy;
			vertices[index].z = cz;
			vertices[index+1].x = -cz;
			index=index+2;
		}		
	}

	for(int i = 0; i < sizeof(vertices); ++i) {
		glBegin(GL_QUADS);
		glVertex3d(vertices[i].x, vertices[i].y, vertices[i].z);
		glVertex3d(vertices[i+1].x, vertices[i+1].y, vertices[i+1].z);
		glVertex3d(vertices[i+2].x, vertices[i+2].y, vertices[i+2].z);
		glVertex3d(vertices[i+3].x, vertices[i+3].y, vertices[i+3].z);
	}
	*/
	

}

void balloon::bottomHalf() {

}