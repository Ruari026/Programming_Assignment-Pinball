/*
== == == == == == == == =
cHiScoreMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the Hi Score Manager class
== == == == == == == == =
*/
#ifndef _CINPUTMGR_H
#define _CINPUTMGR_H
#include "GameConstants.h"

class cInputMgr
{
private:
	static cInputMgr* pInstance;

	bool controllerConnected;

	bool canInput = true;
	float inputTimer = 0;

public:
	static cInputMgr* getInstance();

	cInputMgr();							// Constructor
	~cInputMgr();							// Destructor.

	void CheckControllerStatus();
	bool GetControllerStatus();

	bool Gamepad_Up();
	bool Gamepad_Left();
	bool Gamepad_Down();
	bool Gamepad_Right();

	bool Gamepad_A();

	bool Gamepad_RightBumper();
	bool Gamepad_LeftBumper();

	void InputDelayTimer(float deltaTime);
};

#endif