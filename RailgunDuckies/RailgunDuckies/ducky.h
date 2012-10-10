#ifndef DUCKY_H
#define DUCKY_H


class ducky {
private:
	double x, y, z, rx, ry, rz;

public:
	ducky();
	void drawDuck();
	void updatePos(double x, double y, double z, double rx, double ry);
};


#endif