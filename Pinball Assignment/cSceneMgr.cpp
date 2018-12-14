/*
=====================================================================================
cSceneMgr.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the Scene Manager class
=====================================================================================
*/
#include "cSceneMgr.h"
cSceneMgr* cSceneMgr::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSceneMgr* cSceneMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSceneMgr();
	}
	return cSceneMgr::pInstance;
}


/*
=====================================================================================
- Data constructor initializes the SceneMgr object
- Is always called, thus ensures all SceneMgr objects are in a consistent state.
=====================================================================================
*/
cSceneMgr::cSceneMgr()
{
}


/*
=====================================================================================
- Destructor.
=====================================================================================
*/
cSceneMgr::~cSceneMgr()
{
}

void cSceneMgr::add(LPCSTR btnName, cScene* theBtn)
{
	if (!GetScene(btnName))
	{
		gameScenes.insert(make_pair(btnName, theBtn));
	}
}


/*
=====================================================================================
- return the scene.
=====================================================================================
*/
cScene* cSceneMgr::GetScene(LPCSTR scene)        // return the scene.
{
	map<LPCSTR, cScene*>::iterator btn = gameScenes.find(scene);

	if (btn != gameScenes.end())
	{
		return btn->second;
	}
	else
	{
		return NULL;
	}
}

void cSceneMgr::SetCurrentScene(cScene* newScene)
{
	currentScene = newScene;
}

cScene* cSceneMgr::GetCurrentScene()
{
	return this->currentScene;
}
