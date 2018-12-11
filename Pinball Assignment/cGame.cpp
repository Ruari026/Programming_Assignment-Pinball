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
static cHiScoreMgr* theScoreMgr = cHiScoreMgr::getInstance();
static cInputMgr* theInputMgr = cInputMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

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
	cout << "- Initialising Game -" << endl;
	cout << "--------------------" << endl;

	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	this->m_lastTime = high_resolution_clock::now();

	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();
	
	//Main Menu Elements
	{
		cout << "- Loading Main Menu Items" << endl;

		//Background
		theTextureMgr->addTexture("menuBackground", "Images\\MainMenu\\MainMenu.png");
		menuBkgd.setSpritePos({ 0, 0 });
		menuBkgd.setTexture(theTextureMgr->getTexture("menuBackground"));
		menuBkgd.setSpriteDimensions(theTextureMgr->getTexture("menuBackground")->getTWidth(), theTextureMgr->getTexture("menuBackground")->getTHeight());

		//Controller State
		theTextureMgr->addTexture("controllerTrue", "Images\\MainMenu\\ConnectionTrue.png");
		controllerTrue.setSpritePos({ 25, 825 });
		controllerTrue.setTexture(theTextureMgr->getTexture("controllerTrue"));
		controllerTrue.setSpriteDimensions(theTextureMgr->getTexture("controllerTrue")->getTWidth(), theTextureMgr->getTexture("controllerTrue")->getTHeight());
		theTextureMgr->addTexture("controllerFalse", "Images\\MainMenu\\ConnectionFalse.png");
		controllerFalse.setSpritePos({ 25, 825 });
		controllerFalse.setTexture(theTextureMgr->getTexture("controllerFalse"));
		controllerFalse.setSpriteDimensions(theTextureMgr->getTexture("controllerFalse")->getTWidth(), theTextureMgr->getTexture("controllerFalse")->getTHeight());

		//Button Selector
		theTextureMgr->addTexture("buttonSelector", "Images\\MainMenu\\ButtonSelector.png");
		menuSelector.setSpritePos({ 150,550 });
		menuSelector.setTexture(theTextureMgr->getTexture("buttonSelector"));
		menuSelector.setSpriteDimensions(theTextureMgr->getTexture("buttonSelector")->getTWidth(), theTextureMgr->getTexture("buttonSelector")->getTHeight());

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

		//Scene Sounds
		//Background Music
		theSoundMgr->add("MenuMusic", "Audio\\NewYorkJazzLoop-FoolBoyMedia.wav", soundType::music);
		//Button Clicks
		theSoundMgr->add("ButtonClick", "Audio\\UIConfirmation-InspectorJ.wav", soundType::sfx);

		cout << endl;
	}

	//Instructions & Controls Scene Elements
	{
		cout << "- Instructions Scene Items" << endl;

		//Background
		theTextureMgr->addTexture("instructionsBackground", "Images\\Instructions\\InstructionsDesign.png");
		instructionsBkgd.setSpritePos({ 0, 0 });
		instructionsBkgd.setTexture(theTextureMgr->getTexture("instructionsBackground"));
		instructionsBkgd.setSpriteDimensions(theTextureMgr->getTexture("instructionsBackground")->getTWidth(), theTextureMgr->getTexture("instructionsBackground")->getTHeight());
		theTextureMgr->addTexture("instructionsBackground2", "Images\\Instructions\\InstructionsDesign2.png");
		instructionsBkgd2.setSpritePos({ 0, 0 });
		instructionsBkgd2.setTexture(theTextureMgr->getTexture("instructionsBackground2"));
		instructionsBkgd2.setSpriteDimensions(theTextureMgr->getTexture("instructionsBackground2")->getTWidth(), theTextureMgr->getTexture("instructionsBackground2")->getTHeight());


		//Main Menu Button
		theTextureMgr->addTexture("button2", "Images\\Instructions\\Button.png");
		cButton* newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("button2"));
		newBtn->setSpritePos({ 75,75 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("button2")->getTWidth(), theTextureMgr->getTexture("button2")->getTHeight());
		theButtonMgr->add("Menu_Btn", newBtn);
		
		cout << endl;
	}

	//Hi Score Scene Elements
	{
		cout << "- Hi Score Scene Items" << endl;

		//Scene Background
		theTextureMgr->addTexture("hiScoresBackground", "Images\\Hi-Scores\\HiScoresDesign.png");
		hiScoresBkgd.setSpritePos({ 0, 0 });
		hiScoresBkgd.setTexture(theTextureMgr->getTexture("hiScoresBackground"));
		hiScoresBkgd.setSpriteDimensions(theTextureMgr->getTexture("hiScoresBackground")->getTWidth(), theTextureMgr->getTexture("hiScoresBackground")->getTHeight());

		//Scene Fonts
		theFontMgr->addFont("scores", "Fonts\\TCB_____.TTF", 48);
		theTextureMgr->addTexture("score1", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "1: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		theTextureMgr->addTexture("score2", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "2: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		theTextureMgr->addTexture("score3", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "3: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		theTextureMgr->addTexture("score4", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "4: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		theTextureMgr->addTexture("score5", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "5: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));

		//Scene Buttons
		//Game Restart Button
		theTextureMgr->addTexture("scoresButton1", "Images\\Hi-Scores\\RestartButton.png");
		cButton* newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("scoresButton1"));
		newBtn->setSpritePos({ 75,800 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("scoresButton1")->getTWidth(), theTextureMgr->getTexture("scoresButton1")->getTHeight());
		theButtonMgr->add("Restart_Btn", newBtn);
		//Quit to Main Menu Button
		theTextureMgr->addTexture("scoresButton2", "Images\\Hi-Scores\\MainMenuButton.png");
		newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("scoresButton2"));
		newBtn->setSpritePos({ 425,800 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("scoresButton2")->getTWidth(), theTextureMgr->getTexture("scoresButton2")->getTHeight());
		theButtonMgr->add("MainMenu_Btn", newBtn);

		//Button Selector
		theTextureMgr->addTexture("buttonSelector2", "Images\\Hi-Scores\\ButtonSelector.png");
		hiScoreSelector.setSpritePos({ 0,800 });
		hiScoreSelector.setTexture(theTextureMgr->getTexture("buttonSelector2"));
		hiScoreSelector.setSpriteDimensions(theTextureMgr->getTexture("buttonSelector2")->getTWidth(), theTextureMgr->getTexture("buttonSelector2")->getTHeight());

		//Scene Music
		theSoundMgr->add("HiScoreMusic", "Audio\\FunkyTunaGuitar-Abett.wav", soundType::music);

		cout << endl;
	}

	//Game Scene Elements
	{
		cout << "- Game Scene Items" << endl;

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
		wallSprites[5]->setSpritePos({ 100,685 });
		wallSprites[5]->setTexture(theTextureMgr->getTexture("leftInternal"));
		wallSprites[5]->setSpriteDimensions(theTextureMgr->getTexture("leftInternal")->getTWidth(), theTextureMgr->getTexture("leftInternal")->getTHeight());
		wallSprites[5]->initialise(theSDLWND, theRenderer, "Images\\Internal-L.png");
		//Right Internal Wall
		wallSprites.push_back(new cWall);
		wallSprites[6]->setSpritePos({ 620,685 });
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
	
		//Scene Sounds
		//Background Music
		theSoundMgr->add("GameMusic", "Audio\\VintageElectroPopLoop-Frankum.mp3", soundType::music);
	}

	//Setting Starting Scene
	currentGameState = gameState::mainMenu;

	//Setting Starting Music
	theSoundMgr->getSnd("MenuMusic")->play(-1);
	cout << "--------------------" << endl << endl;
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(theRenderer);
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
			
			//Controller Status
			if (theInputMgr->GetControllerStatus())
			{
				controllerTrue.render(theRenderer, &controllerTrue.getSpriteDimensions(), &controllerTrue.getSpritePos(), controllerTrue.getSpriteScale());
			}
			else
			{
				controllerFalse.render(theRenderer, &controllerFalse.getSpriteDimensions(), &controllerFalse.getSpritePos(), controllerFalse.getSpriteScale());
			}

			//Buttons
			theButtonMgr->getBtn("Play_Btn")->render(theRenderer, &theButtonMgr->getBtn("Play_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("Play_Btn")->getSpritePos(), theButtonMgr->getBtn("Play_Btn")->getSpriteScale());
			theButtonMgr->getBtn("Instructions_Btn")->render(theRenderer, &theButtonMgr->getBtn("Instructions_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("Instructions_Btn")->getSpritePos(), theButtonMgr->getBtn("Instructions_Btn")->getSpriteScale());
			theButtonMgr->getBtn("Quit_Btn")->render(theRenderer, &theButtonMgr->getBtn("Quit_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("Quit_Btn")->getSpritePos(), theButtonMgr->getBtn("Quit_Btn")->getSpriteScale());
			
			if (theInputMgr->GetControllerStatus())
			{
				menuSelector.setSpritePos({ 150,(550 + (selectedMenuButton * 150)) });
				menuSelector.render(theRenderer, &menuSelector.getSpriteDimensions(), &menuSelector.getSpritePos(), menuSelector.getSpriteScale());
			}
		}
		break;

		case (gameState::instructions):
		{
			//Background
			if (theInputMgr->GetControllerStatus())
			{
				//Gamepad Controls
				instructionsBkgd2.render(theRenderer, NULL, NULL, instructionsBkgd2.getSpriteScale());
			}
			else
			{
				//Keyboard Controls
				instructionsBkgd.render(theRenderer, NULL, NULL, instructionsBkgd.getSpriteScale());
			}
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

		case (gameState::hiScores):
		{
			//Background
			hiScoresBkgd.render(theRenderer, NULL, NULL, hiScoresBkgd.getSpriteScale());

			//Scores
			cTexture* tempTexture = theTextureMgr->getTexture("score1");
			SDL_Rect pos = { (WINDOW_WIDTH / 2) - (tempTexture->getTWidth() / 2), 190, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
			tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, { 10,10 });
			
			tempTexture = theTextureMgr->getTexture("score2");
			pos = { (WINDOW_WIDTH / 2) - (tempTexture->getTWidth() / 2), 290, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
			tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, { 10,10 });
			
			tempTexture = theTextureMgr->getTexture("score3");
			pos = { (WINDOW_WIDTH / 2) - (tempTexture->getTWidth() / 2), 390, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
			tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, { 10,10 });
			
			tempTexture = theTextureMgr->getTexture("score4");
			pos = { (WINDOW_WIDTH / 2) - (tempTexture->getTWidth() / 2), 490, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
			tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, { 10,10 });
			
			tempTexture = theTextureMgr->getTexture("score5");
			pos = { (WINDOW_WIDTH / 2) - (tempTexture->getTWidth() / 2), 590, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
			tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, { 10,10 });

			//Buttons
			theButtonMgr->getBtn("Restart_Btn")->render(theRenderer, &theButtonMgr->getBtn("Restart_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("Restart_Btn")->getSpritePos(), theButtonMgr->getBtn("Restart_Btn")->getSpriteScale());
			theButtonMgr->getBtn("MainMenu_Btn")->render(theRenderer, &theButtonMgr->getBtn("MainMenu_Btn")->getSpriteDimensions(), &theButtonMgr->getBtn("MainMenu_Btn")->getSpritePos(), theButtonMgr->getBtn("MainMenu_Btn")->getSpriteScale());
		
			if (theInputMgr->GetControllerStatus())
			{
				hiScoreSelector.setSpritePos({ (0 + (350 * selectedHiScoreButton)), 800 });
				hiScoreSelector.render(theRenderer, &hiScoreSelector.getSpriteDimensions(), &hiScoreSelector.getSpritePos(), hiScoreSelector.getSpriteScale());
			}
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
			theButtonMgr->getBtn("Play_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("Play_Btn")->getClicked())
			{
				ResetGame(theRenderer);
				currentGameState = gameState::gameScene;
				theButtonMgr->getBtn("Play_Btn")->setClicked(false);
				theSoundMgr->getSnd("ButtonClick")->play(0);
				theSoundMgr->getSnd("MenuMusic")->stop();
				theSoundMgr->getSnd("GameMusic")->play(-1);
				clickedArea = { 0,0 };
			}

			theButtonMgr->getBtn("Instructions_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("Instructions_Btn")->getClicked())
			{
				currentGameState = gameState::instructions;
				theButtonMgr->getBtn("Instructions_Btn")->setClicked(false);
				theSoundMgr->getSnd("ButtonClick")->play(0);
				clickedArea = { 0,0 };
			}
			
			theButtonMgr->getBtn("Quit_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("Quit_Btn")->getClicked())
			{
				currentGameState = gameState::exit;
				theButtonMgr->getBtn("Quit_Btn")->setClicked(false);
				theSoundMgr->getSnd("ButtonClick")->play(0);
				clickedArea = { 0,0 };
			}
		}
		break;

		case (gameState::instructions):
		{
			theButtonMgr->getBtn("Menu_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("Menu_Btn")->getClicked())
			{
				currentGameState = gameState::mainMenu;
				theButtonMgr->getBtn("Menu_Btn")->setClicked(false);
				theSoundMgr->getSnd("ButtonClick")->play(0);
				clickedArea = { 0,0 };
			}
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
					SDL_Point flipperRotPoint = leftFlipper.GetFlipperRotationPoint();
					SDL_Point ballCenterPos = { (ballSprite.getSpritePos().x + ballSprite.getSpriteCentre().x),(ballSprite.getSpritePos().y + ballSprite.getSpriteCentre().y) };

					float forceMagnitude = sqrt(((flipperRotPoint.x - ballCenterPos.x)*(flipperRotPoint.x - ballCenterPos.x)) + ((flipperRotPoint.y - ballCenterPos.y)*(flipperRotPoint.y - ballCenterPos.y)));
					forceMagnitude /= 25;
					ballSprite.addForceToBall((1 * forceMagnitude), (-4 * forceMagnitude));
				}

			}
			if (ballSprite.CollidedWithPixels({ (ballSprite.getSpritePos().x + ballSprite.getSpriteCentre().x),(ballSprite.getSpritePos().y + ballSprite.getSpriteCentre().y) }, rightFlipper.GetCollisionPoints()))
			{
				//Collision Reflection
				ballSprite.CalculateCollisions(rightFlipper.GetRotatedCollisionPoints());

				//Force Addition
				if (rightFlipper.GetAnimationState())
				{
					SDL_Point flipperRotPoint = rightFlipper.GetFlipperRotationPoint();
					SDL_Point ballCenterPos = { (ballSprite.getSpritePos().x + ballSprite.getSpriteCentre().x),(ballSprite.getSpritePos().y + ballSprite.getSpriteCentre().y) };

					float forceMagnitude = sqrt(((flipperRotPoint.x - ballCenterPos.x)*(flipperRotPoint.x - ballCenterPos.x))+((flipperRotPoint.y - ballCenterPos.y)*(flipperRotPoint.y - ballCenterPos.y)));
					forceMagnitude /= 25;
					ballSprite.addForceToBall((-1 * forceMagnitude), (-4 * forceMagnitude));
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

			//Checking lose condition
			if (ballSprite.getSpritePos().y > (1100))
			{
				//Changing Scene
				currentGameState = gameState::hiScores;

				//Updating HiScores
				theScoreMgr->SetHiScores(gameScore);

				vector<int> scores = theScoreMgr->GetHiScores();

				theTextureMgr->deleteTexture("score1");
				string s = "1: " + to_string(scores[0]);
				theTextureMgr->addTexture("score1", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				
				theTextureMgr->deleteTexture("score2");
				s = "2: " + to_string(scores[1]);
				theTextureMgr->addTexture("score2", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				
				theTextureMgr->deleteTexture("score3");
				s = "3: " + to_string(scores[2]);
				theTextureMgr->addTexture("score3", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				
				theTextureMgr->deleteTexture("score4");
				s = "4: " + to_string(scores[3]);
				theTextureMgr->addTexture("score4", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				
				theTextureMgr->deleteTexture("score5");
				s = "5: " + to_string(scores[4]);
				theTextureMgr->addTexture("score5", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));

				selectedHiScoreButton = 0;

				//Changing Music
				theSoundMgr->getSnd("GameMusic")->stop();
				theSoundMgr->getSnd("HiScoreMusic")->play(-1);
			}
		}
		break;

		case (gameState::hiScores):
		{
			theButtonMgr->getBtn("MainMenu_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("MainMenu_Btn")->getClicked())
			{
				currentGameState = gameState::mainMenu;
				theButtonMgr->getBtn("MainMenu_Btn")->setClicked(false);
				theSoundMgr->getSnd("ButtonClick")->play(0);
				theSoundMgr->getSnd("MenuMusic")->play(-1);
				clickedArea = { 0,0 };
			}

			theButtonMgr->getBtn("Restart_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("Restart_Btn")->getClicked())
			{
				ResetGame(theRenderer);
				currentGameState = gameState::gameScene;
				theButtonMgr->getBtn("Restart_Btn")->setClicked(false);
				theSoundMgr->getSnd("HiScoreMusic")->stop();
				theSoundMgr->getSnd("ButtonClick")->play(0);
				theSoundMgr->getSnd("GameMusic")->play(-1);
				clickedArea = { 0,0 };
			}
		}
		break;

		case (gameState::exit):
		{
			loop = false;
		}
		break;
	}

	theInputMgr->CheckControllerStatus();
	theInputMgr->InputDelayTimer(deltaTime);
}

bool cGame::getInput(SDL_Renderer* theRenderer)
{
	//Keyboard Inputs
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
				//Keyboard Inputs
				switch (event.type)
				{
					case SDL_KEYDOWN:
					{
						switch (event.key.keysym.sym)
						{
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

	//Checking Gamepad Inputs
	switch (currentGameState)
	{
		case (gameState::mainMenu):
		{
			if (theInputMgr->Gamepad_Up())
			{
				selectedMenuButton--;

				if (selectedMenuButton < 0)
				{
					selectedMenuButton = 2;
				}
			}

			if (theInputMgr->Gamepad_Down())
			{
				selectedMenuButton++;

				if (selectedMenuButton > 2)
				{
					selectedMenuButton = 0;
				}
			}

			if (theInputMgr->Gamepad_A())
			{
				switch (selectedMenuButton)
				{
					case (0):
					{
						ResetGame(theRenderer);
						currentGameState = gameState::gameScene;
						theButtonMgr->getBtn("Play_Btn")->setClicked(false);
						theSoundMgr->getSnd("ButtonClick")->play(0);
						theSoundMgr->getSnd("MenuMusic")->stop();
						theSoundMgr->getSnd("GameMusic")->play(-1);
						clickedArea = { 0,0 };
					}
					break;

					case (1):
					{
						currentGameState = gameState::instructions;
						theButtonMgr->getBtn("Instructions_Btn")->setClicked(false);
						theSoundMgr->getSnd("ButtonClick")->play(0);
						clickedArea = { 0,0 };
					}
					break;

					case (2):
					{
						currentGameState = gameState::exit;
						theButtonMgr->getBtn("Quit_Btn")->setClicked(false);
						theSoundMgr->getSnd("ButtonClick")->play(0);
						clickedArea = { 0,0 };
					}
					break;
				}
			}
		}
		break;

		case (gameState::instructions):
		{
			if (theInputMgr->Gamepad_A())
			{
				currentGameState = gameState::mainMenu;
				theButtonMgr->getBtn("Menu_Btn")->setClicked(false);
				theSoundMgr->getSnd("ButtonClick")->play(0);
				clickedArea = { 0,0 };
			}
		}
		break;

		case (gameState::gameScene):
		{
			if (theInputMgr->Gamepad_RightBumper())
			{
				rightFlipper.Activate();
			}

			if (theInputMgr->Gamepad_LeftBumper())
			{
				leftFlipper.Activate();
			}
		}
		break;

		case (gameState::hiScores):
		{
			if (theInputMgr->Gamepad_Left())
			{
				selectedHiScoreButton--;

				if (selectedHiScoreButton < 0)
				{
					selectedHiScoreButton = 1;
				}
			}

			if (theInputMgr->Gamepad_Right())
			{
				selectedHiScoreButton++;

				if (selectedHiScoreButton > 1)
				{
					selectedHiScoreButton = 0;
				}
			}

			if (theInputMgr->Gamepad_A())
			{
				switch (selectedHiScoreButton)
				{
					case (0):
					{
						ResetGame(theRenderer);
						currentGameState = gameState::gameScene;
						theButtonMgr->getBtn("Restart_Btn")->setClicked(false);
						theSoundMgr->getSnd("HiScoreMusic")->stop();
						theSoundMgr->getSnd("ButtonClick")->play(0);
						theSoundMgr->getSnd("GameMusic")->play(-1);
						selectedMenuButton = 0;
					}
					break;

					case (1):
					{
						currentGameState = gameState::mainMenu;
						theButtonMgr->getBtn("MainMenu_Btn")->setClicked(false);
						theSoundMgr->getSnd("ButtonClick")->play(0);
						theSoundMgr->getSnd("MenuMusic")->play(-1);

					}
					break;
				}
			}
		}
		break;
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

void cGame::ResetGame(SDL_Renderer* theRenderer)
{
	ballSprite.initialise();

	gameScore = 0;
	theTextureMgr->deleteTexture("scoreText");
	string s = "Score: ";
	s += to_string(gameScore);
	theTextureMgr->addTexture("scoreText", theFontMgr->getFont("digital")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 255,255,255,255 }, { 0,0,0,0 }));

}