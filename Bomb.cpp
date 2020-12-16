/*
 * Bomb.cpp
 *
 *  Created on: May 1, 2018
 *      Author: zubaria
 */

#include "Bomb.h"

Bomb::Bomb(int x, int y, int x_inc, int y_inc, double direction, double radius,
		ColorNames color) :
		Object(x, y, direction, radius, color), x_inc(x_inc), y_inc(y_inc), framesToDisappear(
				existenceFrames) {
}
Bomb::~Bomb() {
}
void Bomb::draw() {
	//if (framesToDisappear)
	DrawCircle(float(location.getX()), float(location.getY()), float(radius),
			colors[color]);
}
const Bomb& Bomb::operator =(const Bomb& obj) {
	if (this != &obj) {
		location.setX(obj.location.getX());
		location.setY(obj.location.getY());
		x_inc = obj.x_inc;
		y_inc = obj.y_inc;
		direction = obj.direction;
		color = obj.color;
		framesToDisappear = obj.framesToDisappear;
	}
	return *this;
}
bool Bomb::nextLocation() {
	location.setX(location.getX() + x_inc);
	location.setY(location.getY() + y_inc);
	framesToDisappear--;
	if (framesToDisappear <= 0) {
		return true;
	}
	return false;
}
int Bomb::destroy() {
	cout << "entered destroy of bomb\n";
	framesToDisappear = 0;
	cout << "set frames to 0\n";
	return destructionScore;
	cout << "after returning xD\n";
}
