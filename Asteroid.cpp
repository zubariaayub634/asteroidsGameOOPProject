/*
 * Asteroid.cpp
 *
 *  Created on: Apr 29, 2018
 *      Author: zubaria
 */

#include "Asteroid.h"

int Asteroid::nAsteroid = 0;
Asteroid::Asteroid(int x, int y, double direction, double radius,
		ColorNames color, int corners, int destructionScore,/* int hitCount,*/
		bool changeDirection) :
		Object(x, y, direction, radius, color, destructionScore,
				changeDirection), corners(corners)/*, hitCount(hitCount)*/, AstId(
				++nAsteroid) {
}
void Asteroid::display() {
	cout << AstId << " Asteroid " << location.getX() << " " << location.getY()
			<< " " << " " << direction << " " << radius << " " << color << " "
			<< corners << " " << destructionScore << " " /*<< hitCount*/<< endl;
}
Asteroid::~Asteroid() {
}
void Asteroid::draw() {
	int ogr = 6, ogh = 7;

	glPushMatrix();
	float sx = (float) radius / ogr;
	//glTranslatef(x, y, 1);
	//glScalef(sx, 1, 1);

	// Draw Asteroid here
	const int nvertices = 722;
	GLfloat vertices[nvertices][2];
	float hdegree = M_PI / (corners / 2);
	float angle = 0;
	for (int i = 0; i < nvertices; ++i) {
		vertices[i][0] = radius * cos(angle);
		vertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}

	glColor3fv(colors[color]); // set the circle color
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(location.getX(), location.getY(), 0, 1);
	for (int i = 0; i < nvertices; ++i)
		glVertex4f(location.getX() + vertices[i][0],
				location.getY() + vertices[i][1], 0, 1);
	glEnd();

	glPopMatrix();

	/*int rndpoint = corners;
	 int npoints = MAX(4, rndpoint);
	 //cout << npoints << endl;
	 int dtheta = 360 / npoints;
	 // using the formula rcostheta and rsin theta;
	 float theta = GetRandInRange(0, dtheta);
	 int sx = location.getX() + radius * cos(Deg2Rad(theta)), sy =
	 location.getY() + radius * sin(Deg2Rad(theta));
	 int x1 = sx;
	 int y1 = sy;
	 int stheta = dtheta;
	 for (int i = 0; i < npoints - 1; ++i) {
	 theta = GetRandInRange(stheta, stheta + dtheta);
	 int x2 = location.getX() + radius * cos(Deg2Rad(theta)), y2 =
	 location.getY() + radius * sin(Deg2Rad(theta));
	 DrawLine(x1, y1, x2, y2, 10, colors[color]);
	 x1 = x2;
	 y1 = y2;
	 stheta += dtheta;
	 }
	 DrawLine(x1, y1, sx, sy, 10, colors[color]);*/
}
