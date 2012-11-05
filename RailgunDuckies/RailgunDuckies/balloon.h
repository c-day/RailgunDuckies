#pragma once

#include <gl/freeglut.h>
#include <vector>
#include <assert.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>

class balloon {
	private:
		glm::vec3 position;
		int points;
		static std::vector<glm::vec3> balVert;
		static std::vector<GLuint> balIndex;
		static std::vector<GLuint> balIndex2;

		
	public:
		balloon();
		balloon(float x, float y, float z, int p);
		void drawBalloon();
		void updateBalloon(float x, float y, float z);
		void drawBBalloon(double time);
		void setPoints(int p);
		int getPoints();
		glm::vec3 getBalPos();
		void destroy();
};