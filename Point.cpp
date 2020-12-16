/*
 * Point.cpp
 *
 *  Created on: Apr 29, 2018
 *      Author: zubaria
 */

#include "Point.h"

Point::Point(int a, int b) {
	setX(a);
	setY(b);
}
Point::~Point() {
}
int Point::getX() {
	return this->x;
}
int Point::getX() const {
	return this->x;
}
void Point::setX(int a) {
	withinScreen(a, SCREEN_WIDTH);
	this->x = a;
}
int Point::getY() {
	return this->y;
}
int Point::getY() const {
	return this->y;
}
void Point::setY(int a) {
	withinScreen(a, SCREEN_HEIGHT);
	this->y = a;
}
void Point::withinScreen(int& a, int limit) {
	if (a < -60)
		a = limit;
	if (a > limit)
		a = 0;
}
const Point& Point::operator =(const Point & obj) {
	if (this != &obj) {
		x = obj.x;
		y = obj.y;
	}
	return *this;
}
double Point::distance(const Point& obj) {
	return sqrt(double(pow(x - obj.x, 2) + pow(y - obj.y, 2)));
}
