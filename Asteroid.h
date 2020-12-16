/*
 * Asteroid.h
 *
 *  Created on: Apr 29, 2018
 *      Author: zubaria
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Object.h"

class Asteroid: public Object {
private:
	int corners;
	static int nAsteroid;
	int AstId;
	//int hitCount;
	//bool changeDirection is 0 for simple asteroid and 1 for complex asteroid
public:
	Asteroid(int x, int y, double direction, double radius, ColorNames color,
			int corners, int destructionScore/*, int hitCount = 0*/,
			bool changeDirection = 0);
	virtual ~Asteroid();
	virtual void draw();
	void display();
};

#endif /* ASTEROID_H_ */
