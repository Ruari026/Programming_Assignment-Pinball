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
static cSceneMgr* theSceneMgr = cSceneMgr::getInstance();


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
		cScene* mainMenuScene = new cScene();
		mainMenuScene->SetupManagers();

		//Background
		theTextureMgr->addTexture("menuBackground", "Images\\MainMenu\\MainMenu.png");
		menuBkgd.setSpritePos({ 0, 0 });
		menuBkgd.setTexture(theTextureMgr->getTexture("menuBackground"));
		menuBkgd.setSpriteDimensions(theTextureMgr->getTexture("menuBackground")->getTWidth(), theTextureMgr->getTexture("menuBackground")->getTHeight());
		mainMenuScene->AddSceneItem("menuBackground", RenderType::Background, 0, { 0,0 });

		//Controller State
		theTextureMgr->addTexture("controllerTrue", "Images\\MainMenu\\ConnectionTrue.png");
		controllerTrue.setSpritePos({ 25, 825 });
		controllerTrue.setTexture(theTextureMgr->getTexture("controllerTrue"));
		controllerTrue.setSpriteDimensions(theTextureMgr->getTexture("controllerTrue")->getTWidth(), theTextureMgr->getTexture("controllerTrue")->getTHeight());
		mainMenuScene->AddSceneItem("controllerTrue", RenderType::ControllerConnected, 0, { 25,825 });

		theTextureMgr->addTexture("controllerFalse", "Images\\MainMenu\\ConnectionFalse.png");
		controllerFalse.setSpritePos({ 25, 825 });
		controllerFalse.setTexture(theTextureMgr->getTexture("controllerFalse"));
		controllerFalse.setSpriteDimensions(theTextureMgr->getTexture("controllerFalse")->getTWidth(), theTextureMgr->getTexture("controllerFalse")->getTHeight());
		mainMenuScene->AddSceneItem("controllerFalse", RenderType::ControllerNotConnected, 0, { 25,825 });

		//Button Selector
		theTextureMgr->addTexture("buttonSelector", "Images\\MainMenu\\ButtonSelector.png");
		menuSelector.setSpritePos({ 150,550 });
		menuSelector.setTexture(theTextureMgr->getTexture("buttonSelector"));
		menuSelector.setSpriteDimensions(theTextureMgr->getTexture("buttonSelector")->getTWidth(), theTextureMgr->getTexture("buttonSelector")->getTHeight());
		mainMenuScene->AddSceneItem("buttonSelector", RenderType::ControllerConnected, 0, { 150,550 });

		//Scene Buttons
		//Game Start Button
		theTextureMgr->addTexture("menuButton1", "Images\\MainMenu\\PlayButton.png");
		cButton* newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("menuButton1"));
		newBtn->setSpritePos({ 225,550 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("menuButton1")->getTWidth(), theTextureMgr->getTexture("menuButton1")->getTHeight());
		theButtonMgr->add("Play_Btn", newBtn);
		mainMenuScene->AddSceneItem("Play_Btn", RenderType::Both, 0, { 225,550 });

		//Instructions & Controls Button
		theTextureMgr->addTexture("menuButton2", "Images\\MainMenu\\InstructionsButton.png");
		newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("menuButton2"));
		newBtn->setSpritePos({ 225,700 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("menuButton2")->getTWidth(), theTextureMgr->getTexture("menuButton2")->getTHeight());
		theButtonMgr->add("Instructions_Btn", newBtn);
		mainMenuScene->AddSceneItem("Instructions_Btn", RenderType::Both, 0, { 225,700 });

		//Quit Game Button
		theTextureMgr->addTexture("menuButton3", "Images\\MainMenu\\QuitButton.png");
		newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("menuButton3"));
		newBtn->setSpritePos({ 225,850 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("menuButton3")->getTWidth(), theTextureMgr->getTexture("menuButton3")->getTHeight());
		theButtonMgr->add("Quit_Btn", newBtn);
		mainMenuScene->AddSceneItem("Quit_Btn", RenderType::Both, 0, { 225,850 });

		//Scene Sounds
		//Background Music
		theSoundMgr->add("MenuMusic", "Audio\\NewYorkJazzLoop-FoolBoyMedia.wav", soundType::music);
		//Button Clicks
		theSoundMgr->add("ButtonClick", "Audio\\UIConfirmation-InspectorJ.wav", soundType::sfx);

		cout << endl;
		theSceneMgr->add("Main Menu", mainMenuScene);
	}

	//Instructions & Controls Scene Elements
	{
		cout << "- Instructions Scene Items" << endl;
		cScene* instructionsScene = new cScene();
		instructionsScene->SetupManagers();

		//Backgrounds
		theTextureMgr->addTexture("instructionsBackground", "Images\\Instructions\\InstructionsDesign.png");
		instructionsBkgd.setSpritePos({ 0, 0 });
		instructionsBkgd.setTexture(theTextureMgr->getTexture("instructionsBackground"));
		instructionsBkgd.setSpriteDimensions(theTextureMgr->getTexture("instructionsBackground")->getTWidth(), theTextureMgr->getTexture("instructionsBackground")->getTHeight());
		instructionsScene->AddSceneItem("instructionsBackground", RenderType::ControllerConnected, 0, { 0,0 });
		
		theTextureMgr->addTexture("instructionsBackground2", "Images\\Instructions\\InstructionsDesign2.png");
		instructionsBkgd2.setSpritePos({ 0, 0 });
		instructionsBkgd2.setTexture(theTextureMgr->getTexture("instructionsBackground2"));
		instructionsBkgd2.setSpriteDimensions(theTextureMgr->getTexture("instructionsBackground2")->getTWidth(), theTextureMgr->getTexture("instructionsBackground2")->getTHeight());
		instructionsScene->AddSceneItem("instructionsBackground2", RenderType::ControllerNotConnected, 0, { 0,0 });

		//Main Menu Button
		theTextureMgr->addTexture("button2", "Images\\Instructions\\Button.png");
		cButton* newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("button2"));
		newBtn->setSpritePos({ 75,75 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("button2")->getTWidth(), theTextureMgr->getTexture("button2")->getTHeight());
		theButtonMgr->add("Menu_Btn", newBtn);
		instructionsScene->AddSceneItem("Menu_Btn", RenderType::Both, 0, { 75,75 });
		
		cout << endl;
		theSceneMgr->add("Instructions", instructionsScene);
	}

	//Hi Score Scene Elements
	{
		cout << "- Hi Score Scene Items" << endl;
		cScene* hiScoreScene = new cScene();
		hiScoreScene->SetupManagers();

		//Scene Background
		theTextureMgr->addTexture("hiScoresBackground", "Images\\Hi-Scores\\HiScoresDesign.png");
		hiScoresBkgd.setSpritePos({ 0, 0 });
		hiScoresBkgd.setTexture(theTextureMgr->getTexture("hiScoresBackground"));
		hiScoresBkgd.setSpriteDimensions(theTextureMgr->getTexture("hiScoresBackground")->getTWidth(), theTextureMgr->getTexture("hiScoresBackground")->getTHeight());
		hiScoreScene->AddSceneItem("hiScoresBackground", RenderType::Background, 0, { 0,0 });

		//Scene Fonts
		theFontMgr->addFont("scores", "Fonts\\TCB_____.TTF", 48);
		theTextureMgr->addTexture("score1", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "1: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		hiScoreScene->AddSceneItem("score1", RenderType::Both, 0, { 0,0 });

		theTextureMgr->addTexture("score2", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "2: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		hiScoreScene->AddSceneItem("score2", RenderType::Both, 0, { 0,0 });

		theTextureMgr->addTexture("score3", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "3: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		hiScoreScene->AddSceneItem("score3", RenderType::Both, 0, { 0,0 });

		theTextureMgr->addTexture("score4", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "4: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		hiScoreScene->AddSceneItem("score4", RenderType::Both, 0, { 0,0 });

		theTextureMgr->addTexture("score5", theFontMgr->getFont("scores")->createTextTexture(theRenderer, "5: 0", textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
		hiScoreScene->AddSceneItem("score5", RenderType::Both, 0, { 0,0 });


		//Scene Buttons
		//Game Restart Button
		theTextureMgr->addTexture("scoresButton1", "Images\\Hi-Scores\\RestartButton.png");
		cButton* newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("scoresButton1"));
		newBtn->setSpritePos({ 75,800 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("scoresButton1")->getTWidth(), theTextureMgr->getTexture("scoresButton1")->getTHeight());
		theButtonMgr->add("Restart_Btn", newBtn);
		hiScoreScene->AddSceneItem("Restart_Btn", RenderType::Both, 0, { 75,800 });

		//Quit to Main Menu Button
		theTextureMgr->addTexture("scoresButton2", "Images\\Hi-Scores\\MainMenuButton.png");
		newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture("scoresButton2"));
		newBtn->setSpritePos({ 425,800 });
		newBtn->setSpriteDimensions(theTextureMgr->getTexture("scoresButton2")->getTWidth(), theTextureMgr->getTexture("scoresButton2")->getTHeight());
		theButtonMgr->add("MainMenu_Btn", newBtn);
		hiScoreScene->AddSceneItem("MainMenu_Btn", RenderType::Both, 0, { 425,800 });

		//Button Selector
		theTextureMgr->addTexture("buttonSelector2", "Images\\Hi-Scores\\ButtonSelector.png");
		hiScoreSelector.setSpritePos({ 0,800 });
		hiScoreSelector.setTexture(theTextureMgr->getTexture("buttonSelector2"));
		hiScoreSelector.setSpriteDimensions(theTextureMgr->getTexture("buttonSelector2")->getTWidth(), theTextureMgr->getTexture("buttonSelector2")->getTHeight());
		hiScoreScene->AddSceneItem("buttonSelector2", RenderType::ControllerConnected, 0, { 0,800 });

		//Scene Music
		theSoundMgr->add("HiScoreMusic", "Audio\\FunkyTunaGuitar-Abett.wav", soundType::music);

		cout << endl;
		theSceneMgr->add("Hi Scores", hiScoreScene);
	}

	//Gameplay Scene Elements
	{
		cout << "- Gameplay Scene Items" << endl;
		cScene* gameplayScene = new cScene();
		gameplayScene->SetupManagers();

		//Game Background
		theTextureMgr->addTexture("theBackground", "Images\\Background.png");
		gameBkgd.setSpritePos({ 0, 0 });
		gameBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
		gameBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());
		gameplayScene->AddSceneItem("theBackground", RenderType::Background, 0, { 0,0 });

		//The Walls
		//Top Wall
		theTextureMgr->addTexture("horizontalWall", "Images\\Walls1.png");
		wallSprites.push_back(new cWall);
		wallSprites[0]->setSpritePos({ 0,170 });
		wallSprites[0]->setTexture(theTextureMgr->getTexture("horizontalWall"));
		wallSprites[0]->setSpriteDimensions(theTextureMgr->getTexture("horizontalWall")->getTWidth(), theTextureMgr->getTexture("horizontalWall")->getTHeight());
		wallSprites[0]->initialise(theSDLWND, theRenderer, "Images\\Walls1.png");
		gameplayScene->AddSceneItem("horizontalWall", RenderType::Both, 0, { 0,170 });
		//Left Wall
		theTextureMgr->addTexture("verticalWall(L)", "Images\\Walls2.png");
		wallSprites.push_back(new cWall);
		wallSprites[1]->setSpritePos({ 0,0 });
		wallSprites[1]->setTexture(theTextureMgr->getTexture("verticalWall(L)"));
		wallSprites[1]->setSpriteDimensions(theTextureMgr->getTexture("verticalWall(L)")->getTWidth(), theTextureMgr->getTexture("verticalWall(L)")->getTHeight());
		wallSprites[1]->initialise(theSDLWND, theRenderer, "Images\\Walls2.png");
		gameplayScene->AddSceneItem("verticalWall(L)", RenderType::Both, 0, { 0,0 });
		//Right Wall
		theTextureMgr->addTexture("verticalWall(R)", "Images\\Walls2.png");
		wallSprites.push_back(new cWall);
		wallSprites[2]->setSpritePos({ 770,0 });
		wallSprites[2]->setTexture(theTextureMgr->getTexture("verticalWall(R)"));
		wallSprites[2]->setSpriteDimensions(theTextureMgr->getTexture("verticalWall(R)")->getTWidth(), theTextureMgr->getTexture("verticalWall(R)")->getTHeight());
		wallSprites[2]->initialise(theSDLWND, theRenderer, "Images\\Walls2.png");
		gameplayScene->AddSceneItem("verticalWall(R)", RenderType::Both, 0, { 770,0 });


		theTextureMgr->addTexture("leftSlope", "Images\\Corner-L.png");
		theTextureMgr->addTexture("rightSlope", "Images\\Corner-R.png");
		theTextureMgr->addTexture("leftInternal", "Images\\Internal-L.png");
		theTextureMgr->addTexture("rightInternal", "Images\\Internal-R.png");
		//Left Slope
		wallSprites.push_back(new cWall);
		wallSprites[3]->setSpritePos({ 0,870 });
		wallSprites[3]->setTexture(theTextureMgr->getTexture("leftSlope"));
		wallSprites[3]->setSpriteDimensions(theTextureMgr->getTexture("leftSlope")->getTWidth(), theTextureMgr->getTexture("leftSlope")->getTHeight());
		wallSprites[3]->initialise(theSDLWND, theRenderer, "Images\\Corner-L.png");
		gameplayScene->AddSceneItem("leftSlope", RenderType::Both, 0, { 0,870 });
		//Right Slope
		wallSprites.push_back(new cWall);
		wallSprites[4]->setSpritePos({ 500,870 });
		wallSprites[4]->setTexture(theTextureMgr->getTexture("rightSlope"));
		wallSprites[4]->setSpriteDimensions(theTextureMgr->getTexture("rightSlope")->getTWidth(), theTextureMgr->getTexture("rightSlope")->getTHeight());
		wallSprites[4]->initialise(theSDLWND, theRenderer, "Images\\Corner-R.png");
		gameplayScene->AddSceneItem("rightSlope", RenderType::Both, 0, { 500,870 });
		//Left Internal Wall
		wallSprites.push_back(new cWall);
		wallSprites[5]->setSpritePos({ 100,685 });
		wallSprites[5]->setTexture(theTextureMgr->getTexture("leftInternal"));
		wallSprites[5]->setSpriteDimensions(theTextureMgr->getTexture("leftInternal")->getTWidth(), theTextureMgr->getTexture("leftInternal")->getTHeight());
		wallSprites[5]->initialise(theSDLWND, theRenderer, "Images\\Internal-L.png");
		gameplayScene->AddSceneItem("leftInternal", RenderType::Both, 0, { 100,685 });
		//Right Internal Wall
		wallSprites.push_back(new cWall);
		wallSprites[6]->setSpritePos({ 620,685 });
		wallSprites[6]->setTexture(theTextureMgr->getTexture("rightInternal"));
		wallSprites[6]->setSpriteDimensions(theTextureMgr->getTexture("rightInternal")->getTWidth(), theTextureMgr->getTexture("rightInternal")->getTHeight());
		wallSprites[6]->initialise(theSDLWND, theRenderer, "Images\\Internal-R.png");
		gameplayScene->AddSceneItem("rightInternal", RenderType::Both, 0, { 620,685 });

		//The Flippers
		//Left Flipper
		theTextureMgr->addTexture("flipper(L)", "Images\\Flipper.png");
		leftFlipper.setSpritePos({ 155,817 });
		leftFlipper.setTexture(theTextureMgr->getTexture("flipper(L)"));
		leftFlipper.setSpriteDimensions(theTextureMgr->getTexture("flipper(L)")->getTWidth(), theTextureMgr->getTexture("flipper(L)")->getTHeight());
		leftFlipper.SetFlipperType(FlipperType::LEFT);
		leftFlipper.initialise(theSDLWND, theRenderer, "Images\\Flipper.png");
		gameplayScene->AddSceneItem("flipper(L)", RenderType::Both, 0, { 155,817 });
		//Right Flipper
		theTextureMgr->addTexture("flipper(R)", "Images\\Flipper.png");
		rightFlipper.setSpritePos({ (800 - 155 - 200),817 });
		rightFlipper.setTexture(theTextureMgr->getTexture("flipper(R)"));
		rightFlipper.setSpriteDimensions(theTextureMgr->getTexture("flipper(R)")->getTWidth(), theTextureMgr->getTexture("flipper(R)")->getTHeight());
		rightFlipper.SetFlipperType(FlipperType::RIGHT);
		rightFlipper.initialise(theSDLWND, theRenderer, "Images\\Flipper.png");
		gameplayScene->AddSceneItem("flipper(R)", RenderType::Both, 0, { (800-155-200),817 });

		//The Bumpers
		//High Score Bumper
		theTextureMgr->addTexture("bumper500", "Images\\Bumper2.png");
		bumperSprites.push_back(new cBumper);
		bumperSprites[0]->setSpritePos({ 350,275 });
		bumperSprites[0]->setTexture(theTextureMgr->getTexture("bumper500"));
		bumperSprites[0]->setSpriteDimensions(theTextureMgr->getTexture("bumper500")->getTWidth(), theTextureMgr->getTexture("bumper500")->getTHeight());
		bumperSprites[0]->initialise(theSDLWND, theRenderer, "Images\\Bumper2.png");
		bumperSprites[0]->SetBumperValue(500);
		gameplayScene->AddSceneItem("bumper500", RenderType::Both, 0, { 350,275 });
		//Low Score Bumpers
		//Left Side
		theTextureMgr->addTexture("bumper100(L)", "Images\\Bumper1.png");
		bumperSprites.push_back(new cBumper);
		bumperSprites[1]->setSpritePos({ 150,325 });
		bumperSprites[1]->setTexture(theTextureMgr->getTexture("bumper100(L)"));
		bumperSprites[1]->setSpriteDimensions(theTextureMgr->getTexture("bumper100(L)")->getTWidth(), theTextureMgr->getTexture("bumper100(L)")->getTHeight());
		bumperSprites[1]->initialise(theSDLWND, theRenderer, "Images\\Bumper1.png");
		bumperSprites[1]->SetBumperValue(100);
		gameplayScene->AddSceneItem("bumper100(L)", RenderType::Both, 0, { 150,325 });
		//Right Side
		theTextureMgr->addTexture("bumper100(R)", "Images\\Bumper1.png");
		bumperSprites.push_back(new cBumper);
		bumperSprites[2]->setSpritePos({ 550,325 });
		bumperSprites[2]->setTexture(theTextureMgr->getTexture("bumper100(R)"));
		bumperSprites[2]->setSpriteDimensions(theTextureMgr->getTexture("bumper100(R)")->getTWidth(), theTextureMgr->getTexture("bumper100(R)")->getTHeight());
		bumperSprites[2]->initialise(theSDLWND, theRenderer, "Images\\Bumper1.png");
		bumperSprites[2]->SetBumperValue(100);
		gameplayScene->AddSceneItem("bumper100(R)", RenderType::Both, 0, { 550,325 });

		//The Ball
		theTextureMgr->addTexture("theBall", "Images\\Ball.png");
		ballSprite.initialise();
		ballSprite.setTexture(theTextureMgr->getTexture("theBall"));
		ballSprite.setSpriteDimensions(theTextureMgr->getTexture("theBall")->getTWidth(), theTextureMgr->getTexture("theBall")->getTHeight());
		gameplayScene->AddSceneItem("theBall", RenderType::Both, 0, ballSprite.getSpritePos());

		//Loading Game Fonts
		//Score Text
		theFontMgr->addFont("digital", "Fonts\\DS-DIGIB.TTF", 48);
		theTextureMgr->addTexture("scoreText", theFontMgr->getFont("digital")->createTextTexture(theRenderer, "Score: 0", textType::solid, { 255,255,255,255 }, { 0,0,0,0 }));
		gameplayScene->AddSceneItem("scoreText", RenderType::Both, 0, { (WINDOW_WIDTH / 2) - (theTextureMgr->getTexture("scoreText")->getTWidth() / 2), 75, theTextureMgr->getTexture("scoreText")->getTextureRect().w, theTextureMgr->getTexture("scoreText")->getTextureRect().h });
	
		//Scene Sounds
		//Background Music
		theSoundMgr->add("GameMusic", "Audio\\VintageElectroPopLoop-Frankum.mp3", soundType::music);

		theSceneMgr->add("Gameplay", gameplayScene);
	}

	//Setting Starting Scene
	theSceneMgr->SetCurrentScene(theSceneMgr->GetScene("Main Menu"));

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

	theSceneMgr->GetCurrentScene()->RenderScene(theSDLWND, theRenderer);

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
				//Resetting game variables
				ResetGame(theRenderer);

				//Scene Changing
				currentGameState = gameState::gameScene;
				theSceneMgr->SetCurrentScene(theSceneMgr->GetScene("Gameplay"));

				//Button Reset
				theButtonMgr->getBtn("Play_Btn")->setClicked(false);
				clickedArea = { 0,0 };

				//Sound Manipulation
				theSoundMgr->getSnd("ButtonClick")->play(0);
				theSoundMgr->getSnd("MenuMusic")->stop();
				theSoundMgr->getSnd("GameMusic")->play(-1);
			}

			theButtonMgr->getBtn("Instructions_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("Instructions_Btn")->getClicked())
			{
				//Scene Changing
				currentGameState = gameState::instructions;
				theSceneMgr->SetCurrentScene(theSceneMgr->GetScene("Instructions"));

				//Button Resetting
				theButtonMgr->getBtn("Instructions_Btn")->setClicked(false);
				clickedArea = { 0,0 };

				//Sound Manipulation
				theSoundMgr->getSnd("ButtonClick")->play(0);
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
				//Scene Changing
				currentGameState = gameState::mainMenu;
				theSceneMgr->SetCurrentScene(theSceneMgr->GetScene("Main Menu"));

				//Button Resetting
				theButtonMgr->getBtn("Menu_Btn")->setClicked(false);
				clickedArea = { 0,0 };

				//Sound Manipulation
				theSoundMgr->getSnd("ButtonClick")->play(0);
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

					float forceMagnitude = sqrt(((flipperRotPoint.x - ballCenterPos.x)*(flipperRotPoint.x - ballCenterPos.x)) + ((flipperRotPoint.y - ballCenterPos.y)*(flipperRotPoint.y - ballCenterPos.y)));
					forceMagnitude /= 25;
					ballSprite.addForceToBall((-1 * forceMagnitude), (-4 * forceMagnitude));
				}

			}

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
				theSceneMgr->SetCurrentScene(theSceneMgr->GetScene("Hi Scores"));

				//Updating HiScores
				theScoreMgr->SetHiScores(gameScore);

				vector<int> scores = theScoreMgr->GetHiScores();

				theTextureMgr->deleteTexture("score1");
				string s = "1: " + to_string(scores[0]);
				theTextureMgr->addTexture("score1", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				theSceneMgr->GetScene("Hi Scores")->GetSceneItem("score1")->renderPosition = { (WINDOW_WIDTH / 2) - (theTextureMgr->getTexture("score1")->getTWidth() / 2), 190, theTextureMgr->getTexture("score1")->getTextureRect().w, theTextureMgr->getTexture("score1")->getTextureRect().h };
				
				theTextureMgr->deleteTexture("score2");
				s = "2: " + to_string(scores[1]);
				theTextureMgr->addTexture("score2", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				theSceneMgr->GetScene("Hi Scores")->GetSceneItem("score2")->renderPosition = { (WINDOW_WIDTH / 2) - (theTextureMgr->getTexture("score2")->getTWidth() / 2), 290, theTextureMgr->getTexture("score2")->getTextureRect().w, theTextureMgr->getTexture("score2")->getTextureRect().h };

				theTextureMgr->deleteTexture("score3");
				s = "3: " + to_string(scores[2]);
				theTextureMgr->addTexture("score3", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				theSceneMgr->GetScene("Hi Scores")->GetSceneItem("score3")->renderPosition = { (WINDOW_WIDTH / 2) - (theTextureMgr->getTexture("score3")->getTWidth() / 2), 390, theTextureMgr->getTexture("score3")->getTextureRect().w, theTextureMgr->getTexture("score3")->getTextureRect().h };

				theTextureMgr->deleteTexture("score4");
				s = "4: " + to_string(scores[3]);
				theTextureMgr->addTexture("score4", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				theSceneMgr->GetScene("Hi Scores")->GetSceneItem("score4")->renderPosition = { (WINDOW_WIDTH / 2) - (theTextureMgr->getTexture("score4")->getTWidth() / 2), 490, theTextureMgr->getTexture("score4")->getTextureRect().w, theTextureMgr->getTexture("score4")->getTextureRect().h };

				theTextureMgr->deleteTexture("score5");
				s = "5: " + to_string(scores[4]);
				theTextureMgr->addTexture("score5", theFontMgr->getFont("scores")->createTextTexture(theRenderer, s.c_str(), textType::solid, { 0,0,0,255 }, { 0,0,0,0 }));
				theSceneMgr->GetScene("Hi Scores")->GetSceneItem("score5")->renderPosition = { (WINDOW_WIDTH / 2) - (theTextureMgr->getTexture("score5")->getTWidth() / 2), 590, theTextureMgr->getTexture("score5")->getTextureRect().w, theTextureMgr->getTexture("score5")->getTextureRect().h };

				selectedHiScoreButton = 0;

				//Changing Music
				theSoundMgr->getSnd("GameMusic")->stop();
				theSoundMgr->getSnd("HiScoreMusic")->play(-1);
			}

			//Updating Render Information
			theSceneMgr->GetScene("Gameplay")->GetSceneItem("flipper(L)")->renderPosition = leftFlipper.getSpritePos();
			theSceneMgr->GetScene("Gameplay")->GetSceneItem("flipper(L)")->rotationAngle = leftFlipper.GetFlipperRotation();

			theSceneMgr->GetScene("Gameplay")->GetSceneItem("flipper(R)")->renderPosition = rightFlipper.getSpritePos();
			theSceneMgr->GetScene("Gameplay")->GetSceneItem("flipper(R)")->rotationAngle = rightFlipper.GetFlipperRotation();

			theSceneMgr->GetScene("Gameplay")->GetSceneItem("theBall")->renderPosition = ballSprite.getSpritePos();
		}
		break;

		case (gameState::hiScores):
		{
			theButtonMgr->getBtn("MainMenu_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("MainMenu_Btn")->getClicked())
			{
				//Scene Changing
				currentGameState = gameState::mainMenu;
				theSceneMgr->SetCurrentScene(theSceneMgr->GetScene("Main Menu"));

				//Button Reset
				theButtonMgr->getBtn("MainMenu_Btn")->setClicked(false);
				clickedArea = { 0,0 };

				//Sound Manipulation
				theSoundMgr->getSnd("ButtonClick")->play(0);
				theSoundMgr->getSnd("MenuMusic")->play(-1);
			}

			theButtonMgr->getBtn("Restart_Btn")->update(clickedArea);
			if (theButtonMgr->getBtn("Restart_Btn")->getClicked())
			{
				//Resetting Game variables
				ResetGame(theRenderer);

				//Scene Changing
				currentGameState = gameState::gameScene;
				theSceneMgr->SetCurrentScene(theSceneMgr->GetScene("Gameplay"));

				//Button Reset
				theButtonMgr->getBtn("Restart_Btn")->setClicked(false);
				clickedArea = { 0,0 };

				//Sound Manipulation
				theSoundMgr->getSnd("HiScoreMusic")->stop();
				theSoundMgr->getSnd("ButtonClick")->play(0);
				theSoundMgr->getSnd("GameMusic")->play(-1);
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