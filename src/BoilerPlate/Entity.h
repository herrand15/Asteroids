#pragma once
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "_vector2.h"


	class Entity
	{
	public:
		//members
		Vector2 * position;
		float Mass;
		float width;
		float height;
		float directionAngle;


		//functions
		Entity();
		Entity(float width_, float height_);
		void Update();
		void Render();
	
	};

#endif // ENTITY_H_INCLUDED