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
	bool shot;
	bool hit;
	bool ENDGAME;
	bool automated;

	int totalHit;
	int zclose, zfar;
	int playerScore;
	int numBalloons;
	
	float shootTime;
	
	std::vector<balloon> balloons;
	railGun * myGun;
	ducky * myDuck;

public:
	game();

	void updateGame();
	void drawScene(int width, int height);
	void resetGame();
	void setAuto(bool in);	
	void shootDuck(float launchVelocity);
	void resetDuck();

	bool getShot();
	bool gameOver();
	bool getAuto();	
	
	int getScore();
	int missed;	

	railGun * getGun();
	ducky * getDuck();
	std::vector<balloon> getBalloons();
};
