#pragma once
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "_vector2.h"
#include "Entity.h"
#include "Bullet.h"
#include "SDLEvent.hpp"
#include <SDL_opengl.h>

class Asteroid : public Entity {
private:
	Vector2 asteroidPoints[13];
	char size;
	int direction;
	bool collided;

public:
	Asteroid(int width_, int height_, char size_); 
	void drawAsteroid();
	char getSize();
	bool checkCollision(Entity* gameEntity);
	void setSize(char size_);
	void setPosition(Vector2 pos);
	void Update(float timeDiff);
	void Render();


};

#endif // ASTEROID_H_INCLUDED
