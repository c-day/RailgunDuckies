#include "balloon.h"

using namespace std;

static const GLsizei VertexCount = 6; 
static const GLsizei VertexSize = 4;
const int stacks = 26;
const float slices = 36;
const int array_size = 972;



//Constuctor that puts the balloon at the origin. 
balloon::balloon() {
	this->position.x = this->position.y = this->position.z = 0.0;
}

/*
Constructor that will place the balloon at a given point in space, and
will assign the balloon a point value. 
*/
balloon::balloon(float x, float y, float z, int p) {
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->points = p;
}

//Converts degrees to radians for trig functions. 
float radians(float deg) {
	return 3.14159f/180.0f*deg;
}

/*
This function draws the balloon by computing vertices from mathematical 
functions.  The top half of the balloon is drawn and a hemisphere, and the 
bottom half of the balloon is drawn from a cosine function.  There is also 
few lines that will display the point value of each balloon hovering above
the balloon.  The vertices are stored in a vertex array and then a normal 
array is computed along side the vertex array.  This allows us to draw the
balloons with a vertex buffer.  
*/
void balloon::drawBalloon() {
	GLfloat mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	//Store modelview matrix
	glPushMatrix();

	//Move to the specified coordinates to draw the balloon at
	glTranslatef(this->position.x, this->position.y, -this->position.z);

	//store the matrix before displaying the point value
	glPushMatrix();
	char score_string[16];
	sprintf_s(score_string, "%d", this->points);

	glDisable(GL_LIGHTING);
	glTranslatef(-0.75, 1.5, -0.5);
	glScalef(0.01f, 0.01f, 1.0f);
	glColor3f(0, 0, 0);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *) score_string);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	int index = 0;
	float r = 0;

	glm::vec3 PositionData[array_size];
	glm::vec3 NormalArray[array_size];
	GLuint IndexData[3*array_size];
	GLuint IndexData2[3*array_size];
	/*
	To draw the balloon, navigate from the top to the bottom along the y-axis.  
	at each height, compute the radius according to the proper function(either 
	an arc or a cosine curve). After the proper radius is computed, rotate around
	the y-axis and store each point in the vertex array. 
	*/
	for (float curY = 1.0; curY >= -1.65; curY -= float(2.65/stacks)) {
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
			float deltaX = cos(radians(rotAng));
			float deltaZ = sin(radians(rotAng));
			PositionData[index].x = r * deltaX;
			PositionData[index].y = curY;
			PositionData[index].z = r * deltaZ;
			index++;
		}

	}

	/*
	To calculate the index arrays, choose the vertex at the index, move one to
	the right (i+1) and then move one below that(i+36).  Then for the other 
	triangle choose one to the right (i+1), one below (i+36), and one below and 
	to the right (i+37).  
	*/
	for (int i = 0; i < array_size; i++) {			
			IndexData[3*i] = i;
			IndexData[(3*i)+1] = i+1;
			IndexData[(3*i)+2] = i+36;
		

			IndexData2[3*i] = i+1;
			IndexData2[(3*i)+1] = i+36;
			IndexData2[(3*i)+2] = i+37;
		
		
		if(i > 36) {
			glm::vec3 temp1 = glm::normalize(glm::cross(PositionData[i-1], PositionData[i-37]));
			glm::vec3 temp2 = glm::normalize(glm::cross(PositionData[i-37], PositionData[i-36]));
			glm::vec3 temp3 = glm::normalize(glm::cross(PositionData[i-36], PositionData[i+1]));
			glm::vec3 temp4 = glm::normalize(glm::cross(PositionData[i+1], PositionData[i+37]));
			glm::vec3 temp5 = glm::normalize(glm::cross(PositionData[i+37], PositionData[i+36]));
			glm::vec3 temp6 = glm::normalize(glm::cross(PositionData[i+36], PositionData[i-1]));

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
	
}

/*
Allows for updating balloon position by specifying new coordinates. 
*/
void balloon::updateBalloon(float x, float y, float z) {
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;

}

/*
Special Draw function for beauty mode.  Translates only in the z direction
to keep the balloon centered on the screen.  The function takes in the game
time which is used to control the rotation of the balloon. 
*/
void balloon::drawBBalloon(double time) {
	glPushMatrix();
	glTranslated(0, 0, -5);
	glRotated((time/1000) * 45.0, 0.1, 1, 0.1);
	this->drawBalloon();
	glPopMatrix();
}

//Allow game class to set point value of balloon.
void balloon::setPoints(int p) {
	this->points = p;
}

//Allow game class to get the point value of a balloon. 
int balloon::getPoints() {
	return this->points;
}

glm::vec3 balloon::getBalPos() {
	return this->position;
}

void balloon::destroy() {
	this->position.z = 100;
}