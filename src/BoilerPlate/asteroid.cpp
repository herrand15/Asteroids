#include "asteroid.hpp"
#include "MathUtilities.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;


Asteroid::Asteroid(int width_, int height_, char size_) {
	

	position = Vector2((rand() % width_)-width_, (rand() %height_)-height_);
	height = height_;
	width = width_;
	direction = rand() % 360;
	collided = false;
	size = size_;
	if (size == 's')
		radius = 13.3;
	if (size == 'm')
		radius = 27.55;
	if (size == 'l')
		radius = 47.5;


	asteroidPoints[0] = Vector2(-5.0f, 8.1f);
	asteroidPoints[1] = Vector2(-10.5f,3.9f);
	asteroidPoints[2] = Vector2(-11.2f, -0.6f);
	asteroidPoints[3] = Vector2(-7.8f, -2.1f);
	asteroidPoints[4] = Vector2(-10.0f, -5.0f);
	asteroidPoints[5] = Vector2(-4.9f,-9.2f);
	asteroidPoints[6] = Vector2(1.9f, -9.6f);
	asteroidPoints[7] = Vector2(5.7f, -8.1f);
	asteroidPoints[8] = Vector2(8.6f,-7.2f);
	asteroidPoints[9] = Vector2(8.4f, -4.3f);
	asteroidPoints[10] = Vector2(8.4f, -1.7f);
	asteroidPoints[11] = Vector2(9.8f, 3.0f);
	asteroidPoints[12] = Vector2(4.5f, 8.6f);
}



void Asteroid::drawAsteroid() {
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	switch (size) {
		//this switch will take a char; 's' will draw a small asteroid, 'm' a medium one and 'l' a large one
	case 's':
		for (int i = 0; i < 13; i++) {
			glVertex2f(asteroidPoints[i].x *1.4, asteroidPoints[i].y *1.4 );
		}
		Mass = 1.0;
		break;
	case 'm':
		for (int i = 0; i < 13; i++) {
			glVertex2f(asteroidPoints[i].x *2.9f , asteroidPoints[i].y *2.9f );
		}
		Mass = 1.5;
		break;
	case 'l':
		for (int i = 0; i < 13; i++) {
			glVertex2f(asteroidPoints[i].x *5.0f, asteroidPoints[i].y *5.0f);
		}
		Mass = 2.0;
		break;
	}
	glEnd();
}

char Asteroid::getSize() {
	return size;
}

void Asteroid::setSize(char size_) {
	size = size_;
}

void Asteroid::setPosition(Vector2 pos) {
	position = pos;
}


bool Asteroid::checkCollision(Entity* gameEntity) {
	if ((radius + gameEntity->getRadius()) < sqrt(((position.x - gameEntity->getPosition().x)*(position.x - gameEntity->getPosition().x)) + ((position.y - gameEntity->getPosition().y)*(position.y - gameEntity->getPosition().y)))) {
		collided = false;
		return false;
	}
	else{
		if (size == 'l' && gameEntity->getRadius()!=23.50) {
			radius = 27.55;
		}
		else if (size == 'm' && gameEntity->getRadius() != 23.50) {
			radius = 13.3;
		}
		collided = true;
		return true;
	}
}



void Asteroid::Update(float timeDiff)
{
	int currentSpeed;
	if (size == 's')
		currentSpeed = 3.2;
	if (size == 'm')
		currentSpeed = 3.0;
	if (size == 'l')
		currentSpeed = 2.0;
	
	position.x += currentSpeed * cos(degreeToRadians(direction));
	position.y += currentSpeed * sin(degreeToRadians(direction));

	position.x = Warp(position.x, width / 2, -width / 2);
	position.y = Warp(position.y, height / 2, -height / 2);

	speed = velocity.calculateLength();

	Entity::Update(timeDiff);
}

void Asteroid::Render() {
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0);
	drawAsteroid();
}