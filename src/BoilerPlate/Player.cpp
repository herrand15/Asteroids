#include "Player.h"

Player::Player() {
	position = new Vector2(Vector2::Origin);
}

void Player::Move(Vector2& mov) {
	position->x += mov.x;
	position->y += mov.y;

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


}