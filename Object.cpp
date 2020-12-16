/*
 * Object.cpp
 *
 *  Created on: Apr 29, 2018
 *      Author: zubaria
 */

#include "Object.h"

Object::Object(int x, int y, double direction, double radius, ColorNames color,
		int destructionScore, bool changeDirection) :
		location(x, y), direction(direction), radius(radius), color(color), destructionScore(
				destructionScore), changeDirection(changeDirection) {
	while (direction == 0) {
		direction = GetRandInRange(-10, 10);
	}
}
Object::~Object() {
}
bool Object::nextLocation() {
	location.setX(location.getX() + X_INCREMENT);
	location.setY(location.getY() + direction * X_INCREMENT);
	return true; //dummy return
}
bool Object::isColliding(Object& obj) {
	if (location.distance(obj.location) <= (radius + obj.radius)) {
		return true;
	}
	return false;
}

const Point& Object::getLocation() const {
	return location;
}

double Object::getRadius() const {
	return radius;
}
int Object::destroy() {
	return destructionScore;
}
