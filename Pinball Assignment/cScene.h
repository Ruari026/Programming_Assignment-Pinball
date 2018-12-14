/*
=================
cScene.h
- Header file for class definition - SPECIFICATION
- Header file for the scene class
=================
*/

#ifndef _CSCENE_H
#define _CSCENE_H

#include "GameConstants.h"
#include "cTextureMgr.h"
#include "cButtonMgr.h"
#include "cInputMgr.h"

enum class RenderType { ControllerConnected, ControllerNotConnected, Both, Background};

struct RenderItem 
{
	RenderType type;
	float rotationAngle;
	SDL_Rect renderPosition;
};

class cScene
{
private:
	cTextureMgr* theTextureMgr;
	cButtonMgr* theButtonMgr;
	cInputMgr* theInputMgr;

protected:
	map <LPCSTR, RenderItem*> sceneItems;

public:
	cScene();
	void SetupManagers();

	void AddSceneItem(LPCSTR itemName, RenderType newType, float newRotation, SDL_Rect newPosition);
	RenderItem* GetSceneItem(LPCSTR itemName);

	void RenderScene(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	
}; 
#endif