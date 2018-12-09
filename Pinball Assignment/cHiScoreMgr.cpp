/*
== == == == == == == == =
cHiScoreMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the Hi Score Manager class
== == == == == == == == =
*/

#include "cHiScoreMgr.h"

#include <fstream>

cHiScoreMgr* cHiScoreMgr::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cHiScoreMgr* cHiScoreMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cHiScoreMgr();
	}
	return cHiScoreMgr::pInstance;
}

/*
=================================================================================
Constructor
=================================================================================
*/
cHiScoreMgr::cHiScoreMgr()
{
}

cHiScoreMgr::~cHiScoreMgr()							// Destructor.
{
}


/*
=================================================================================
Updating the stored Hi Scores
=================================================================================
*/
void cHiScoreMgr::SetHiScores(int newScore)
{
	vector<int> scores = GetHiScores();

	//Checking where the score is to be put in the array
	int position = scores.size();
	for (int i = scores.size() - 1; i >= 0; i--)
	{
		if (newScore > scores[i])
		{
			position = i;
		}
	}

	//Moving all the scores in the array down a spot
	if (position != scores.size())
	{
		int savedInt = newScore;
		for (int i = position; i < scores.size(); i++)
		{

			int savedCurrent = scores[i];
			scores[i] = savedInt;
			savedInt = savedCurrent;
		}
	}

	//Saving Hi-Scores to the file
	ofstream hiScores;
	hiScores.open("Data\\HiScores.txt", ios::trunc);
	for (int i = 0; i < 5; i++)
	{
		hiScores << scores[i] << endl;
	}
	hiScores.close();
}

vector<int> cHiScoreMgr::GetHiScores()
{
	cout << "-Reading From File-" << endl;
	cout << "--------------------" << endl;
	//Reading from text file
	ifstream hiScoresFile("Data\\HiScores.txt");
	string line;
	vector<int> hiScores;

	if (hiScoresFile.is_open())
	{
		//hiScoreArray.clear();
		while (getline(hiScoresFile, line))
		{
			hiScores.push_back(stoi(line));
			cout << line << endl;
		}
		hiScoresFile.close();
	}
	cout << "--------------------" << endl << endl;

	return hiScores;
}
