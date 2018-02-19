#pragma once
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "_vector2.h"
#include "Entity.h"
#include "SDLEvent.hpp"
#include <SDL2/SDL_opengl.h>

class Player : Entity {
private:
	bool isSpeedingUp; //check if the ship is moving
	Vector2 shipPoints[4];
	Vector2 thrusterPoints[8];


public:
	Player(float width_, float height_);

	void MoveForward();
	void RotateLeft();
	void RotateRight();
	float Warp(float x, float max, float min);
	void resizeWidthAndHeight(float Widht, float Height);
	void drawShip();
	void drawThruster();

	void setIsSpeedingUp();//setter 

	void Update();
	void Render();

}; 


#endif // PLAYER_H_INCLUDED
