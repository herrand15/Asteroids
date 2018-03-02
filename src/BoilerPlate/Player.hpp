#pragma once
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "_vector2.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "asteroid.hpp"



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
	void setPosition(Vector2);
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
