#pragma once

#include <GL/freeglut.h>
#include <vector>
#include <iostream>

#include "railGun.h"
#include "ducky.h"
#include "balloon.h"


class game {
private:
	bool won;
	std::vector<ducky> ducks;
	std::vector<balloon> balloons;
	std::vector<railGun> myGun;

public:
	game();
	void updateGame(float time);
	void drawScene(int width, int height);
	bool hasWon();
};
