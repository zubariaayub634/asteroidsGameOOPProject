/*
 * SpaceShip.cpp
 *
 *  Created on: May 3, 2018
 *      Author: zubaria
 */

#include "SpaceShip.h"

SpaceShip::SpaceShip(int x, int y, double direction, double radius,
		ColorNames color, int destructionScore, bool changeDirection,
		int thrustFrameCtr) :
		Attacker(x, y, direction, radius, DARK_SLATE_GRAY), thrustFrameCtr(
				thrustFrameCtr), vertical(true), x_inc(0), y_inc(X_INCREMENT) {
	vertices[0][0] = location.getX() - WIDTH / 2;
	vertices[1][0] = location.getY();
	vertices[0][1] = location.getX();
	vertices[1][1] = location.getY() + HEIGHT;
	vertices[0][2] = location.getX() + WIDTH / 2;
	vertices[1][2] = location.getY();
	calculateDirection();
	//cout << "Spaceship made\n";
}
void SpaceShip::draw() {
	DrawTriangle(vertices[0][0], vertices[1][0], vertices[0][1], vertices[1][1],
			vertices[0][2], vertices[1][2], colors[color]);
	for (int i = 0; i < nBombs; i++) {
		bombs[i].draw();
	}
}
SpaceShip::~SpaceShip() {
}
void SpaceShip::applyThrust() {
	thrustFrameCtr = THRUST_FRAMES;
}
bool SpaceShip::nextLocation() {
	if (thrustFrameCtr) {
		translate(x_inc, y_inc);
		thrustFrameCtr--;
	}
	for (int i = 0; i < nBombs; i++) {
		if (bombs[i].nextLocation()) {
			Bomb *temp = new Bomb[--nBombs];
			int k = 0;
			for (int j = 0; j <= nBombs; j++) {
				if (j != i)
					temp[k++] = bombs[j];
			}
			if (bombs)
				delete[] bombs;
			bombs = temp;
		}
	}
	return true;
}
void SpaceShip::translate(int changeInX, int changeInY) {
	location.setX(location.getX() + changeInX);
	location.setY(location.getY() + changeInY);
	for (int i = 0; i < 3; i++) {
		vertices[0][i] += changeInX;
		vertices[1][i] += changeInY;
		Point temp(0, 0);
		temp.withinScreen(vertices[0][i], 1020);
		temp.withinScreen(vertices[1][i], 840);
	}
}
void SpaceShip::stop() {
	thrustFrameCtr = 0;
}
void SpaceShip::rotate(double theeta) {
	angle += Deg2Rad(theeta);
	while (angle > M_PI) {
		angle -= 2 * M_PI;
		//cout << "loop1 entered\n";
	}
	while (angle < - M_PI) {
		angle += 2 * M_PI;
		//cout << "loop2 entered\n";
	}
	//cout << endl << "angle: " << setprecision(15) << angle << endl;
	double rotator[2][2] = { { cos(angle), -sin(angle) }, { sin(angle), cos(
			angle) } };
	int origin[2][3] = { { -WIDTH / 2, 0, WIDTH / 2 }, { 0, HEIGHT, 0 } }; //vertices translated to origin
	double resultant[2][3];
	for (int i = 0; i < 2; i++) { //rotating object at origin
		for (int j = 0; j < 3; j++) {
			resultant[i][j] = 0;
			for (int k = 0; k < 2; k++) {
				resultant[i][j] += rotator[i][k] * origin[k][j];
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[i][j] = resultant[i][j];
		}
	}
	if (angle > -0.05 && angle < 0.05) {
		vertical = true;
		//cout << "condition1 entered\n";
		x_inc = 0;
		y_inc = X_INCREMENT;
		direction = 0.01;
	} else if (angle == M_PI || angle == -M_PI) {
		//cout << "condition2 entered\n";
		vertical = true;
		x_inc = 0;
		y_inc = -X_INCREMENT;
		direction = 0.01;
	} else {
		vertical = false;
		x_inc = 10;
		y_inc = abs(vertices[1][1] * 10.0 / vertices[0][1]);
		//cout << "y_inc outside if: " << y_inc << endl;
		if (angle > 0 && angle <= M_PI / 2) {
			//	cout << "if1\n";
			x_inc *= -1;
		} else if (angle > M_PI / 2 && angle <= M_PI) {
			//	cout << "if2\n";
			x_inc *= -1;
			y_inc *= -1;
		} else if (angle > -M_PI / 2 && angle <= 0) {
			//	cout << "if3\n";
		} else if (angle > -M_PI && angle <= M_PI / 2) {
			//	cout << "if4\n";
			y_inc *= -1;
		}
		direction = float(vertices[1][1] - location.getY())
				/ float(vertices[0][1] - location.getX());
		//cout << "direction: " << direction << endl;
	}
	for (int i = 0; i < 3; i++) { //translating object back to given position
		vertices[0][i] += location.getX();
		vertices[1][i] += location.getY();
	}
}
void SpaceShip::calculateDirection() {
	if (vertices[0][1] - location.getX() == 0) {
		vertical = true;
	}
	direction = (float(vertices[1][0] - location.getY()))
			/ (float(vertices[0][0] - location.getX()));
	vertical = false;
}
void SpaceShip::generateBomb() {
	if (!allowBombLaunch)
		return;
	Bomb* temp = new Bomb[++nBombs];
	for (int i = 0; i < nBombs - 1; i++)
		temp[i] = bombs[i];
//deal with direction of bomb after rotation
	Bomb x(vertices[0][1], vertices[1][1], x_inc, y_inc, direction * 3, 5,
			color);
	temp[nBombs - 1] = x;
	if (bombs)
		delete[] bombs;
	bombs = temp;
}
bool SpaceShip::isColliding(Object& obj) {
	Point p1(vertices[0][0], vertices[1][0]);
	Point p2(vertices[0][1], vertices[1][1]);
	Point p3(vertices[0][2], vertices[1][2]);
	if (p1.distance(obj.getLocation()) <= obj.getRadius()
			|| p2.distance(obj.getLocation()) <= obj.getRadius()
			|| p3.distance(obj.getLocation()) <= obj.getRadius())
		return true;
	return false;
}
Bomb& SpaceShip::operator[](int index) {
	return bombs[index];
}
