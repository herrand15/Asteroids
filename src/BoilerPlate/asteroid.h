#pragma once
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "_vector2.h"
#include "Entity.h"
#include "SDLEvent.hpp"
#include <SDL2/SDL_opengl.h>

class Asteroid : Entity {
protected:
	Vector2 asteroidPoints[10];
	char size;


public:
	Asteroid(float height, float width);
	void move();
	void rotate(); 
	void drawAsteroid(char size);
	char getSize();
	void Update();
	void Render();


};












#endif // ASTEROID_H_INCLUDED
