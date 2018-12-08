#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "pinballGame.h"

using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime, SDL_Renderer* theRenderer);
	bool getInput();
	double getElapsedSeconds();
	void ResetGame(SDL_Renderer* theRenderer);

	static cGame* getInstance();

private:

	static cGame* pInstance;
	bool loop = true;
	gameState currentGameState;
	SDL_Point clickedArea;

	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;

	// Main Menu Scene
	cSprite menuBkgd;

	//Instructions Scene
	cSprite instructionsBkgd;

	// Game Scene
	int gameScore = 0;
	// Game objects
	cSprite gameBkgd;
	vector<cWall*> wallSprites;
	cFlipper leftFlipper;
	cFlipper rightFlipper;
	vector<cBumper*> bumperSprites;
	cBall ballSprite;

	//Hi Scores Scene
	cSprite hiScoresBkgd;
};

#endif
