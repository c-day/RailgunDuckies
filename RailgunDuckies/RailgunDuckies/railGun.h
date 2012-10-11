#pragma once

#include <gl/freeglut.h>

class railGun {

private:
	double x, y, z, rx, ry;

public:
	railGun();
	void drawGun();
	void updateGun();
	void drawBGun(double time);

};

