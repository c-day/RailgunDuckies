#ifndef GAME_H
#define GAME_H
#include <vector>
#include "balloon.h"
#include "ducky.h"


class game {
private:
	bool won;
	bool done;
	std::vector<ducky*> ducks;
	std::vector<balloon*> balloons;

public:
	game();
	void playGame();
	void d();
	void updatePos(double x, double y, double z, double rx, double ry);
	void drawScene();
};



#endif