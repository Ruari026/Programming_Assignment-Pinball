/*
=================
- cButton.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cScene.h"

/*
=================================================================
Default Constructor
=================================================================
*/
cScene::cScene()
{
	
}

void cScene::SetupManagers()
{
	theTextureMgr = cTextureMgr::getInstance();
	theButtonMgr = cButtonMgr::getInstance();
	theInputMgr = cInputMgr::getInstance();
	theSoundMgr = cSoundMgr::getInstance();
}

void cScene::AddSceneItem(LPCSTR itemName, RenderConditions newType, float newRotation, SDL_Rect newPosition)
{
	if (!GetSceneItem(itemName)) 
	{
		RenderItem* itemDetails = new RenderItem;
		itemDetails->type = newType;
		itemDetails->rotationAngle = newRotation;
		itemDetails->renderPosition = { newPosition.x, newPosition.y, 1,1 };

		sceneItems.insert(make_pair(itemName, itemDetails));
	}
}

RenderItem* cScene::GetSceneItem(LPCSTR itemName)
{
	map<LPCSTR, RenderItem*>::iterator item = sceneItems.find(itemName);

	if (item != sceneItems.end())
	{
		return item->second;
	}
	else
	{
		return NULL;
	}
}

/*
=================================================================
Rendering all the sprites in the scene
=================================================================
*/
void cScene::RenderScene(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	map<LPCSTR, RenderItem*>::iterator itemIterator = sceneItems.begin();
	
	//Forcing the background to render first
	while (itemIterator != sceneItems.end())
	{
		LPCSTR itemName = itemIterator->first;
		RenderConditions itemType = itemIterator->second->type;

		if (itemType == RenderConditions::Background)
		{
			//Texture Rendering variables
			SDL_Texture* theTexture = theTextureMgr->getTexture(itemName)->getTexture();
			SDL_Rect textureRect = theTextureMgr->getTexture(itemName)->getTextureRect();

			SDL_Rect texturePosition = itemIterator->second->renderPosition;
			texturePosition.w = textureRect.w;
			texturePosition.h = textureRect.h;

			float textureRotation = itemIterator->second->rotationAngle;
			SDL_Point textureCenter = { (int)((theTextureMgr->getTexture(itemName)->getTWidth()) / 2),(int)((theTextureMgr->getTexture(itemName)->getTHeight()) / 2) };
			FPoint textureScale = { 1,1 };

			//Rendering the texture
			theTextureMgr->getTexture(itemName)->renderTexture(theRenderer, theTexture, &textureRect, &texturePosition, textureRotation, &textureCenter, textureScale);
		}

		itemIterator++;
	}

	//Resetting the iterator
	itemIterator = sceneItems.begin();

	//Rendering all the other items
	while (itemIterator != sceneItems.end())
	{
		LPCSTR itemName = itemIterator->first;
		RenderConditions itemType = itemIterator->second->type;
		
		//Rendering items that aren't affected by the controller's connection state
		if (itemType == RenderConditions::Both)
		{
			if (theTextureMgr->getTexture(itemName))
			{
				//Texture Rendering variables
				SDL_Texture* theTexture = theTextureMgr->getTexture(itemName)->getTexture();
				SDL_Rect textureRect = theTextureMgr->getTexture(itemName)->getTextureRect();

				SDL_Rect texturePosition = itemIterator->second->renderPosition;
				texturePosition.w = textureRect.w;
				texturePosition.h = textureRect.h;

				float textureRotation = itemIterator->second->rotationAngle;
				SDL_Point textureCenter = { (int)((theTextureMgr->getTexture(itemName)->getTWidth()) / 2),(int)((theTextureMgr->getTexture(itemName)->getTHeight()) / 2) };
				FPoint textureScale = { 1,1 };

				//Rendering the texture
				theTextureMgr->getTexture(itemName)->renderTexture(theRenderer, theTexture, &textureRect, &texturePosition, textureRotation, &textureCenter, textureScale);
			}
			if (theButtonMgr->getBtn(itemName))
			{
				//Texture Rendering variables
				SDL_Rect textureRect = theButtonMgr->getBtn(itemName)->getSpriteDimensions();

				SDL_Rect texturePosition = itemIterator->second->renderPosition;
				texturePosition.w = textureRect.w;
				texturePosition.h = textureRect.h;

				FPoint textureScale = { 1,1 };

				//Rendering the texture
				theButtonMgr->getBtn(itemName)->render(theRenderer, &textureRect, &texturePosition, textureScale);
			}
		}

		//Rendering items that are affected by the controller's connection state
		if (theInputMgr->GetControllerStatus())
		{
			//Rendering items that require a controller to be connected
			if (itemType == RenderConditions::ControllerConnected)
			{
				//Texture Rendering variables
				SDL_Texture* theTexture = theTextureMgr->getTexture(itemName)->getTexture();
				SDL_Rect textureRect = theTextureMgr->getTexture(itemName)->getTextureRect();

				SDL_Rect texturePosition = itemIterator->second->renderPosition;
				texturePosition.w = textureRect.w;
				texturePosition.h = textureRect.h;

				float textureRotation = itemIterator->second->rotationAngle;
				SDL_Point textureCenter = { (int)((theTextureMgr->getTexture(itemName)->getTWidth()) / 2),(int)((theTextureMgr->getTexture(itemName)->getTHeight()) / 2) };
				FPoint textureScale = { 1,1 };

				//Rendering the texture
				theTextureMgr->getTexture(itemName)->renderTexture(theRenderer, theTexture, &textureRect, &texturePosition, textureRotation, &textureCenter, textureScale);
			}
		}
		else
		{
			//Rendering items that require no controllers to be connected
			if (itemType == RenderConditions::ControllerNotConnected)
			{
				//Texture Rendering variables
				SDL_Texture* theTexture = theTextureMgr->getTexture(itemName)->getTexture();
				SDL_Rect textureRect = theTextureMgr->getTexture(itemName)->getTextureRect();

				SDL_Rect texturePosition = itemIterator->second->renderPosition;
				texturePosition.w = textureRect.w;
				texturePosition.h = textureRect.h;

				float textureRotation = itemIterator->second->rotationAngle;
				SDL_Point textureCenter = { (int)((theTextureMgr->getTexture(itemName)->getTWidth()) / 2),(int)((theTextureMgr->getTexture(itemName)->getTHeight()) / 2) };
				FPoint textureScale = { 1,1 };

				//Rendering the texture
				theTextureMgr->getTexture(itemName)->renderTexture(theRenderer, theTexture, &textureRect, &texturePosition, textureRotation, &textureCenter, textureScale);
			}
		}

		//Rendering Items that are affected by if the game is muted
		if (theSoundMgr->isMuted())
		{ 
			//Rendering items that the game to be muted
			if (itemType == RenderConditions::GameMuted)
			{
				if (theButtonMgr->getBtn(itemName))
				{
					//Texture Rendering variables
					SDL_Rect textureRect = theButtonMgr->getBtn(itemName)->getSpriteDimensions();

					SDL_Rect texturePosition = itemIterator->second->renderPosition;
					texturePosition.w = textureRect.w;
					texturePosition.h = textureRect.h;

					FPoint textureScale = { 1,1 };

					//Rendering the texture
					theButtonMgr->getBtn(itemName)->render(theRenderer, &textureRect, &texturePosition, textureScale);
				}
			}
		}
		else
		{
			//Rendering items that the game to be muted
			if (itemType == RenderConditions::GameNotMuted)
			{
				if (theButtonMgr->getBtn(itemName))
				{
					//Texture Rendering variables
					SDL_Rect textureRect = theButtonMgr->getBtn(itemName)->getSpriteDimensions();

					SDL_Rect texturePosition = itemIterator->second->renderPosition;
					texturePosition.w = textureRect.w;
					texturePosition.h = textureRect.h;

					FPoint textureScale = { 1,1 };

					//Rendering the texture
					theButtonMgr->getBtn(itemName)->render(theRenderer, &textureRect, &texturePosition, textureScale);
				}
			}
		}
		itemIterator++;
	}
}