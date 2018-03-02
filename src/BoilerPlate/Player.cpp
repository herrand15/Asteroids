#include "Player.hpp"
#include "MathUtilities.hpp"


const float MAX_SPEED = 400;
const float FRICTION = 0.99f;
const float breakAway = 8.5f;
const float ROTATIONANGLE = 270;
const float BULLETVELOCITY = 500.0;
const int MINIMUNDISTANCEFORDEBUGLINE = 400;

Player::Player(int width_, int height_) {
	position = Vector2(Vector2::Origin);
	
	height = height_;
	width = width_;
	directionAngle = 0.0f;
	radius = 23.50;
	Mass = 1.0;
	

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

	Acceleration(Vector2(breakAway, breakAway));
}

void Player::RotateLeft() {
	directionAngle += degreeToRadians(ROTATIONANGLE);
}

void Player::RotateRight() {
	directionAngle -= degreeToRadians(ROTATIONANGLE);
}


void Player::setIsSpeedingUp() {
  isSpeedingUp = true;
}

void Player::setPosition(Vector2 pos) {
	position = pos;
}

void Player::DrawShip() {

    glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2f(shipPoints[i].x, shipPoints[i].y);
	}
	glEnd();
}

void Player::DrawThruster() {
	glColor3f(1.0, 0.5, 0.0);
	glBegin(GL_POLYGON);

	for (int i = 0; i< 8; i++) {
		glVertex2f(thrusterPoints[i].x, thrusterPoints[i].y);
	}
	glEnd();

}


void Player::Acceleration(Vector2 impulse) {
	velocity.x += (impulse.x / Mass) * cos(degreeToRadians(directionAngle+45) );
	velocity.y += (impulse.y / Mass) * sin(degreeToRadians(directionAngle+45) );
	
}


void Player::Render() {
	glLoadIdentity();

	glTranslatef(position.x ,position.y, 0.0f);
	glRotatef(directionAngle, 0.0, 0.0, 1.0);

	DrawShip();
	if (isSpeedingUp==true) {
		DrawThruster();
	}

}

Vector2 Player::getPosition() {
	return position;
}

float Player::getAngle() {
	return directionAngle;
}


void Player::StopThrust()
{
	isSpeedingUp = false;
}

void Player::Update(float timeDiff) {
	speed = velocity.calculateLength();

	if (speed > MAX_SPEED)
	{
		velocity.x = (velocity.x / speed) * MAX_SPEED;
		velocity.y = (velocity.y / speed) * MAX_SPEED;
	}

	Entity::Update(timeDiff);

	if (!isSpeedingUp) velocity =  velocity* FRICTION;

}

Bullet* Player::shoot() {
	Bullet * Shot = new Bullet(width,height);
	Shot->Actualize(Vector2(BULLETVELOCITY,BULLETVELOCITY), position, directionAngle+45);
	return Shot;
}


void Player::DrawLines(Asteroid* asteroid_) {
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	float distance = sqrt(((position.x - asteroid_->getPosition().x)*(position.x - asteroid_->getPosition().x)) + ((position.y - asteroid_->getPosition().y)*(position.y - asteroid_->getPosition().y)));

	if (distance < MINIMUNDISTANCEFORDEBUGLINE) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(position.x, position.y);
		glVertex2f(asteroid_->getPosition().x, asteroid_->getPosition().y);
		glEnd();
	}
}