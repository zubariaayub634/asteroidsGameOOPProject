/*
 * Attacker.h
 *
 *  Created on: May 1, 2018
 *      Author: zubaria
 */

#ifndef ATTACKER_H_
#define ATTACKER_H_

#include "Bomb.h"

class Attacker: public Object {
protected:
	Bomb* bombs;
	int nBombs;
	bool allowBombLaunch;
public:
	Attacker(int x, int y, double direction = 0, double radius = 0,
			ColorNames color = MAROON, int destructionScore = 0,
			bool changeDirection = 0);
	virtual ~Attacker();
	virtual void draw();
	void generateBomb();
	bool nextLocation();
	Bomb& operator[](int index);
	int getNBombs() const;
};

#endif /* ATTACKER_H_ */
