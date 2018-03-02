#include "Entity.hpp"

	float Entity::Warp(float position, float maxP, float minP) {
		if (position < minP) {
			return maxP - (minP - position);
		}
		if (position > maxP) {
			return minP + (position - maxP);
		}
		return position;
	}

	void Entity::resizeWidthAndHeight(int Widht, int Height) {
		width = Widht;
		height = Height;
	}

	
	Entity::Entity() {};

	Entity::Entity(int width_, int height_) {
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


	void Entity::DrawCircle() {

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

		
		position.x = (float)Warp(position.x, (float)width / 2, (float)-width / 2);
		position.y = (float)Warp(position.y, (float)height / 2, (float)-height / 2);


	}



