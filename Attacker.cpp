/*
 * Attacker.cpp
 *
 *  Created on: May 1, 2018
 *      Author: zubaria
 */

#include "Attacker.h"

Attacker::Attacker(int x, int y, double direction, double radius,
		ColorNames color, int destructionScore, bool changeDirection) :
		Object(x, y, direction, radius, color, destructionScore,
				changeDirection), bombs(NULL), nBombs(0), allowBombLaunch(1) {
}
Attacker::~Attacker() {
	if (bombs)
		delete[] bombs;
}
void Attacker::draw() {
	DrawRoundRect(float(location.getX()), float(location.getY()),
			float(radius + 20), float(radius), colors[color]);
	for (int i = 0; i < nBombs; i++) {
		bombs[i].draw();
	}
}
void Attacker::generateBomb() {
	if (!allowBombLaunch)
		return;
	Bomb* temp = new Bomb[++nBombs];
	for (int i = 0; i < nBombs - 1; i++)
		temp[i] = bombs[i];
	//deal with direction of bomb after rotation
	Bomb x(location.getX() + radius / 2 + 10, location.getY() + radius / 2,
			GetRandInRange(-100, 100) / float(GetRandInRange(1, 100)), 5,
			color);
	temp[nBombs - 1] = x;
	if (bombs)
		delete[] bombs;
	bombs = temp;
}
Bomb& Attacker::operator[](int index) {
	return bombs[index];
}

int Attacker::getNBombs() const {
	return nBombs;
	cout << "get n bomb\n";
}

bool Attacker::nextLocation() {
	Object::nextLocation();
	for (int i = 0; i < nBombs; i++) {
		if (bombs[i].nextLocation()) {
			Bomb * temp = new Bomb[nBombs - 1];
			int k = 0;
			for (int j = 0; j < nBombs; j++)
				if (i != j)
					temp[k++] = bombs[j];
			if (bombs)
				delete[] bombs;
			bombs = temp;
			nBombs--;
			i--;
		}
	}
	return true;
}
