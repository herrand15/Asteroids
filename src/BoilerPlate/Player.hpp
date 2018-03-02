#pragma once
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "_vector2.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "asteroid.hpp"



class Player : public Entity {
private:
	bool isSpeedingUp; 
	Vector2 shipPoints[4];
	Vector2 thrusterPoints[8];

public:

	Player(int width_, int height_);

	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void DrawShip();
	void DrawThruster();
	void DrawLines(Asteroid* asteroid_);

	void setIsSpeedingUp(); 
	void setPosition(Vector2);
	void Acceleration(Vector2 impulse);
	void StopThrust();
	Vector2 getPosition();
	float getAngle();

	void Update(float timeDiff);
	void Render();
	
	Bullet* shoot();
}; 


#endif // PLAYER_H_INCLUDED
