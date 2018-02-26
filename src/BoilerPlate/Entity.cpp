#include "Entity.h"

	float Entity::Warp(float position, float maxP, float minP) {
		if (position < minP) {
			return maxP - (minP - position);
		}
		if (position > maxP) {
			return minP + (position - maxP);
		}
		return position;
	}

	void Entity::resizeWidthAndHeight(float Widht, float Height) {
		width = Widht;
		height = Height;
	}

	
	Entity::Entity() {};

	Entity::Entity(float width_, float height_) {
		width = width_;
		height = height_;
		directionAngle = 0.0f;
	}

	Vector2 Entity::getPosition() {
		return position;
	}

	float Entity::getRadius() {
		return radius;
	}


	void Entity::drawCircle() {

		int lines = 100;

		float twoPi = 2.0f * 3.141592653f;

		glLoadIdentity();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= lines; i++) {
			glVertex2f(
				position.x + (radius * cos(i *  twoPi / lines)),
				position.y + (radius* sin(i * twoPi / lines))
			);
		}
		glEnd();
	}


	void Entity::Update(float timeDiff) {
		
		position.x += velocity.x * timeDiff;
		position.y += velocity.y * timeDiff;

		
		position.x = Warp(position.x, width / 2, -width / 2);
		position.y = Warp(position.y, height / 2, -height / 2);


	}



