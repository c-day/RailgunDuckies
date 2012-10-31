#pragma once

#include <GL/freeglut.h>
#include <vector>
#include <time.h>
#include <iostream>


#include "railGun.h"
#include "ducky.h"
#include "balloon.h"



class game {
private:
	bool won;
	bool shot;
	bool hit;
	bool fired;
	bool stop;
	bool ENDGAME;
	std::vector<ducky> ducks;
	std::vector<balloon> balloons;
	railGun * myGun;
	int zclose, zfar;
	int playerScore;
	GLfloat currentMat[16];
	GLfloat trajectoryMat[16];
	float shootTime;
	ducky * myDuck;

	

public:
	game();
	void updateGame(float time);
	void drawScene(int width, int height);
	bool hasWon();
	railGun* getGun();
	int getScore();
	void shootDuck(float launchVelocity);
	int missed;
	ducky * getDuck();
	bool getShot();
	void resetDuck();
};
