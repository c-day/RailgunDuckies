#pragma once

#include <gl/freeglut.h>
#include <assert.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>

class balloon {
	private:
		float x, y, z;


		
	public:
		balloon();
		balloon(float x, float y, float z);
		void drawBalloon();
		void updateBalloon(float x, float y, float z);
		void drawBBalloon(double time);
		
};

