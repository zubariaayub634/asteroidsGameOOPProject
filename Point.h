/*
 * Point.h
 *
 *  Created on: Apr 29, 2018
 *      Author: zubaria
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
	int x, y;
	static const int SCREEN_WIDTH = 1020;
	static const int SCREEN_HEIGHT = 840;
public:
	Point(int a, int b);
	virtual ~Point();
	int getX();
	void setX(int a);
	int getY();
	int getX() const;
	int getY() const;
	void setY(int a);
	void withinScreen(int& a, int limit);
	const Point& operator =(const Point & obj);
	double distance(const Point& obj);
	//void display();
};

#endif /* POINT_H_ */
