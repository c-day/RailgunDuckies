#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>

class ducky {
private:
	glm::vec3 duckPos;
	glm::vec3 duckRot;
	bool beauty;
	glm::vec3 launchVec;
	static GLuint display_list_handle;
public:
	ducky();
	void drawDuck();
	void updatePos(float x, float y, float z, float rx, float ry);
	void ducky::updatePos(glm::vec3 position, glm::vec3 rotation);
	void drawBDuck(float time);
	void fly();
	void setTraj(glm::vec3 in);
	void collision();
	
	glm::vec3 getDuckPos();
	glm::vec3 getDuckRot();
	glm::vec3 getTraj();
};

