/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"

Board::Board() :
		score(0), lives(3), level(1), nAsteroids(0), asteroidInitialRadius(60), nAttackers(
				0), objects(NULL), attackers(NULL), ship(NULL) {
	startLevel();
}
void Board::startLevel() {
	InitRandomizer();
	deallocate();
	nAsteroids = 3 + level;
	nAttackers = 1 + level;
	objects = new Asteroid*[nAsteroids];
	attackers = new Attacker*[nAttackers];
	ship = new SpaceShip(WIDTH / 2, HEIGHT / 2);
	for (int i = 0; i < nAsteroids; i++) {
		int tempx, tempy;
		do {
			tempx = (GetRandInRange(0, WIDTH));
		} while (tempx > WIDTH / 2 - 100 && tempx < WIDTH / 2 + 100);
		do {
			tempy = (GetRandInRange(0, HEIGHT));
		} while (tempy > HEIGHT / 2 - 100 && tempy < HEIGHT / 2 + 100);
		objects[i] = new Asteroid(tempx, tempy,
				GetRandInRange(-100, 100) / float(GetRandInRange(1, 100)),
				asteroidInitialRadius, (ColorNames) GetRandInRange(2, 39),
				GetRandInRange(6, 10), 10);
	}
	for (int i = 0; i < nAttackers; i++) {
		int tempx, tempy;
		do {
			tempx = (GetRandInRange(0, WIDTH));
		} while (tempx > WIDTH / 2 - 100 && tempx < WIDTH / 2 + 100);
		do {
			tempy = (GetRandInRange(0, HEIGHT));
		} while (tempy > HEIGHT / 2 - 100 && tempy < HEIGHT / 2 + 100);
		attackers[i] = new Attacker(tempx, tempy,
				GetRandInRange(-100, 100) / float(GetRandInRange(1, 100)),
				GetRandInRange(20, 50), (ColorNames) GetRandInRange(2, 39), 0,
				GetRandInRange(0, 1));
	}
}
void Board::deallocate() {
	if (objects) {
		for (int i = 0; i < nAsteroids; i++) {
			if (objects[i]) {
				delete objects[i];
			}
		}
		delete[] objects;
	}
	if (attackers) {
		for (int i = 0; i < nAttackers; i++) {
			if (attackers[i]) {
				delete attackers[i];
			}
		}
		delete[] attackers;
	}
	if (ship) {
		delete ship;
	}
}
Board::~Board() {
	deallocate();
}

void Board::removeAttacker(int index) {
	Attacker** temp = new Attacker*[nAttackers - 1];
	int l = 0;	//index of temp being accessed
	for (int k = 0; k < nAttackers; k++) { //remove the object from the array
		if (index != k) {
			temp[l++] = attackers[k];
		} /*else {
		 delete attackers[k];
		 }*/
	}
	if (attackers) {
		delete[] attackers;
	}
	attackers = temp;
	nAttackers--;
}
void Board::removeAsteroid(int index, int score) {
	switch (score) {
	case 10: { //destroy the big asteroid and generate two complex asteroids of half the radius
		Asteroid** temp = new Asteroid*[nAsteroids + 1];
		int l = 0; //index of temp being accessed
		for (int k = 0; k < nAsteroids; k++) {
			if (index != k) {
				temp[l++] = objects[k];
			} else {
				for (int m = 0; m < 2; m++) {
					temp[l++] = new Asteroid((objects[k]->getLocation()).getX(),
							(objects[k]->getLocation()).getY(),
							GetRandInRange(-100, 100)
									/ float(GetRandInRange(1, 100)),
							asteroidInitialRadius / 2,
							(ColorNames) GetRandInRange(2, 39),
							GetRandInRange(6, 10), 20, /*1,*/1);
				}
				//delete objects[k];
			}
		}
		if (objects)
			delete[] objects;
		objects = temp;
		nAsteroids++;
		break;
	}
	case 20: { //destroy the complex asteroid and generate 4 simple asteroids of half the radius
		Asteroid** temp = new Asteroid*[nAsteroids + 3];
		int l = 0; //index of temp being accessed
		for (int k = 0; k < nAsteroids; k++) {
			if (index != k) {
				temp[l++] = objects[k];
			} else {
				for (int m = 0; m < 4; m++) {
					temp[l++] = new Asteroid((objects[k]->getLocation()).getX(),
							(objects[k]->getLocation()).getY(),
							GetRandInRange(-100, 100)
									/ float(GetRandInRange(1, 100)),
							asteroidInitialRadius / 4,
							(ColorNames) GetRandInRange(2, 39),
							GetRandInRange(6, 10), 40, 2);
				}
				//delete objects[k];
			}
		}
		if (objects)
			delete[] objects;
		objects = temp;
		nAsteroids += 3;
		break;
	}
	case 40: { //remove the asteroid from the array
		if (nAsteroids - 1 <= 0) {
			objects = NULL;
			nAsteroids = 0;
			break;
		}
		Asteroid** temp = new Asteroid*[nAsteroids - 1];
		int l = 0; //index of temp being accessed
		for (int k = 0; k < nAsteroids; k++) {
			if (index != k) {
				temp[l++] = objects[k];
			}
		}
		if (objects)
			delete[] objects;
		objects = temp;
		nAsteroids--;
		break;
	}
	}
}
void Board::draw() {
	for (int i = 0; i < nAsteroids; i++) {
		objects[i]->draw();
	}
	for (int i = 0; i < nAttackers; i++) {
		attackers[i]->draw();
	}
	if (lives > 0)
		ship->draw();
	else {
		string str = " GAME OVER";
		DrawString(510, 420, str, colors[DARK_SLATE_GRAY]);
	}
	string str = " LVL ";
	str += static_cast<char>(level + 48);
	DrawString(20, 780, str, colors[DARK_SLATE_GRAY]);
	DrawString(20, 740, "Score: " + Num2Str(score), colors[DARK_SLATE_GRAY]);
	for (int i = 0; i < lives; i++) {
		DrawTriangle(100 + i * 40, 780, 100 + i * 40 + /*width of triangle*/30,
				780, 100 + i * 40 + /*width of triangle*/30 / 2,
				780 + 30/*height of triangle*/, colors[DARK_SLATE_GRAY]);
	}
}
void Board::upKey() {
	ship->applyThrust();
}
void Board::downKey() {
	ship->stop();
}
void Board::rightKey() {
	ship->rotate(-10);
}
void Board::leftKey() {
	ship->rotate(10);
}
void Board::pressB() {
	ship->generateBomb();
}
int Board::getHeight() const {
	return HEIGHT;
}
int Board::getWidth() const {
	return WIDTH;
}
void Board::timerFunc() {
	if (!nAsteroids && !nAttackers) {
		level++;
		startLevel();
	}
	for (int i = 0; i < nAsteroids; i++) {
		objects[i]->nextLocation();
	}
	ship->nextLocation();
	for (int i = 0; i < nAttackers; i++) {
		attackers[i]->nextLocation();
	}
	restart_attacker: for (int i = 0; i < nAttackers; i++) {
		if (GetRandInRange(0, 1000) <= 25) //discharge bombs randomly in random directions(see generateBomb())
			attackers[i]->generateBomb();
		for (int j = 0; j < attackers[i]->getNBombs(); j++) {
			if (attackers[i]->isColliding(*(objects[j]))) {
				int tempScore = objects[j]->destroy();
				removeAsteroid(j, tempScore);
				score += tempScore;
			}
		}
		for (int j = 0; j < nAsteroids; j++) {
			if (attackers[i]->isColliding(*(objects[j]))) {
				score += attackers[i]->destroy();
				removeAttacker(i);
				int tempScore = objects[j]->destroy();
				removeAsteroid(j, tempScore);
				score += tempScore;
				goto restart_attacker;
			}
		}
		for (int j = 0; j < ship->getNBombs(); j++) {
			if ((*ship)[j].isColliding(*(objects[i]))) {
				score += objects[i]->destroy();
				removeAttacker(i);
				goto restart_attacker;
			}
		}
		if (nAttackers && ship->isColliding(*(objects[i]))) {
			lives--;
			delete ship;
			ship = new SpaceShip(510, 420);
			score += objects[i]->destroy();
			removeAttacker(i);
			glutPostRedisplay();
		}
	}
	restart_asteroid: for (int j = 0; j < nAsteroids; j++) {
		for (int i = 0; i < ship->getNBombs(); i++) {
			if ((*ship)[i].isColliding(*(objects[j]))) {
				int tempScore = objects[j]->destroy();
				removeAsteroid(j, tempScore);
				score += tempScore;
				goto restart_asteroid;
			}
		}
		if (nAsteroids && ship->isColliding(*(objects[j]))) {
			lives--;
			delete ship;
			ship = new SpaceShip(510, 420);
			int tempScore = objects[j]->destroy();
			removeAsteroid(j, tempScore);
			score += tempScore;
			glutPostRedisplay();
		}
	}
}
