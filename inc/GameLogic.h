#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Singleton.h"

class GameLogic
{
public:
	SINGLETONDECLARATIONS(GameLogic);

	void SetHorse(int horse) { currentHorse = horse; }
	void SetRider(int rider) { currentRider = rider; }
	void SetLevel(int level) { currentLevel = level; }
	void SetTime(int time)	 { accTime = time; }

	int GetHorse(void) { return currentHorse; }
	int GetRider(void) { return currentRider; }
	int GetLevel(void) { return currentLevel; }
	int GetTime(void)  { return accTime; }
private:
	int currentHorse;
	int currentRider;
	int currentLevel;
	int accTime;
};

#endif
