#ifndef MAINPROGRAM_H
#define MAINPROGRAM_H

#include "Singleton.h"

union SDL_Event;

class BaseState;
class Texture;

class MainProgram
{
public:
	enum State
	{
		STATE_RIDING,
		STATE_SPLASHSCREEN,
		STATE_RIDERSELECT,
		STATE_HORSESELECT,
		STATE_HIGHSCORE
	};
	SINGLETONDECLARATIONS(MainProgram);
	~MainProgram();
	void SwitchToState(State target);

	void Render(Texture* sb);
	void Update(float timePassed);
	bool HandleInput(SDL_Event& event);
private:
	BaseState* currentStatePtr;
	State currentState;
};

#endif
