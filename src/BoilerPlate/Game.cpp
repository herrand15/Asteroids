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
		asteroids.push_back(new Asteroid(width_, height_, 'l'));
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
	pointsUntillAddingLife = 2000;
	getting2000MorePointsCounter = 0;

	SoundEngine = irrklang::createIrrKlangDevice();
	SoundEngine->setSoundVolume(1.0f);
}

bool Game::CheckCollisionsWithBullets(Asteroid* asteroid) {
	bool hasCollided = false;
	std::vector <Bullet*> aliveAsteroids;
	for (int i = 0; i < bullets.size(); i++) {
		if (asteroid->checkCollision(bullets[i])) {
			hasCollided = true;
			if(asteroid->getSize()==smalll) score += 75;
			else if (asteroid->getSize() == medium) score += 50;
			else if (asteroid->getSize() == smalll) score += 25;
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
					division1->setSize(smalll);
					score += 50;
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



void Game::drawPlayerLives() {
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
		glTranslatef((width/2)-48+distance, (height/2)-30, 0.0);
		drawPlayerLives();
		distance -= 50;
	}
	
}


void Game::ShotABullet() {
	if (isPlayerAlive) {
		if (bullets.size() < 10) {
			bullets.push_back(p1->shoot());
			SoundEngine->play2D("Fire.wav");
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

	
	if (score > pointsUntillAddingLife + (getting2000MorePointsCounter*2000)) {
		getting2000MorePointsCounter++;
		addALife = true;
		if(addALife = true) lives++;
		addALife = false;
	}


}

void Game::drawScore() {
	SDL_Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 0;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	userFeedBackMessages.RenderText(std::to_string(score), black, (width / 2) - 148, (height / 2) - 120);

}


void Game::drawEndGameMessage() {
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
		p1->drawCircle();
		for (auto bullet : bullets) {
			bullet->drawCircle();
		}
		for (int i = 0; i < asteroids.size(); i++) {
			asteroids[i]->drawCircle();
			p1->drawLines(asteroids[i]);
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
