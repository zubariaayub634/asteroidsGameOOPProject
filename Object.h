/*
 * Object.h
 *
 *  Created on: Apr 29, 2018
 *      Author: zubaria
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Point.h"
#include "util.h"

class Object {
protected:
	const static int X_INCREMENT = 1;
	Point location;
	double direction;
	double radius;
	ColorNames color;
	int destructionScore;
	bool changeDirection; //indicates whether the direction of asteroid changes at intervals
public:
	Object(int x, int y, double direction, double radius, ColorNames color,
			int destructionScore = 0, bool changeDirection = 0);
	virtual ~Object();
	virtual bool nextLocation();
	virtual void draw()=0;
	bool isColliding(Object& obj);
	const Point& getLocation() const;
	double getRadius() const;
	virtual int destroy(); //returns destruction score
};

#endif /* OBJECT_H_ */
