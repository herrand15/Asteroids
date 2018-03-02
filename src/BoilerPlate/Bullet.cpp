#include "Bullet.hpp"
#include "MathUtilities.hpp"
#include <math.h>

Bullet::Bullet(int width_, int height_): Entity(width_,height_) {
	currentActiveTime = 0;

	radius = 3.0;
	Mass = 1.0f;  
	bulletPoints[0] = Vector2(-1.5f, 0.0f);
	bulletPoints[1] = Vector2(-1.0f, -1.0f);
	bulletPoints[2] = Vector2(0.0f, -1.4f);
	bulletPoints[3] = Vector2(1.0f, -1.0f);
	bulletPoints[4] = Vector2(1.5f, 0.0f);
	bulletPoints[5] = Vector2(1.1f, 1.3f);
	bulletPoints[6] = Vector2(0.0f, 1.6f);
	bulletPoints[7] = Vector2(-1.2f, 1.2f);

}



void Bullet::Actualize(Vector2 impulse, Vector2 position_, int angle) {
	directionAngle = angle;
	position = position_;

	float xvel = impulse.x * cos(degreeToRadians(directionAngle));
	float yvel = impulse.y * sin(degreeToRadians(directionAngle));
	
	velocity.x = (xvel / Mass);
	velocity.y = (yvel / Mass);

}

bool Bullet::IsActive() {
	return currentActiveTime >= maxActiveTime;
}

void Bullet::Update(float timeDiff) {
	currentActiveTime++;;

	Entity::Update(timeDiff);
}

void Bullet::Render() {
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 8; i++) {
		glVertex2d(bulletPoints[i].x, bulletPoints[i].y);
	}
	glEnd();
}

