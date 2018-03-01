#include "App.hpp"
#include <iostream>
#include <algorithm>
#include "ColorRepresentation.h"
// OpenGL includes
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#include "_vector2.h"
#include <string>

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
		showFrame = false;
		large = 'l';
		smalll = 's';
		medium = 'm';

		Game1 = Game(m_width, m_height);

		
		for (int i = 0; i < maxFrames; i++) {
			frames[i] = Vector2((float)i, 0.0f);
		}
		framePosition = 0;
		frameDeltaTime = DESIRED_FRAME_RATE;
		
	}

	TTF_Font*  m_font;
	
	
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

		if (TTF_Init() == -1) {
			SDL_Log("TTF_Init: %s\n", TTF_GetError());
			return false;
		}
		m_font = TTF_OpenFont("Hyperspace.ttf", 50);

		SDL_version compile_version;
		const SDL_version *link_version = TTF_Linked_Version();
		SDL_TTF_VERSION(&compile_version);

		SDL_Log("compiled with SDL_ttf version: %d.%d.%d\n",
			compile_version.major,
			compile_version.minor,
			compile_version.patch);

		SDL_Log("running with SDL_ttf version: %d.%d.%d\n",
			link_version->major,
			link_version->minor,
			link_version->patch);

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
			Game1.getPlayer()->setIsSpeedingUp();
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
			Game1.SwitchDebugMode();
				SDL_Log("Cambiando modo de debug");
			break;
		case SDL_SCANCODE_R:
			SDL_Log("Reiniciando juego");
			if (Game1.getPlayerStatus() == 0) {
				Game1.RestartGame();
			}
			break;
		case SDL_SCANCODE_KP_PLUS:
			SDL_Log("Anadiendo asteroide");
			Game1.AddAsteroid();
			break;
		case SDL_SCANCODE_KP_MINUS:
			Game1.EliminateAsteroid();
				SDL_Log("Eliminando asteroide");
				
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
			Game1.getPlayer()->StopThrust();
			break;
		case SDL_SCANCODE_LEFT:
		
			leftArrow = false;
			
			break;
		case SDL_SCANCODE_DOWN:
			
			break;
		case SDL_SCANCODE_RIGHT:
			rightArrow = false;
			
			break;
		case SDL_SCANCODE_SPACE:
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

	unsigned int power_two_floor(unsigned int val) {
		unsigned int power = 2, nextVal = power * 2;
		while ((nextVal *= 2) <= val)
			power *= 2;
		return power * 2;
	}

	

	void RenderText(std::string message, SDL_Color color, float x, float y)
	{
		glLoadIdentity();
		glTranslatef(x, y, 0.f);

		SDL_Surface *surface;

		//Render font to a SDL_Surface
		if ((surface = TTF_RenderText_Blended(m_font, message.c_str(), color)) == nullptr) {
			TTF_CloseFont(m_font);
			std::cout << "TTF_RenderText error: " << std::endl;
			return;
		}

		GLuint texId;

		//Generate OpenGL texture
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);

		//Avoid mipmap filtering
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//Find the first power of two for OpenGL image 
		int w = power_two_floor(surface->w) * 2;
		int h = power_two_floor(surface->h) * 2;

		//Create a surface to the correct size in RGB format, and copy the old image
		SDL_Surface * s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

		SDL_BlitSurface(surface, NULL, s, NULL);

		//Copy the created image into OpenGL format
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);

		//Draw the OpenGL texture as a Quad
		glBegin(GL_QUADS); {
			glTexCoord2d(0, 1); glVertex3f(0, 0, 0);
			glTexCoord2d(1, 1); glVertex3f(0 + surface->w, 0, 0);
			glTexCoord2d(1, 0); glVertex3f(0 + surface->w, 0 + surface->h, 0);
			glTexCoord2d(0, 0); glVertex3f(0, 0 + surface->h, 0);
		} glEnd();
		glDisable(GL_TEXTURE_2D);

		//Cleanup
		SDL_FreeSurface(s);
		SDL_FreeSurface(surface);
		glDeleteTextures(1, &texId);
	}

	void App::Update()
	{
		double startTime = m_timer->GetElapsedTimeInSeconds();

		// Update code goes here
		//
		
		if (upArrow)
			Game1.getPlayer()->MoveForward();
		if (leftArrow)
			Game1.getPlayer()->RotateLeft();
		if (rightArrow)
			Game1.getPlayer()->RotateRight();
		if (spaceBar) {
			Game1.ShotABullet();
			spaceBar = false;
		}
		
		Game1.UpdateGame(frameDeltaTime);


		Game1.CheckAllCollisions();
		
		//RenderText("#Ay!", color)
	

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
		
		Game1.RenderGame();
		Game1.DrawCircles();

		SDL_Color rojo;
		rojo.r = 0;
		rojo.g = 0;
		rojo.b = 0;
		rojo.a = 0;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(1.0, 0.0, 0.0, 0.0);
		RenderText(std::to_string(Game1.getScore()), rojo, -500.0, 200.0);
		if (Game1.getPlayerStatus()==false) {
			RenderText("GAME OVER", rojo, -100.0, -25.0);
			RenderText("Press R to play again   -  Press ESC to exit", rojo, -380.0, -100.0);
		}




		if (showFrame) {
			createFrameRateGraph();
		}

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
		
	
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 0.0, 1.0);
		for (int i = 0; i < maxFrames; i++) {
			glVertex2f(frames[i].x *15.0f, (DESIRED_FRAME_TIME - frames[i].y )* 25000.0f);
			}
		glEnd();

	}

	

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;
		Game1.ResizeWidthAndHeight(m_width, m_height);
	
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
