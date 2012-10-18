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
	std::vector<ducky> ducks;
	std::vector<balloon> balloons;
	railGun * myGun;
	int zclose, zfar;
	int playerScore;
	
	ducky * myDuck;
	

public:
	game();
	void updateGame(float time);
	void drawScene(int width, int height);
	bool hasWon();
	railGun* getGun();
	int getScore();
	void shootDuck();
	int missed;
};
