#pragma once
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "_vector2.hpp"
#include "IncludeSDL.hpp"

	class Entity
	{

	public:
		//members
		Vector2 position;
		float Mass;
		int width;
		int height;
		float directionAngle;
		float radius;
		Vector2 velocity;
		float speed;

		//functions
		Entity();
		float Warp(float position, float maxP, float minP);
		void resizeWidthAndHeight(int Widht, int Height);
		Vector2 getPosition();
		float getRadius();
		void DrawCircle();
		Entity(int width_, int height_);
		void Update(float timeDiff);
		
	
	};

#endif // ENTITY_H_INCLUDED