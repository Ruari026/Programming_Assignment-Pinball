/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();

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
	theFontMgr->initFontLib();
	
	//Main Menu Elements
	{
		//Background
		theTextureMgr->addTexture("menuBackground", "Images\\MainMenu.png");
		menuBkgd.setSpritePos({ 0, 0 });
		menuBkgd.setTexture(theTextureMgr->getTexture("menuBackground"));
		menuBkgd.setSpriteDimensions(theTextureMgr->getTexture("menuBackground")->getTWidth(), theTextureMgr->getTexture("menuBackground")->getTHeight());

		//Scene Buttons
		//Game Start Button
		theTextureMgr->addTexture("menuButton1", "Images\\MainMenu\\PlayButton.png");
		cButton* newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("menuButton1"));
		newBtn->setSpritePos({ 225,550 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("menuButton1")->getTWidth(), theTextureMgr->getTexture("menuButton1")->getTHeight());
		theButtonMgr->add("Play_Btn", newBtn);
		//Instructions & Controls Button
		theTextureMgr->addTexture("menuButton2", "Images\\MainMenu\\InstructionsButton.png");
		newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("menuButton2"));
		newBtn->setSpritePos({ 225,700 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("menuButton2")->getTWidth(), theTextureMgr->getTexture("menuButton2")->getTHeight());
		theButtonMgr->add("Instructions_Btn", newBtn);
		//Quit Game Button
		theTextureMgr->addTexture("menuButton3", "Images\\MainMenu\\QuitButton.png");
		newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("menuButton3"));
		newBtn->setSpritePos({ 225,850 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("menuButton3")->getTWidth(), theTextureMgr->getTexture("menuButton3")->getTHeight());
		theButtonMgr->add("Quit_Btn", newBtn);
	}

	//Instructions & Controls Scene Elements
	{
		//Background
		theTextureMgr->addTexture("instructionsBackground", "Images\\Instructions\\InstructionsDesign.png");
		instructionsBkgd.setSpritePos({ 0, 0 });
		instructionsBkgd.setTexture(theTextureMgr->getTexture("instructionsBackground"));
		instructionsBkgd.setSpriteDimensions(theTextureMgr->getTexture("instructionsBackground")->getTWidth(), theTextureMgr->getTexture("instructionsBackground")->getTHeight());

		//Main Menu Button
		theTextureMgr->addTexture("button2", "Images\\Instructions\\Button.png");
		cButton* newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("button2"));
		newBtn->setSpritePos({ 75,75 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("button2")->getTWidth(), theTextureMgr->getTexture("button2")->getTHeight());
		theButtonMgr->add("Menu_Btn", newBtn);
	}

	//Game Scene Elements
	{
		//Game Background
		theTextureMgr->addTexture("theBackground", "Images\\Background.png");
		gameBkgd.setSpritePos({ 0, 0 });
		gameBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
		gameBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

		//The Walls
		theTextureMgr->addTexture("horizontalWall", "Images\\Walls1.png");
		theTextureMgr->addTexture("verticalWall", "Images\\Walls2.png");
		theTextureMgr->addTexture("leftSlope", "Images\\Corner-L.png");
		theTextureMgr->addTexture("rightSlope", "Images\\Corner-R.png");
		theTextureMgr->addTexture("leftInternal", "Images\\Internal-L.png");
		theTextureMgr->addTexture("rightInternal", "Images\\Internal-R.png");
		//Top Wall
		wallSprites.push_back(new cWall);
		wallSprites[0]->setSpritePos({ 0,170 });
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
		//Left Internal Wall
		wallSprites.push_back(new cWall);
		wallSprites[5]->setSpritePos({ 100,700 });
		wallSprites[5]->setTexture(theTextureMgr->getTexture("leftInternal"));
		wallSprites[5]->setSpriteDimensions(theTextureMgr->getTexture("leftInternal")->getTWidth(), theTextureMgr->getTexture("leftInternal")->getTHeight());
		wallSprites[5]->initialise(theSDLWND, theRenderer, "Images\\Internal-L.png");
		//Right Internal Wall
		wallSprites.push_back(new cWall);
		wallSprites[6]->setSpritePos({ 620,700 });
		wallSprites[6]->setTexture(theTextureMgr->getTexture("rightInternal"));
		wallSprites[6]->setSpriteDimensions(theTextureMgr->getTexture("rightInternal")->getTWidth(), theTextureMgr->getTexture("rightInternal")->getTHeight());
		wallSprites[6]->initialise(theSDLWND, theRenderer, "Images\\Internal-R.png");

		//The Flippers
		theTextureMgr->addTexture("theFlipper", "Images\\Flipper.png");
		//Left Flipper
		leftFlipper.setSpritePos({ 155,817 });
		leftFlipper.setTexture(theTextureMgr->getTexture("theFlipper"));
		leftFlipper.setSpriteDimensions(theTextureMgr->getTexture("theFlipper")->getTWidth(), theTextureMgr->getTexture("theFlipper")->getTHeight());
		leftFlipper.SetFlipperType(FlipperType::LEFT);
		leftFlipper.initialise(theSDLWND, theRenderer, "Images\\Flipper.png");
		//Right Flipper
		rightFlipper.setSpritePos({ (800 - 155 - 200),817 });
		rightFlipper.setTexture(theTextureMgr->getTexture("theFlipper"));
		rightFlipper.setSpriteDimensions(theTextureMgr->getTexture("theFlipper")->getTWidth(), theTextureMgr->getTexture("theFlipper")->getTHeight());
		rightFlipper.SetFlipperType(FlipperType::RIGHT);
		rightFlipper.initialise(theSDLWND, theRenderer, "Images\\Flipper.png");

		//The Bumpers
		theTextureMgr->addTexture("bumper100", "Images\\Bumper1.png");
		theTextureMgr->addTexture("bumper500", "Images\\Bumper2.png");
		//High Score Bumper
		bumperSprites.push_back(new cBumper);
		bumperSprites[0]->setSpritePos({ 350,275 });
		bumperSprites[0]->setTexture(theTextureMgr->getTexture("bumper500"));
		bumperSprites[0]->setSpriteDimensions(theTextureMgr->getTexture("bumper500")->getTWidth(), theTextureMgr->getTexture("bumper500")->getTHeight());
		bumperSprites[0]->initialise(theSDLWND, theRenderer, "Images\\Bumper2.png");
		bumperSprites[0]->SetBumperValue(500);
		//Low Score Bumpers
		bumperSprites.push_back(new cBumper);
		bumperSprites[1]->setSpritePos({ 150,325 });
		bumperSprites[1]->setTexture(theTextureMgr->getTexture("bumper100"));
		bumperSprites[1]->setSpriteDimensions(theTextureMgr->getTexture("bumper100")->getTWidth(), theTextureMgr->getTexture("bumper100")->getTHeight());
		bumperSprites[1]->initialise(theSDLWND, theRenderer, "Images\\Bumper1.png");
		bumperSprites[1]->SetBumperValue(100);
		bumperSprites.push_back(new cBumper);
		bumperSprites[2]->setSpritePos({ 550,325 });
		bumperSprites[2]->setTexture(theTextureMgr->getTexture("bumper100"));
		bumperSprites[2]->setSpriteDimensions(theTextureMgr->getTexture("bumper100")->getTWidth(), theTextureMgr->getTexture("bumper100")->getTHeight());
		bumperSprites[2]->initialise(theSDLWND, theRenderer, "Images\\Bumper1.png");
		bumperSprites[2]->SetBumperValue(100);

		//The Ball
		theTextureMgr->addTexture("theBall", "Images\\Ball.png");
		ballSprite.initialise();
		ballSprite.setTexture(theTextureMgr->getTexture("theBall"));
		ballSprite.setSpriteDimensions(theTextureMgr->getTexture("theBall")->getTWidth(), theTextureMgr->getTexture("theBall")->getTHeight());

		//Loading Game Fonts
		//Score Text
		theFontMgr->addFont("digital", "Fonts\\DS-DIGIB.TTF", 48);
		theTextureMgr->addTexture("scoreText", theFontMgr->getFont("digital")->createTextTexture(theRenderer, "Score: 0", textType::solid, { 255,255,255,255 }, { 0,0,0,0 }));
	}

	//Setting Starting Scene
	currentGameState = gameState::mainMenu;
	
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput();
		this->update(elapsedTime, theRenderer);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	
	switch (currentGameState)
	{
		case (gameState::mainMenu):
		{
			//Background
			menuBkgd.render(theRenderer, NULL, NULL, menuBkgd.getSpriteScale());
		
			//Buttons
			theButtonMgr->getBtn("Play_Btn")->render(theRenderer, &theButtonMgr->getBtn("Play_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("Play_Btn")->getSpritePos(), theButtonMgr->getBtn("Play_Btn")->getSpriteScale());
			theButtonMgr->getBtn("Instructions_Btn")->render(theRenderer, &theButtonMgr->getBtn("Instructions_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("Instructions_Btn")->getSpritePos(), theButtonMgr->getBtn("Instructions_Btn")->getSpriteScale());
			theButtonMgr->getBtn("Quit_Btn")->render(theRenderer, &theButtonMgr->getBtn("Quit_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("Quit_Btn")->getSpritePos(), theButtonMgr->getBtn("Quit_Btn")->getSpriteScale());
		}
		break;

		case (gameState::instructions):
		{
			//Background
			instructionsBkgd.render(theRenderer, NULL, NULL, instructionsBkgd.getSpriteScale());
	
			//Buttons
			theButtonMgr->getBtn("Menu_Btn")->render(theRenderer, &theButtonMgr->getBtn("Menu_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("Menu_Btn")->getSpritePos(), theButtonMgr->getBtn("Menu_Btn")->getSpriteScale());
		}
		break;

		case (gameState::gameScene):
		{
			//Gameobjects
			gameBkgd.render(theRenderer, NULL, NULL, gameBkgd.getSpriteScale());

			for (int w = 0; w < wallSprites.size(); w++)
			{
				wallSprites[w]->render(theRenderer, &wallSprites[w]->getSpriteDimensions(), &wallSprites[w]->getSpritePos(), wallSprites[w]->getSpriteScale());
			}

			leftFlipper.render(theRenderer, &leftFlipper.getSpriteDimensions(), &leftFlipper.getSpritePos(), leftFlipper.GetFlipperRotation(), &leftFlipper.getSpriteCentre(), leftFlipper.getSpriteScale());
			rightFlipper.render(theRenderer, &rightFlipper.getSpriteDimensions(), &rightFlipper.getSpritePos(), rightFlipper.GetFlipperRotation(), &rightFlipper.getSpriteCentre(), rightFlipper.getSpriteScale());

			for (int i = 0; i < bumperSprites.size(); i++)
			{
				bumperSprites[i]->render(theRenderer, &bumperSprites[i]->getSpriteDimensions(), &bumperSprites[i]->getSpritePos(), bumperSprites[i]->getSpriteScale());
			}

			ballSprite.render(theRenderer, &ballSprite.getSpriteDimensions(), &ballSprite.getSpritePos(), ballSprite.getBallRotation(), &ballSprite.getSpriteCentre(), ballSprite.getSpriteScale());

			//UI Elements
			cTexture* tempTexture = theTextureMgr->getTexture("scoreText");
			SDL_Rect pos = { (WINDOW_WIDTH / 2) - (tempTexture->getTWidth() / 2), 75, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
			tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, { 10,10 });
		}
		break;
	}
	
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{
	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime, SDL_Renderer* theRenderer)
{
	switch (currentGameState)
	{
		case (gameState::mainMenu):
		{
			currentGameState = theButtonMgr->getBtn("Play_Btn")->update(currentGameState, gameState::gameScene, clickedArea);
			currentGameState = theButtonMgr->getBtn("Instructions_Btn")->update(currentGameState, gameState::instructions, clickedArea);
			currentGameState = theButtonMgr->getBtn("Quit_Btn")->update(currentGameState, gameState::exit, clickedArea);
		}
		break;

		case (gameState::instructions):
		{
			currentGameState = theButtonMgr->getBtn("Menu_Btn")->update(currentGameState, gameState::mainMenu, clickedArea);
		}
		break;

		case (gameState::gameScene):
		{
			//Calculating the ball's new velocity
			ballSprite.CalculateBallVelocity();

			//Checking if any collisions are occuring
			ballSprite.canCollide = true;
			ballSprite.SetBoundingRect();

			//Collisions with the walls
			for (int w = 0; w < wallSprites.size(); w++)
			{
				if (ballSprite.CollidedWithBox(&ballSprite.GetBoundingRect(), &wallSprites[w]->GetBoundingRect()))
				{
					if (ballSprite.CollidedWithPixels({ (ballSprite.getSpritePos().x + ballSprite.getSpriteCentre().x),(ballSprite.getSpritePos().y + ballSprite.getSpriteCentre().y) }, wallSprites[w]->GetCollisionPoints()))
					{
						//Collision Reflection
						ballSprite.CalculateCollisions(wallSprites[w]->GetCollisionPoints());
					}
				}
			}
			//Collisions with the Flippers
			if (ballSprite.CollidedWithPixels({ (ballSprite.getSpritePos().x + ballSprite.getSpriteCentre().x),(ballSprite.getSpritePos().y + ballSprite.getSpriteCentre().y) }, leftFlipper.GetCollisionPoints()))
			{
				//Collision Reflection
				ballSprite.CalculateCollisions(leftFlipper.GetRotatedCollisionPoints());

				//Force Addition
				if (leftFlipper.GetAnimationState())
				{
					ballSprite.addForceToBall(10, -30);
				}
			}
			if (ballSprite.CollidedWithPixels({ (ballSprite.getSpritePos().x + ballSprite.getSpriteCentre().x),(ballSprite.getSpritePos().y + ballSprite.getSpriteCentre().y) }, rightFlipper.GetCollisionPoints()))
			{
				//Collision Reflection
				ballSprite.CalculateCollisions(rightFlipper.GetRotatedCollisionPoints());

				//Force Addition
				if (rightFlipper.GetAnimationState())
				{
					ballSprite.addForceToBall(-5, -30);
				}
			}

			//Collisions with the Bumpers
			for (int b = 0; b < bumperSprites.size(); b++)
			{
				if (ballSprite.CollidedWithBox(&ballSprite.GetBoundingRect(), &bumperSprites[b]->GetBoundingRect()))
				{
					if (ballSprite.CollidedWithPixels({ (ballSprite.getSpritePos().x + ballSprite.getSpriteCentre().x),(ballSprite.getSpritePos().y + ballSprite.getSpriteCentre().y) }, bumperSprites[b]->GetCollisionPoints()))
					{
						//Collision Reflection
						ballSprite.CalculateCollisions(bumperSprites[b]->GetCollisionPoints());

						//Points Addition
						gameScore += bumperSprites[b]->GetBumperValue();
						cout << "Score: " << gameScore << endl << endl;

						theTextureMgr->deleteTexture("scoreText");
						string s = "Score: ";
						s += to_string(gameScore);
						theTextureMgr->addTexture("scoreText", theFontMgr->getFont("digital")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 255,255,255,255 }, { 0,0,0,0 }));
					}
				}
			}

			//Setting the ball's new position
			ballSprite.CalculateBallPosition();
			ballSprite.SetBallPosition();

			//Flipper Animations
			leftFlipper.update(deltaTime);
			rightFlipper.update(deltaTime);
		}
		break;

		case (gameState::exit):
		{
			loop = false;
		}
		break;
	}
}

bool cGame::getInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			loop = false;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				clickedArea = { event.motion.x, event.motion.y };
			}
		}

		//Scene Exclusive Controls
		switch (currentGameState)
		{
			case (gameState::gameScene):
			{
				switch (event.type)
				{

				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
					//Quitting the Game
					case SDLK_ESCAPE:
					{
						currentGameState = gameState::exit;
					}
					break;

					//Moving the ball
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

					//Respawn
					case SDLK_r:
					{
						ballSprite.RespawnBall(250, 400);
					}
					break;

					//Flippers
					case SDLK_q:
					{
						leftFlipper.Activate();
					}
					break;

					case SDLK_e:
					{
						rightFlipper.Activate();
					}
					break;
					}
				}
				}
			}
			break;
		}
	}
	return loop;
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

