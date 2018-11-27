/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();

/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}


/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}

void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	this->m_lastTime = high_resolution_clock::now();

	theTextureMgr->setRenderer(theRenderer);
	
	//Game Background
	theTextureMgr->addTexture("theBackground", "Images\\Background.png");
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	//The Walls
	theTextureMgr->addTexture("horizontalWall", "Images\\Walls1.png");
	theTextureMgr->addTexture("verticalWall", "Images\\Walls2.png");
	theTextureMgr->addTexture("leftSlope", "Images\\Corner-L.png");
	theTextureMgr->addTexture("rightSlope", "Images\\Corner-R.png");
	//Top Wall
	wallSprites.push_back(new cWall);
	wallSprites[0]->setSpritePos({ 0,0 });
	wallSprites[0]->setTexture(theTextureMgr->getTexture("horizontalWall"));
	wallSprites[0]->setSpriteDimensions(theTextureMgr->getTexture("horizontalWall")->getTWidth(), theTextureMgr->getTexture("horizontalWall")->getTHeight());
	wallSprites[0]->initialise(theSDLWND, theRenderer, "Images\\Walls1.png");
	//Left Wall
	wallSprites.push_back(new cWall);
	wallSprites[1]->setSpritePos({ 0,0 });
	wallSprites[1]->setTexture(theTextureMgr->getTexture("verticalWall"));
	wallSprites[1]->setSpriteDimensions(theTextureMgr->getTexture("verticalWall")->getTWidth(), theTextureMgr->getTexture("verticalWall")->getTHeight());
	wallSprites[1]->initialise(theSDLWND, theRenderer, "Images\\Walls2.png");
	//Right Wall
	wallSprites.push_back(new cWall);
	wallSprites[2]->setSpritePos({ 770,0 });
	wallSprites[2]->setTexture(theTextureMgr->getTexture("verticalWall"));
	wallSprites[2]->setSpriteDimensions(theTextureMgr->getTexture("verticalWall")->getTWidth(), theTextureMgr->getTexture("verticalWall")->getTHeight());
	wallSprites[2]->initialise(theSDLWND, theRenderer, "Images\\Walls2.png");
	//Left Slope
	wallSprites.push_back(new cWall);
	wallSprites[3]->setSpritePos({ 0,870 });
	wallSprites[3]->setTexture(theTextureMgr->getTexture("leftSlope"));
	wallSprites[3]->setSpriteDimensions(theTextureMgr->getTexture("leftSlope")->getTWidth(), theTextureMgr->getTexture("leftSlope")->getTHeight());
	wallSprites[3]->initialise(theSDLWND, theRenderer, "Images\\Corner-L.png");
	//Right Slope
	wallSprites.push_back(new cWall);
	wallSprites[4]->setSpritePos({ 500,870 });
	wallSprites[4]->setTexture(theTextureMgr->getTexture("rightSlope"));
	wallSprites[4]->setSpriteDimensions(theTextureMgr->getTexture("rightSlope")->getTWidth(), theTextureMgr->getTexture("rightSlope")->getTHeight());
	wallSprites[4]->initialise(theSDLWND, theRenderer, "Images\\Corner-R.png");


	//The Ball
	theTextureMgr->addTexture("theBall", "Images\\Ball.png");
	ballSprite.initialise();
	ballSprite.setTexture(theTextureMgr->getTexture("theBall"));
	ballSprite.setSpriteDimensions(theTextureMgr->getTexture("theBall")->getTWidth(), theTextureMgr->getTexture("theBall")->getTHeight());
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	
	spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
	
	for (int w = 0; w < wallSprites.size(); w++)
	{
		wallSprites[w]->render(theRenderer, &wallSprites[w]->getSpriteDimensions(), &wallSprites[w]->getSpritePos(), wallSprites[w]->getSpriteScale());
	}

	ballSprite.render(theRenderer, &ballSprite.getSpriteDimensions(), &ballSprite.getSpritePos(), ballSprite.getBallRotation(), &ballSprite.getSpriteCentre(), ballSprite.getSpriteScale());
	
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	//Calculating the ball's new velocity
	ballSprite.CalculateBallVelocity();

	//Chacking if any collisions are occuring
	ballSprite.SetBoundingRect();
	for (int w = 0; w < wallSprites.size(); w++)
	{
		if (ballSprite.CollidedWith(&ballSprite.GetBoundingRect(), &wallSprites[w]->GetBoundingRect()))
		{
			ballSprite.CalculateCollisions(wallSprites[w]->GetCollisionPoints());
		}
	}

	//Setting the ball's new position
	ballSprite.CalculateBallPosition();
	ballSprite.SetBallPosition();
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		if (event.type == SDL_KEYDOWN)
		{
			SDL_Rect currentPos = ballSprite.getSpritePos();
			switch (event.key.keysym.sym)
			{

				case SDLK_ESCAPE:
				{
					theLoop = false;
				}
				break;

				case SDLK_w:
				{
					ballSprite.addForceToBall(0, -25);
				}
				break;

				case SDLK_a:
				{
					ballSprite.addForceToBall(-25, 0);
				}
				break;

				case SDLK_s:
				{
					ballSprite.addForceToBall(0, 25);
				}
				break;

				case SDLK_d:
				{
					ballSprite.addForceToBall(25, 0);
				}
				break;

			}
		}
	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}
