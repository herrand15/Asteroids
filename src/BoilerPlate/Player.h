#pragma once
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "_vector2.h"
#include "Entity.h"
#include "Bullet.h"
#include "asteroid.h"
#include "SDLEvent.hpp"
#include <SDL2/SDL_opengl.h>


class Player : public Entity {
private:
	bool isSpeedingUp; //check if the ship is moving
	Vector2 shipPoints[4];
	Vector2 thrusterPoints[8];
	

public:

	Player(float width_, float height_);

	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void drawShip();
	void drawThruster();
	void drawLines(Asteroid* asteroid_);

	void setIsSpeedingUp(); 
	void acceleration(Vector2 impulse);
	void StopThrust();
	Vector2 getPosition();
	int getAngle();

	void Update(float timeDiff);
	void Render();
	
	

	//
	Bullet* shoot();
}; 


#endif // PLAYER_H_INCLUDED
