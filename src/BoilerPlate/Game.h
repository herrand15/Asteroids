#pragma once
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include "_vector2.h"
#include "asteroid.h"
#include "Player.h"
#include "Bullet.h"
#include <ctime>


class Game {
private:
	Player*							p1;
	std::vector<Bullet*>			bullets;
	std::vector<Bullet*>			activeBullets;
	std::vector<Asteroid*>			asteroids;
	int								width;
	int								height;
	float							playerActiveTime;
	float							playerDeadTime;
	int								score;
	int                             lives;
	int								wave;

	bool debugMode;
	bool isPlayerAlive;

public:
	Game();
	Game(int width_,int height_);
	bool CheckCollisionsWithBullets(Asteroid*);
	void CheckAllCollisions();
	Player* getPlayer();
	int getScore();
	
	int getPlayerStatus();
	void RestartGame();
	void drawPlayerLives();
	void showPlayerLives();
	void SpawnAsteroids();
	void ShotABullet();
	void AddAsteroid();
	void EliminateAsteroid();
	void SwitchDebugMode();
	void DrawCircles();
	void ResizeWidthAndHeight(int width_, int height_);


	void UpdateGame(float deltaTime);
	void RenderGame();

};

#endif // !GAME_H_INCLUDED

