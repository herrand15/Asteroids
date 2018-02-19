#include "Player.h"
#include "MathUtilities.h"

Player::Player(float width_, float height_) {
	position = new Vector2(Vector2::Origin);
	
	height = height_;
	width = width_;
	directionAngle = 0.0;


	shipPoints[0] = Vector2(25.0f, 25.0f);
	shipPoints[1] = Vector2(12.5f, -12.5f);
	shipPoints[2] = Vector2(-12.5f, -12.5f);
	shipPoints[3] = Vector2(-12.5f, 12.5f);

	thrusterPoints[0] = Vector2(-12.5f, -12.5f);
	thrusterPoints[1] = Vector2(4.56f, -12.5f);
	thrusterPoints[2] = Vector2(-3.27f, -25.84f);
	thrusterPoints[3] = Vector2(-9.25f, -17.3f);
	thrusterPoints[4] = Vector2(-24.63f, -25.56f);
	thrusterPoints[5] = Vector2(-18.23f, -9.61f);
	thrusterPoints[6] = Vector2(-25.06f, -5.48f);
	thrusterPoints[7] = Vector2(-12.5f, 3.06f);
	
}


void Player::MoveForward() {
	position->x += 8.0f * cos(degreeToRadians(directionAngle + 45));
	position->y += 8.0f * sin(degreeToRadians(directionAngle + 45));

	position->x = Warp(position->x, width/2, -width/2);
	position->y = Warp(position->y, height/2, -height/2);
}

void Player::RotateLeft() {
	directionAngle += degreeToRadians(300);
}

void Player::RotateRight() {
	directionAngle -= degreeToRadians(300);
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

void Player::resizeWidthAndHeight(float Widht, float Height) {
	width = Widht;
	height = Height;
}

void Player::setIsSpeedingUp() {
  isSpeedingUp = true;
}

void Player::drawShip() {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex2f(shipPoints[i].x, shipPoints[i].y);
	}
	glEnd();
}

void Player::drawThruster() {
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i< 8; i++) {
		glVertex2f(thrusterPoints[i].x, thrusterPoints[i].y);
	}
	isSpeedingUp = false;
	glEnd();

}


void Player::Render() {
	glLoadIdentity();

	glTranslatef(position->x ,position->y, 0.0f);
	glRotatef(directionAngle, 0.0, 0.0, 1.0);

	drawShip();
	//Dibujar el fuego si la nave esta avanzando
	if (isSpeedingUp==true) {
		drawThruster();
	}


}