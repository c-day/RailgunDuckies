#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>

class ducky {
private:
	glm::vec3 duckPos;
	glm::vec3 duckRot;
	GLfloat trajectory[16];
	bool beauty;
public:
	ducky();
	void drawDuck();
	void updatePos(float x, float y, float z, float rx, float ry);
	void drawBDuck(float time);
	glm::vec3 getDuckPos();
	glm::vec3 getDuckRot();
	void setTraj(GLfloat traj[]);
	GLfloat * getTraj();
};


