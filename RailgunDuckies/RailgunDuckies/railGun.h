#ifndef RAILGUN_H
#define RAILGUN_H

class railGun {

private:
	double x, y, z, rx, ry;

public:
	railGun();
	void drawGun();
	void updateGun();
	void drawBGun(double time);

};

#endif