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
		double x, y, z;
		/*
		struct slice1 {
			double x; 
			double y;
			double z;
		};
		struct slice2 {
			double x;
			double y;
			double z;
		};
		struct slice2 slice2[80];
		struct slice1 slice1[80];
		*/


		
	public:
		balloon();
		void drawBalloon();
		void updateBalloon(float x, float y, float z);
		void drawBBalloon(double time);
		
};

