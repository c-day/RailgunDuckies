#pragma once

#include <GL/freeglut.h>
#include <vector>
#include <iostream>

#include "ducky.h"
#include "balloon.h"
#include "railGun.h"

class game {
private:
	bool won;
	bool done;
	std::vector<ducky*> ducks;
	std::vector<balloon*> balloons;

public:
	game();
	void updateGame(double time);
	void drawScene();
};
