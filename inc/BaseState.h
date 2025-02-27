#ifndef BASESTATE_H
#define BASESTATE_H

//#include "MenuSelector.h"

class Texture;

class MenuSelector;
//enum Menu;

union SDL_Event;

class BaseState
{
public:
	virtual ~BaseState() {}
	virtual void Render(Texture* sb) = 0;
	virtual void Update(float timePassed) = 0;
	virtual bool HandleInput(SDL_Event& event) = 0;
	virtual void Init() = 0;
	virtual void Exit() = 0;

	//void SetNextMenu(Menu next) { nextMenu = next; }
private:
	//Menu nextMenu;
};

#endif
