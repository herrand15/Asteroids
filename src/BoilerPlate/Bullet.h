
#pragma once
#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "_vector2.h"
#include "Entity.h"
#include <SDL2/SDL_opengl.h>


const int maxActiveTime = 70;
class Bullet : public Entity {
private:
	Vector2 bulletPoints[8];
	int shotAngle;	
	int currentActiveTime;



public:
	Bullet(int width_, int height_);
	bool IsActive();
	void Actualize(Vector2 impulse, Vector2 position, int angle);
	void Update(float timeDiff);
	void Render();
};

#endif // BULLET_H_INCLUDED

