#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>

class railGun {

private:
	glm::vec3 pos;
	glm::vec3 rot;

public:
	railGun();
	void drawGun();
	void updateGun(float rx, float ry, float rz);
	void drawBGun(float time);

};

