#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
class railGun {

private:
	glm::vec3 pos;
	glm::vec3 rot;
	void drawCube(float d);
	void drawFace(float d);

public:
	railGun();
	void drawGun();
	void updateGunX(float rx);
	void updateGunY(float ry);
	void drawBGun(float time);
	glm::vec3 getRot();
};

