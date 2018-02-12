#include "Player.h"

Player::Player() {
	position = new Vector2(Vector2::Origin);
}

void Player::Move(Vector2& mov) {
	position->x += mov.x;
	position->y += mov.y;

	float x = position->x += mov.x;;
	float y = position->y += mov.y;;

	position->x = Warp(x, 1136/2, -1136/ 2);
	position->y = Warp(y, 640/ 2, -640/ 2);
}


float Player::Warp(float position, float maxP, float minP) {
	if (position < minP) {
		return maxP - (minP - position);
	}
	if (position > maxP) {
		return minP + (position - maxP);
	}
	return position;
}

void Player::setIsSpeedingUp() {
  isSpeedingUp = true;
}


void Player::Render() {
	glLoadIdentity();
	
	glTranslatef(position->x ,position->y, 0.0f);
	

	glBegin(GL_LINE_LOOP);
	glVertex2f(25.0, 25.0);
	glVertex2f(12.5, -12.5);
	glVertex2f(-12.5, -12.5);
	glVertex2f(-12.5, 12.5);
	glEnd();
	//Dibujar el fuego si la nave esta avanzando
	if (isSpeedingUp==true) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(-12.5, -12.5);
		glVertex2f(4.56, -12.5);
		glVertex2f(-3.27, -25.84);
		glVertex2f(-9.25, - 17.3);
		glVertex2f(-24.63, - 25.56);
		glVertex2f(-18.23, - 9.61);
		glVertex2f(-25.06, - 5.48);
		glVertex2f(-12.5, 3.06);
		isSpeedingUp = false;
		glEnd();

	}


}