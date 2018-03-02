#pragma once
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "_vector2.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "SDLEvent.h"
#include <SDL_opengl.h>

class Asteroid : public Entity {
private:
	Vector2 asteroidPoints[13];
	char size;
	int direction;
	bool collided;

public:
	Asteroid(int width_, int height_, char size_); 
	void DrawAsteroid();
	char getSize();
	bool checkCollision(Entity* gameEntity);
	void setSize(char size_);
	void setPosition(Vector2 pos);
	void Update(float timeDiff);
	void Render();


};

#endif // ASTEROID_H_INCLUDED
