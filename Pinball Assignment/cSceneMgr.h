
/*
==========================================================================
SceneMgr.h
==========================================================================
*/

#ifndef _SCENEMGR_H
#define _SCENEMGR_H

// OpenGL Headers
#include "GameConstants.h"
#include "cScene.h"

using namespace std;

class cSceneMgr
{
private:
	static cSceneMgr* pInstance;
	cScene* currentScene;

protected:
	cSceneMgr();
	~cSceneMgr();
	map <LPCSTR, cScene*> gameScenes;

public:
	static cSceneMgr* getInstance();

	void add(LPCSTR sceneName, cScene* newScene);
	void SetCurrentScene(cScene* newScene);
	cScene* GetScene(LPCSTR scene);
	cScene* GetCurrentScene();
};
#endif
