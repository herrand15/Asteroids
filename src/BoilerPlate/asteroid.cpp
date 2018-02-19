#include "asteroid.h"
#include "MathUtilities.h"
using namespace std;
Asteroid::Asteroid(float height_, float width_) {
	position = new Vector2(Vector2::Origin);
	height = height_;
	width = width_;
	directionAngle = 0.0f;

	asteroidPoints[0] = Vector2(35.8f, 39.5f);
	asteroidPoints[1] = Vector2(0.0f,52.0f);
	asteroidPoints[2] = Vector2(-20.9f, 44.2f);
	asteroidPoints[3] = Vector2(-32.8f, 24.3f);
	asteroidPoints[4] = Vector2(-28.6f, 3.7f);
	asteroidPoints[5] = Vector2(-12.7f,-15.5f);
	asteroidPoints[6] = Vector2(20.0f, -20.0f);
	asteroidPoints[7] = Vector2(38.4f, -6.8f);
	asteroidPoints[8] = Vector2(33.4f, 9.1f);
	asteroidPoints[9] = Vector2(42.6f, 26.4f);
}

void Asteroid::rotate() {
	directionAngle += degreeToRadians(230);
}

void Asteroid::drawAsteroid(char size) {
	glBegin(GL_LINE_LOOP);
	switch (size) {
		//this switch will take a char; 's' will draw a small asteroid, 'm' a medium one and 'l' a large one
	case 's':
		for (int i = 0; i < 10; i++) {
			glVertex2f(asteroidPoints[i].x *0.7f, asteroidPoints[i].y *0.7f);
		}
		size = 's';
		break;
	case 'm':
		for (int i = 0; i < 10; i++) {
			glVertex2f(asteroidPoints[i].x , asteroidPoints[i].y );
		}
		size = 'm';
		break;
	case 'l':
		for (int i = 0; i < 10; i++) {
			glVertex2f(asteroidPoints[i].x *1.3f, asteroidPoints[i].y *1.3f);
		}
		size = 'l';
		break;
	}

	glEnd();
}

char Asteroid::getSize() {
	return size;
}

void Asteroid::Render() {
	glLoadIdentity();
	glTranslatef(position->x, position->y , 0.0);
	glRotatef(directionAngle, 0.0, 0.0, 1.0);
	drawAsteroid('l');

}