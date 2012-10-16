#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>

class ducky {
private:
	glm::vec3 pos;
	glm::vec3 rot;
public:
	ducky();
	void drawDuck();
	void updatePos(float x, float y, float z, float rx, float ry);
	void drawBDuck(float time);

};


