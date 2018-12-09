/*
== == == == == == == == =
cHiScoreMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the Hi Score Manager class
== == == == == == == == =
*/

#include "cInputMgr.h"

#include <Xinput.h>
#pragma comment(lib, "XInput.lib")

cInputMgr* cInputMgr::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cInputMgr* cInputMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cInputMgr();
	}
	return cInputMgr::pInstance;
}

/*
=================================================================================
Constructor
=================================================================================
*/
cInputMgr::cInputMgr()
{
}

cInputMgr::~cInputMgr()							// Destructor.
{
}


/*
=================================================================================
Setting Up & Checking If Gamepad Input is Possible
=================================================================================
*/
void cInputMgr::CheckControllerStatus()
{
	//Checking if a controller is connected to port 1
	DWORD dwResult;
	for (DWORD i = 0; i < 1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			controllerConnected = true;
		}
		else
		{
			controllerConnected = false;
		}
	}
}

bool cInputMgr::GetControllerStatus()
{
	return controllerConnected;
}


/*
=================================================================================
Checking Player Keyboard Inputs
=================================================================================
*/


/*
=================================================================================
Checking Player Gamepad Inputs
=================================================================================
*/
bool cInputMgr::Gamepad_Up()
{
	if (canInput)
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			if (controllerConnected)
			{
				XINPUT_STATE _controllerState;

				//Get the controller's state
				ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
				XInputGetState(i, &_controllerState);

				//Detecting Input
				if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				{
					canInput = false;
					inputTimer = 0;
					return true;
				}
			}
		}
	}
	return false;
}

bool cInputMgr::Gamepad_Down()
{
	if (canInput)
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			if (controllerConnected)
			{
				XINPUT_STATE _controllerState;

				//Get the controller's state
				ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
				XInputGetState(i, &_controllerState);

				//Detecting Input
				if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				{
					canInput = false;
					inputTimer = 0;
					return true;
				}
			}
		}
	}
	return false;
}

bool cInputMgr::Gamepad_Left()
{
	if (canInput)
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			if (controllerConnected)
			{
				XINPUT_STATE _controllerState;

				//Get the controller's state
				ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
				XInputGetState(i, &_controllerState);

				//Detecting Input
				if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				{
					canInput = false;
					inputTimer = 0;
					return true;
				}
			}
		}
	}
	return false;
}

bool cInputMgr::Gamepad_Right()
{
	if (canInput)
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			if (controllerConnected)
			{
				XINPUT_STATE _controllerState;

				//Get the controller's state
				ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
				XInputGetState(i, &_controllerState);

				//Detecting Input
				if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				{
					canInput = false;
					inputTimer = 0;
					return true;
				}
			}
		}
	}
	return false;
}

bool cInputMgr::Gamepad_A()
{
	if (canInput)
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			if (controllerConnected)
			{
				XINPUT_STATE _controllerState;

				//Get the controller's state
				ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
				XInputGetState(i, &_controllerState);

				//Detecting Input
				if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
				{
					canInput = false;
					inputTimer = 0;
					return true;
				}
			}
		}
	}
	return false;
}

bool cInputMgr::Gamepad_RightBumper()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		if (controllerConnected)
		{
			XINPUT_STATE _controllerState;

			//Get the controller's state
			ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
			XInputGetState(i, &_controllerState);

			//Detecting Input
			if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				return true;
			}
		}
	}
	return false;
}

bool cInputMgr::Gamepad_LeftBumper()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		if (controllerConnected)
		{
			XINPUT_STATE _controllerState;

			//Get the controller's state
			ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
			XInputGetState(i, &_controllerState);

			//Detecting Input
			if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				return true;
			}
		}
	}
	return false;
}


/*
=================================================================================
Checking Player Gamepad Inputs
=================================================================================
*/
void cInputMgr::InputDelayTimer(float deltaTime)
{
	if (!canInput)
	{
		inputTimer += deltaTime;

		if (inputTimer >= 0.2f)
		{
			canInput = true;
		}
	}
}