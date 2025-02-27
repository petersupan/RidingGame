#ifndef SPLASHSCREENSTATE_H
#define SPLASHSCREENSTATE_H

#include "BaseState.h"

class SplashScreenState : public BaseState
{
	void Render(Texture* sb);
	void Update(float timePassed);
	bool HandleInput(SDL_Event& event);
	void Init();
	void Exit();

private:
	Texture* screenTex;
};

#endif
