#pragma once
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "_vector2.h"
#include <SDL_opengl.h>

	class Entity
	{

	public:
		//members
		Vector2 position;
		float Mass;
		int width;
		int height;
		int directionAngle;
		float radius;
		Vector2 velocity;
		float speed;

		//functions
		Entity();
		float Warp(float position, float maxP, float minP);
		void resizeWidthAndHeight(float Widht, float Height);
		Vector2 getPosition();
		float getRadius();
		void drawCircle();
		Entity(float width_, float height_);
		void Update(float timeDiff);
		
	
	};

#endif // ENTITY_H_INCLUDED