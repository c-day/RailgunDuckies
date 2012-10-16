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
	const float slices = 36;
	const int array_size = 972;
	glm::vec3 PositionData[array_size];
	glm::vec3 NormalArray[array_size];
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
		for (float rotAng = 10.0f; rotAng < 360.0f; rotAng += 360/slices) {
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
		
		
		if(i > 36) {

			glm::vec3 temp1 = glm::cross(PositionData[i-1], PositionData[i-37]);
			glm::vec3 temp2 = glm::cross(PositionData[i-37], PositionData[i-36]);
			glm::vec3 temp3 = glm::cross(PositionData[i-36], PositionData[i+1]);
			glm::vec3 temp4 = glm::cross(PositionData[i+1], PositionData[i+37]);
			glm::vec3 temp5 = glm::cross(PositionData[i+37], PositionData[i+36]);
			glm::vec3 temp6 = glm::cross(PositionData[i+36], PositionData[i-1]);

			NormalArray[i] = glm::normalize((temp1+temp2+temp3+temp4+temp5+temp6));

		}

	}



	glColor3d(1, 0, 0);
	glVertexPointer(3, GL_FLOAT, 0, PositionData);

	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_NORMAL_ARRAY);	

	glNormalPointer(GL_FLOAT, 0, NormalArray);
	glDrawElements(GL_TRIANGLES, 2808, GL_UNSIGNED_INT, IndexData);
	glDrawElements(GL_TRIANGLES, 2807, GL_UNSIGNED_INT, IndexData2);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glTranslated(0, -1.6, 0);
	glutSolidSphere(0.06, 10, 10);
	glTranslated(0, -0.07, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.05, 0.09, 20, 20);
	glPopMatrix();


	glPopMatrix();
	
}

void balloon::drawBBalloon(double time) {
	glPushMatrix();
	glTranslated(0, 0, -5);
	glRotated((time/1000) * 45.0, 0.1, 1, 0.1);
	this->drawBalloon();
	glPopMatrix();
}
	

