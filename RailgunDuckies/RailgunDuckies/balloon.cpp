#include <gl/freeglut.h>
#include "balloon.h"
#include <algorithm>
#include <cmath>


balloon::balloon() {
	x = 0;
	y = 0;
	z = 0;
	slices = 50;
	stacks = 50;
	
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
	for(int horCount=0; horCount<stacks; horCount++) {
		for(int vertCount=0; vertCount<slices; vertCount++) {
			cx = horCount;
			cy = sqrt((1-pow(x, 2)));
			cz = sqrt((1-pow(x, 2)));

			verticies[horCount][vertCount][0] = cx;
			verticies[horCount][vertCount][1] = cy;
			verticies[horCount][vertCount][2] = cz;
		}
	}

	for(int horCount=0; horCount<stacks; horCount++) {
		glBegin(GL_QUAD_STRIP);
		for(int vertCount=0; vertCount<slices; vertCount++) {
			glVertex3f(verticies[horCount][vertCount][0], verticies[horCount][vertCount][1], verticies[horCount][vertCount][2]);
		}
		glEnd();
	}
}

void balloon::bottomHalf() {

}