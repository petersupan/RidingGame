#ifndef RIDERSELECTSTATE_H
#define RIDERSELECTSTATE_H

#include "BaseState.h"
#include <vector>

class RiderSelectState : public BaseState
{
public:
	RiderSelectState();
	virtual ~RiderSelectState();
	void Render(Texture* sb);
	void Update(float timePassed);
	bool HandleInput(SDL_Event& event);
	void Init();
	void Exit();

private:
	std::vector<Texture*> textures;
	//Texture* screenTex;
	int currentActive;
	int nrTextures;

	void ChangeActive(int value);
};

#endif

