#include "Defines.h"
#include "MainProgram.h"

#include "RidingState.h"
#include "SplashScreenState.h"
#include "RiderSelectState.h"
#include "HorseSelectState.h"
#include "HighScoreState.h"
#include "SDL/sdl_events.h"
#include "Texture.h"
#include <assert.h>


SINGLETONFUNCTIONS(MainProgram);

MainProgram::MainProgram():
    currentStatePtr(0),
	currentState(STATE_SPLASHSCREEN)
{
	SwitchToState(currentState);
}

MainProgram::~MainProgram()
{
	if (currentStatePtr != 0)
	{
		currentStatePtr->Exit();
		SAFE_DELETE( currentStatePtr );
	}
}

void MainProgram::Update(float timePassed)
{
	currentStatePtr->Update(timePassed);
}

void MainProgram::Render(Texture* sb)
{
	currentStatePtr->Render(sb);
}

bool MainProgram::HandleInput(SDL_Event& ev)
{
	currentStatePtr->HandleInput(ev);

	return true;
}

void MainProgram::SwitchToState(State target)
{
	//if (currentState != target)
	if (currentStatePtr != 0)
	{
		currentStatePtr->Exit();
   		SAFE_DELETE( currentStatePtr );
	}
	switch (target)
	{
	case STATE_RIDING:
		currentStatePtr = SAFE_NEW RidingState();
		currentStatePtr->Init();
		break;
	case STATE_SPLASHSCREEN:
		currentStatePtr = SAFE_NEW SplashScreenState();
		currentStatePtr->Init();
		break;
	case STATE_RIDERSELECT:
		currentStatePtr = SAFE_NEW RiderSelectState();
		currentStatePtr->Init();
		break;
	case STATE_HORSESELECT:
		currentStatePtr = SAFE_NEW HorseSelectState();
		currentStatePtr->Init();
		break;
	case STATE_HIGHSCORE:
		currentStatePtr = SAFE_NEW HighscoreState();
		currentStatePtr->Init();
		break;
	default:
		assert(false);
		break;
	}
	currentState = target;
}
