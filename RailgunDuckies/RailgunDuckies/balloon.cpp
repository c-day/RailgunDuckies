#include "balloon.h"


using namespace std;

balloon::balloon() {
	this->x = this->y = this->z = 0.0f;
}

static const GLsizei VertexCount = 6; 
static const GLsizei VertexSize = 4;




float radians(float deg) {
	return 3.14159f/180.0f*deg;
}


void balloon::drawBalloon() {
	GLfloat mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glPushMatrix();

	int index = 0;
	const int stacks = 26;
	const int array_size = 1000;
	glm::vec3 PositionData[array_size];
	GLuint IndexData[3*array_size];
	GLuint IndexData2[3*array_size];
	float r = 0;
	

	for (float curY = 1.0; curY >= -1.65; curY -= 2.65/stacks) {
		assert(index < array_size);
		//Check Y position and determine function to control balloon radius
		if (curY >= 0) {
			r = sqrt(1 - pow(curY, 2));
		} else {
			r = cos(curY);
		}
		//store initial point at current y, radius, and z=0
		PositionData[index].y = curY;
		PositionData[index].x = r;
		PositionData[index].z = 0;
		index++;
		for (float rotAng = 10.0f; rotAng < 360.0f; rotAng += 10.0f) {
			//*
			float deltaX = cos(radians(rotAng));
			float deltaZ = sin(radians(rotAng));
			PositionData[index].x = r * deltaX;
			PositionData[index].y = curY;
			PositionData[index].z = r * deltaZ;
			//*/
			//PositionData[index] = glm::rotateY(PositionData[index-1], rotAng);
			index++;
		}

	}

	//Calculate the index arrays
	for (int i = 0; i < array_size; i++) {
		IndexData[3*i] = i;
		IndexData[(3*i)+1] = i+1;
		IndexData[(3*i)+2] = i+36;

		IndexData2[3*i] = i+1;
		IndexData2[(3*i)+1] = i+36;
		IndexData2[(3*i)+2] = i+37;
	}



	glColor3d(1, 0, 0);
	glVertexPointer(3, GL_FLOAT, 0, PositionData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 2808, GL_UNSIGNED_INT, IndexData);
	glDrawElements(GL_TRIANGLES, 2807, GL_UNSIGNED_INT, IndexData2);
	glDisableClientState(GL_VERTEX_ARRAY);


	/*
	GLfloat varray[4940];

	for (double cy = 1.0; cy >= -1.65; cy = cy - 0.1) {
		if (cy >= 0) {
			r = sqrt(1 - pow(cy, 2));
		} else {
			r = cos(cy);
		}
		for (double ang = 0; ang <= 360; ang = ang + 6) {
			double rads = 3.14159265/180*ang;

			varray[index] = r*cos(rads);
			++index;
			varray[index] = cy;
			++index;
			varray[index] = r*sin(rads);
			++index;
		}

	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 180, varray);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4940);
	glDisableClientState(GL_VERTEX_ARRAY);

	*/
	//WORKING CODE
	/*
	
	for (double cy = 1.0; cy >= -1.65; cy = cy - 0.1) {
		if (cy >= 0) {
			r = sqrt(1 - pow(cy, 2));
		} else {
			r = cos(cy);
		}

		slice1[index].x = r; 
		slice1[index].y = cy;
		slice1[index].z = 0;
		slice2[index].x = r*cos(0.01745);
		slice2[index].y = cy;
		slice2[index].z = r*sin(0.01745);
		++index;
	}
	
	for (int r = 0; r < 361; ++r) {
		glColor3d(1, 0, 0);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < 80; ++i) {
			glVertex3d(slice1[i].x, slice1[i].y, slice1[i].z);
			glVertex3d(slice2[i].x, slice2[i].y, slice2[i].z);
		}
		glEnd();
		glRotated(1, 0, 1, 0);
	}
	glTranslated(0, -1.6, 0);
	glutSolidSphere(0.06, 10, 10);
	glTranslated(0, -0.07, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.05, 0.09, 20, 20);
	glPopMatrix();

	*/
	glPopMatrix();
	
}

void balloon::drawBBalloon(double time) {
	glPushMatrix();
	glTranslated(0, 0, -5);
	glRotated((time/1000) * 45.0, 0.1, 1, 0.1);
	this->drawBalloon();
	glPopMatrix();
}
	

