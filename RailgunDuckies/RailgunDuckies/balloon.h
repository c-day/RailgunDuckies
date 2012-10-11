#pragma once

#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <cmath>

class balloon {
	private:
		double x, y, z, r;
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
		void drawBBalloon(double time);
		
};

