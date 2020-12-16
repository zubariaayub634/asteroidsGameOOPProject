/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include "util.h"
#include "Asteroid.h"
#include "Bomb.h"
#include "SpaceShip.h"
//#define WITH_TEXTURES
using namespace std;

class Board {
private:
	const static int WIDTH = 1020;
	const static int HEIGHT = 840;
	int score;
	int lives;
	int level;
	int nAsteroids;
	int asteroidInitialRadius;
	int nAttackers;
	Asteroid** objects;
	Attacker** attackers;
	SpaceShip* ship;
public:
	Board();
	~Board();
	void deallocate();
	void removeAttacker(int index);
	void removeAsteroid(int index, int score);
	void draw();
	void upKey();
	void downKey();
	void rightKey();
	void leftKey();
	void pressB();
	void timerFunc();
	int getHeight() const;
	int getWidth() const;
	void startLevel();
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif
