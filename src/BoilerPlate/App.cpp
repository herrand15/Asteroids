#include "App.hpp"
#include <iostream>
#include <algorithm>
#include "ColorRepresentation.h"
// OpenGL includes
#include <SDL2/SDL_opengl.h>

#include "_vector2.h"
//#include <ctime>

namespace Engine
{

	const float maxFrames = 20;
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
	{
		
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();

		upArrow = false;
		leftArrow = false;
		rightArrow = false;
		spaceBar = false;
		debugMode = false;
		showFrame = false;
		large = 'l';
		smalll = 's';
		medium = 'm';
		//srand(time(NULL));

		p1 = new Player(m_width, m_height);
		asteroids.push_back(new Asteroid(m_width, m_height, large));

		
		for (int i = 0; i < maxFrames; i++) {
			frames[i] = Vector2((float)i, 0.0f);
		}
		framePosition = 0;
		frameDeltaTime = DESIRED_FRAME_RATE;
		
	}



	
	App::~App()
	{
		CleanupSDL();
	}

	void App::Execute()
	{
		if (m_state != GameState::INIT_SUCCESSFUL)
		{
			std::cerr << "Game INIT was not successful." << std::endl; 
			return;
		}

		m_state = GameState::RUNNING;

		SDL_Event event;
		while (m_state == GameState::RUNNING)
		{
			// Input polling
			//
			while (SDL_PollEvent(&event))
			{
				OnEvent(&event);
			}

			//
			Update();
			Render();
		}
	}

	bool App::Init()
	{
		// Init the external dependencies
		//
		bool success = SDLInit() && GlewInit();
		if (!success)
		{
			m_state = GameState::INIT_FAILED;
			return false;
		}

		// Setup the viewport
		//
		SetupViewport();

		// Change game state
		//
		m_state = GameState::INIT_SUCCESSFUL;

		return true;
	}

	void App::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
	{
		
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			SDL_Log("Moviendo adelante");
			
			p1->setIsSpeedingUp();
			upArrow = true;
			break;
		case SDL_SCANCODE_LEFT:
			SDL_Log("Rotando a la izquierda");
			leftArrow = true;
			
			break;
		case SDL_SCANCODE_DOWN:
	
			break;
		case SDL_SCANCODE_RIGHT:
			SDL_Log("Rotando a la derecha");
			rightArrow = true;
			
			break;
		case SDL_SCANCODE_D:
			if (debugMode == false) {
				SDL_Log("Modo de debug activado");
				debugMode = true;
			}
			else if (debugMode == true) {
				SDL_Log("Modo de debug desactivado");
				debugMode = false;
			}
			break;
		case SDL_SCANCODE_KP_PLUS:
			SDL_Log("Anadiendo asteroide");
			asteroids.push_back(new Asteroid(m_width, m_height,large));
			break;
		case SDL_SCANCODE_KP_MINUS:
			if (asteroids.size()>0) {
				SDL_Log("Eliminando asteroide");
				asteroids.pop_back();
			}
			break;
		case SDL_SCANCODE_SPACE:
			SDL_Log("Disparando");
			spaceBar = true;
			break;
		case SDL_SCANCODE_F:
			SDL_Log("Mostrando frame-rate");
			if (showFrame == false) {
				showFrame = true;
			}
			else {
				showFrame = false;
			}
			break;
		default:			
			SDL_Log("%S was pressed.", keyBoardEvent.keysym.scancode);
			break;
		}
	}

	void App::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{

		case SDL_SCANCODE_UP:
			upArrow = false;
			p1->StopThrust();
			break;
		case SDL_SCANCODE_LEFT:
			SDL_Log("Rotando a la izquierda");
			leftArrow = false;
			
			break;
		case SDL_SCANCODE_DOWN:
			
			break;
		case SDL_SCANCODE_RIGHT:
			SDL_Log("Rotando a la derecha");
			rightArrow = false;
			
			break;
		case SDL_SCANCODE_SPACE:
			SDL_Log("Disparando");
			spaceBar = false;
			break;
		case SDL_SCANCODE_ESCAPE:

			OnExit();
			break;
		
		default:
			//DO NOTHING
			break;
		}
	}

	void App::Update()
	{
		double startTime = m_timer->GetElapsedTimeInSeconds();

		// Update code goes here
		//
		
		if (upArrow)
			p1->MoveForward();
		if (leftArrow)
			p1->RotateLeft();
		if (rightArrow)
			p1->RotateRight();
		if (spaceBar) {
			if (bullets.size()<3  ) {
				bullets.push_back(p1->shoot());
			}
			spaceBar = false;
		}
		
		p1->Update(frameDeltaTime);

		for (int i = 0; i < asteroids.size(); i++) {
			asteroids[i]->Update(frameDeltaTime);
		}

		std::vector <Bullet*> activeBullets;
		for (auto bullet : bullets) {
			bullet->Update(frameDeltaTime );
			if (debugMode) {
				bullet->drawCircle();
			}
			if (!bullet->IsActive()) activeBullets.push_back(bullet);
		}

		bullets = activeBullets;

		if (!debugMode) {
			for (int i = 0; i < asteroids.size(); i++) {
				for (int j = 0; j < bullets.size(); j++) {
					if (asteroids[i]->checkCollision(bullets[j])) {
						if (asteroids[i]->getSize() == 'l') {
							asteroids[i]->setSize('m');
							bullets.erase(bullets.begin() + j);
							Vector2 pos = asteroids[i]->getPosition();
							asteroids.insert(asteroids.begin() + (i), new Asteroid(m_width, m_height, medium) );
							asteroids[i]->setPosition(pos);
	
						}
						else if (asteroids[i]->getSize() == 'm') {
							asteroids[i]->setSize('s');
							bullets.erase(bullets.begin() + j);
							Vector2 pos = asteroids[i]->getPosition();
							asteroids.insert(asteroids.begin() + (i), new Asteroid(m_width, m_height, smalll));
							asteroids[i]->setPosition(pos);
							
						}
						else if (asteroids[i]->getSize() == 's') {
							bullets.erase(bullets.begin() + j);
							asteroids.erase(asteroids.begin() + i);
						}
					}
				}
				
				if (asteroids[i]->checkCollision(p1)) {
					delete p1;
				}
			}
		}

		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

		frameDeltaTime = DESIRED_FRAME_TIME - ( endTime - startTime);
		createFrameRate();
		while (endTime < nextTimeFrame)
		{
			// Spin lock
			endTime = m_timer->GetElapsedTimeInSeconds();
		}

		double elapsedTime = endTime - startTime;        

		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();

		m_nUpdates++;
		
	}

	void App::Render()
	{
		ColorRepresentation background;
		glClearColor(background.midnightBlue.R, background.midnightBlue.G, background.midnightBlue.B, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		p1->Render();
		
		for (int i = 0; i < asteroids.size(); i++) {
			asteroids[i]->Render();
		}
		if (debugMode) {
			p1->drawCircle();
			for (int i = 0; i < asteroids.size(); i++) {
				asteroids[i]->drawCircle();
				p1->drawLines(asteroids[i]);
			}
		}
		if (showFrame) {
			createFrameRateGraph();
		}

		for (auto bullet : bullets) bullet->Render();

		SDL_GL_SwapWindow(m_mainWindow);
	}

	bool App::SDLInit()
	{
		// Initialize SDL's Video subsystem
		//
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cerr << "Failed to init SDL" << std::endl;
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Uint32 flags =  SDL_WINDOW_OPENGL     | 
						SDL_WINDOW_SHOWN      | 
						SDL_WINDOW_RESIZABLE;

		m_mainWindow = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			flags
		);

		if (!m_mainWindow)
		{
			std::cerr << "Failed to create window!" << std::endl;
			SDL_Quit();
			return false;
		}

		m_context = SDL_GL_CreateContext(m_mainWindow);
		SDL_GL_MakeCurrent(m_mainWindow, m_context);

		// Make double buffer interval synced with vertical scanline refresh
		SDL_GL_SetSwapInterval(0);

		return true;
	}

	void App::SetupViewport()
	{
		// Defining ortho values
		//
		float halfWidth = m_width * 0.5f;
		float halfHeight = m_height * 0.5f;

		// Set viewport to match window
		//
		glViewport(0, 0, m_width, m_height);

		// Set Mode to GL_PROJECTION
		//
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set projection MATRIX to ORTHO
		//
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

		// Setting Mode to GL_MODELVIEW
		//
		glMatrixMode(GL_MODELVIEW);
	}

	bool App::GlewInit()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}

		return true;
	}

	void App::CleanupSDL()
	{
		// Cleanup
		//
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();
	}
	
	void App::createFrameRate() {
		frames[framePosition] = Vector2((float)framePosition, frameDeltaTime);
		framePosition += 1;
		if (framePosition >= maxFrames) {
			framePosition = 0;
		}

	}
	void App::createFrameRateGraph() {
		glLoadIdentity();
		glTranslatef(150.0, -250.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0.0, 1.0);
		for (int i = 0; i < maxFrames; i++) {
			glVertex2f(frames[i].x *15.0f, (DESIRED_FRAME_TIME - frames[i].y )* 80000.0f);
			}
		glEnd();

	}

	

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;
		p1->resizeWidthAndHeight(m_width, m_height);
		for (int i = 0; i < asteroids.size(); i++) {
			asteroids[i]->resizeWidthAndHeight(m_width, m_height);
		}
		
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->resizeWidthAndHeight(m_width, m_height);
		}
	
		SetupViewport();
	}

	void App::OnExit()
	{
		// Exit main for loop
		//
		m_state = GameState::QUIT;

		// Cleanup SDL pointers
		//
		CleanupSDL();
	}
}
