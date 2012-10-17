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
	void updateGunX(float rx);
	void updateGunY(float ry);
	void drawBGun(float time);
	glm::vec3 getRot();
};

