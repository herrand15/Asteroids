#pragma once
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "_vector2.h"
#include <SDL2/SDL_opengl.h>

class Player {
public:
	Vector2* position;


	Player();
	void Move(Vector2& mov);
	void Update();
	void Render();

}; 


#endif // PLAYER_H_INCLUDED
