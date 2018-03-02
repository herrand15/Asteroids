#include "Saucer.hpp"

const int SAUCERANGLE = 180;
const int BULLETVELOCITY = 500.0;

Saucer::Saucer(int width_, int height_) {
	position = Vector2(0.0, 0.0/*(-320 +rand()+320)*/);


	saucerPoints[0] = Vector2(-3.0f, 1.00f);
	saucerPoints[1] = Vector2(-3.0f, 4.00f);
	saucerPoints[2] = Vector2(3.0f, 4.00f);
	saucerPoints[3] = Vector2(3.0f, 1.00f);
	saucerPoints[4] = Vector2(5.5f, -0.5f);
	saucerPoints[5] = Vector2(8.0f, -2.00f);
	saucerPoints[6] = Vector2(4.1f, -3.2f);
	saucerPoints[7] = Vector2(-4.0f, -3.3f);
	saucerPoints[8] = Vector2(-8.0f, -2.00f);
	saucerPoints[9] = Vector2(-5.5f, -0.5f);
	
	

	height = height_;
	width = width_;
	radius = 11.0;
	Mass = 1.5;

}

void Saucer::MoveSaucer(Vector2 impulse){

		velocity.x += (impulse.x / Mass) * cos(degreeToRadians(SAUCERANGLE));
		velocity.y += (impulse.y / Mass) * sin(degreeToRadians(SAUCERANGLE));
}

void Saucer::Render() {
	glLoadIdentity();

	glTranslatef(position.x, position.y, 0.0f);
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 10; i++) {
		glVertex2d(saucerPoints[i].x, saucerPoints[i].y);
	}
	glEnd();
}

void Saucer::Update(float timeDiff) {
	speed = velocity.calculateLength();
	int saucerSpeed = 10;

	position.x += saucerSpeed * cos(degreeToRadians(SAUCERANGLE));
	position.y +=  saucerSpeed * sin(degreeToRadians(SAUCERANGLE));

	speed = velocity.calculateLength();
	Entity::Update(timeDiff);


}


Bullet* Saucer::SaucerShot() {
	Bullet * Shot = new Bullet(width, height);
	Shot->Actualize(Vector2(BULLETVELOCITY, BULLETVELOCITY), position, SAUCERANGLE);
	return Shot;
}