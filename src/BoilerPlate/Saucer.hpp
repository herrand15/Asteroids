#pragma once
#pragma once
#ifndef SAUCER_H_INCLUDED
#define SAUCER_H_INCLUDED

#include "MathUtilities.hpp"
#include "_vector2.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "asteroid.hpp"



class Saucer : public Entity {
private:
	int width;
	int height;
	Vector2 saucerPoints[10];

public:

	Saucer(int width_, int height_);

	void MoveSaucer(Vector2);
	Bullet* SaucerShot();

	void setSaucerPosition(Vector2);
	Vector2 getSaucerPosition();

	void Update(float timeDiff);
	void Render();
};


#endif // SAUCER_H_INCLUDED
