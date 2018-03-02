#include "Game.hpp"
#include "TextRenderizing.hpp"

const char smalll = 's';
const char medium = 'm';
const char large = 'l';
const float timeUntillPlayerCanDieOrRespawn = 300;

Game::Game() {

}

Game::Game(int width_, int height_) {
	srand(time(NULL));
	p1 = new Player(width_, height_);
	wave = 1;
	for (int i =0 ; i < 4+wave; i++) {
		asteroids.push_back(new Asteroid(width_, height_, large));
		}
	userFeedBackMessages.Init();
	userFeedBackMessages = TextRenderizing(width, height);
	debugMode = false;
	height = height_;
	width = width_;
	playerActiveTime = 0;
	playerDeadTime = 0;
	score = 0;
	lives = 3;
	addALife = false;
	isPlayerAlive = true;
	pointsUntillAddingLife = 4500;
	getting4500MorePointsCounter = 0;

	SoundEffects = irrklang::createIrrKlangDevice();
	SoundEffects->setSoundVolume(1.0f);
}

bool Game::CheckCollisionsWithBullets(Asteroid* asteroid) {
	bool hasCollided = false;
	std::vector <Bullet*> aliveAsteroids;
	for (int i = 0; i < bullets.size(); i++) {
		if (asteroid->checkCollision(bullets[i])) {
			hasCollided = true;
			if(asteroid->getSize() ==smalll)score += 75;
			SoundEffects->play2D("bangSmall.wav");
		}
		else aliveAsteroids.push_back(bullets[i]);
	}
	bullets = aliveAsteroids;
	return hasCollided;
}


void Game::CheckAllCollisions() {
	if (!debugMode) {
		std::vector <Asteroid*> aliveAsteroids;
		for (int i = 0; i < asteroids.size(); i++) {
			if (CheckCollisionsWithBullets(asteroids[i])) {
				if (asteroids[i]->getSize() == large) {
					Asteroid * division1 = asteroids[i];
					score += 25;
					division1->setSize(medium);
					
					Asteroid *division2 = new Asteroid(width, height, medium);
					Vector2 pos = division1->getPosition();
					division2->setPosition(pos);

					aliveAsteroids.push_back(division1);
					aliveAsteroids.push_back(division2);
				}
				else if (asteroids[i]->getSize() == medium) {
					Asteroid *division1 = asteroids[i];
					score += 50;
					division1->setSize(smalll);
					Asteroid *division2 = new Asteroid(width, height, smalll);
					Vector2 pos = division1->getPosition();
					division2->setPosition(pos);

					aliveAsteroids.push_back(division1);
					aliveAsteroids.push_back(division2);
				}
			}
			else aliveAsteroids.push_back(asteroids[i]);

			if (asteroids[i]->checkCollision(p1) && playerActiveTime>timeUntillPlayerCanDieOrRespawn) {
				isPlayerAlive = false;
				SoundEffects->play2D("bangLarge.wav");
				playerActiveTime = 0;
				lives -= 1;
			}
		}
		asteroids = aliveAsteroids;
	}

}


Player* Game::getPlayer(){
	return p1;
}

int Game::getPlayerStatus() {
	return lives;
}

void Game::RestartGame() {
	isPlayerAlive = true;
	bullets.clear();
	asteroids.clear();
	activeBullets.clear();
	lives = 3;
	score = 0;
	wave = 1;
	pointsUntillAddingLife = 3000;

}

int Game::getScore(){
	return score;
}



void Game::DrawPlayerLives() {
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0 * 10, -1.7 * 10);
	glVertex2f(1.0 * 10, -1.0 * 10);
	glVertex2f(1.8 * 10, 0.0 * 10);
	glVertex2f(2.0 * 10, 0.6 * 10);
	glVertex2f(1.5 * 10, 1.5 * 10);
	glVertex2f(1.0 * 10, 1.8 * 10);
	glVertex2f(0.5 * 10, 1.65 * 10);
	glVertex2f(0.0 * 10, 1.1 * 10);
	glVertex2f(-0.5 * 10, 1.65 * 10);
	glVertex2f(-1.0 * 10, 1.8 * 10);
	glVertex2f(-1.5 * 10, 1.5 * 10);
	glVertex2f(-2.0 * 10, 0.6 * 10);
	glVertex2f(-1.8 * 10, 0.0 * 10);
	glVertex2f(-1.0 * 10, -1.0 * 10);
	glVertex2f(0.0 * 10, -1.7 * 10);
	glEnd();
}

void Game::showPlayerLives() {
	int distance = 0;
	for (int i = 0; i < lives; i++) {
		glLoadIdentity();
		glTranslatef((GLfloat)(width/2)-48+distance, (GLfloat)(height/2)-30, 0.0);
		DrawPlayerLives();
		distance -= 50;
	}
	
}


void Game::ShotABullet() {
	if (isPlayerAlive) {
		if (bullets.size() < 10) {
			bullets.push_back(p1->shoot());
			SoundEffects->play2D("Fire.wav");
		}
	}
}

void Game::AddAsteroid() {
	asteroids.push_back(new Asteroid(width, height, large));
} 

void Game::SpawnAsteroids() {
	for (int i = 0; i < 4 + wave; i++) {
		asteroids.push_back(new Asteroid(width, height, large));
	}
}

void Game::EliminateAsteroid() {
	if (asteroids.size()>0) {
		asteroids.pop_back();
	}
}


void Game::SwitchDebugMode() {
	if (debugMode == false) debugMode = true;
	else if (debugMode == true) debugMode = false;
}


void Game::UpdateGame(float deltaTime) {
	if (isPlayerAlive) {
		p1->Update(deltaTime);
	}
	if (asteroids.size() == 0) {
		playerActiveTime = 0;
		wave += 1;
		SpawnAsteroids();
	}


	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i]->Update(deltaTime);
	}

	std::vector <Bullet*> activeBullets;
	for (auto bullet : bullets) {
		bullet->Update(deltaTime);
		if (!bullet->IsActive()) activeBullets.push_back(bullet);
	}
	bullets = activeBullets;

	if (playerDeadTime > timeUntillPlayerCanDieOrRespawn && lives >0) {
		p1->setPosition(Vector2::Origin);
		isPlayerAlive = true;
		playerDeadTime = 0;
	}
	if (isPlayerAlive){
		playerActiveTime++;
	}
	else {
		playerDeadTime++;
	}

	
	if (score > pointsUntillAddingLife + (getting4500MorePointsCounter*4500)) {
		getting4500MorePointsCounter++;
		addALife = true;
		if (addALife = true) {
			lives++;
			SoundEffects->play2D("extraShip.wav");
		}
		addALife = false;
	}


}

void Game::DrawScore() {
	SDL_Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 0;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	userFeedBackMessages.RenderText(std::to_string(score), black, (float)(width / 2) - 148, (float)(height / 2) - 120);

}


void Game::DrawEndGameMessage() {
	SDL_Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 0;

	userFeedBackMessages.RenderText("GAME OVER", black, -100.0, -25.0);
	userFeedBackMessages.RenderText("Press R to play again   -  Press ESC to exit", black, -420.0, -100.0);

}






void Game::RenderGame() {
	if (isPlayerAlive) {
		p1->Render();
	}
	showPlayerLives();
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i]->Render();
	}
	for (auto bullet : bullets) bullet->Render();
	
}

void Game::DrawCircles() {
	if (debugMode ==true) {
		p1->DrawCircle();
		for (auto bullet : bullets) {
			bullet->DrawCircle();
		}
		for (int i = 0; i < asteroids.size(); i++) {
			asteroids[i]->DrawCircle();
			p1->DrawLines(asteroids[i]);
		}
	}

}


void Game::ResizeWidthAndHeight(int width_, int height_) {
	height = height_;
	width = width_;
	p1->resizeWidthAndHeight(width_,height_);
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i]->resizeWidthAndHeight(width_, height_);
	}

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->resizeWidthAndHeight(width_, height_);
	}

}
