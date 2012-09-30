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

}

void balloon::bottomHalf() {

}