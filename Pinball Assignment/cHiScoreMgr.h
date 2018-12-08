/*
== == == == == == == == =
cHiScoreMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the Hi Score Manager class
== == == == == == == == =
*/
#ifndef _CHISCOREMGR_H
#define _CHISCOREMGR_H
#include "GameConstants.h"

class cHiScoreMgr
{
private:
	static cHiScoreMgr* pInstance;

public:
	static cHiScoreMgr* getInstance();

	cHiScoreMgr();							// Constructor
	~cHiScoreMgr();							// Destructor.

	vector<int> GetHiScores();
	void SetHiScores(int newScore);

};

#endif