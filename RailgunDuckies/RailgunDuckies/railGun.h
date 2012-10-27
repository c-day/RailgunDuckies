#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
class railGun {

private:
	glm::vec3 pos;
	glm::vec3 rot;
	GLfloat barrellMat[16];
	void drawCube(float d);
	void drawFace(float d);
	glm::vec3 chamber;
	glm::vec3 barrellVec;

public:
	railGun();
	void drawGun();
	void updateGunX(float rx);
	void updateGunY(float ry);
	void drawBGun(float time);
	glm::vec3 getBvec();
	glm::vec3 getChamber();
	glm::vec3 getRot();
	GLfloat * getMat();
	
};

