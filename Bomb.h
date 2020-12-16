/*
 * Bomb.h
 *
 *  Created on: May 1, 2018
 *      Author: zubaria
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "Object.h"
#include "util.h"

class Bomb: public Object {
private:
	static const int existenceFrames = 50;
	int x_inc, y_inc;
	int framesToDisappear;
public:
	Bomb(int x = 0, int y = 0, int x_inc = 0, int y_inc = 0, double direction =
			0, double radius = 5, ColorNames color = RED);
	virtual ~Bomb();
	void draw();
	const Bomb& operator =(const Bomb& obj);
	virtual bool nextLocation();
	virtual int destroy();
};

#endif /* BOMB_H_ */
