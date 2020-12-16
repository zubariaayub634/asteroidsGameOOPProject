/*
 * SpaceShip.h
 *
 *  Created on: May 3, 2018
 *      Author: zubaria
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include "Attacker.h"
#include<cmath>
#include <iomanip>

#define M_PI 3.14152

class SpaceShip: public Attacker {
private:
	const static int HEIGHT = 70;
	const static int WIDTH = 50;
	const static int THRUST_FRAMES = 50;
	int thrustFrameCtr;
	int vertices[2][3];
	bool vertical;
	double angle;
	int x_inc;
	int y_inc;
public:
	SpaceShip(int x, int y, double direction = 0, double radius = 60,
			ColorNames color = RED, int destructionScore = 0,
			bool changeDirection = 1, int thrustFrameCtr = 0);
	virtual ~SpaceShip();
	void applyThrust();
	bool nextLocation();
	void rotate(double theeta);
	void draw();
	void translate(int changeInX, int changeInY);
	void generateBomb();
	void calculateDirection();
	void stop();
	bool isColliding(Object& obj);
	Bomb& operator[](int index);
};

#endif /* SPACESHIP_H_ */
