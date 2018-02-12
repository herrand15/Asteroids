#pragma once
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "_vector2.h"
#include "SDLEvent.hpp"
#include <SDL2/SDL_opengl.h>

class Player {
private:
	Vector2* position;
	bool isSpeedingUp; //check is the ship is moving


public:
	Player();

	void Move(Vector2& mov);
	void MoveForward();
	void RotateLeft();
	void RotateRight();
	float Warp(float x, float max, float min);

	void setIsSpeedingUp();//setter 
	//se buscara una manera mas eficiente de manejar el thruster en el siguiente assignment

	void Update();
	void Render();

}; 


#endif // PLAYER_H_INCLUDED
