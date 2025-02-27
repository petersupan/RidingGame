#ifndef HORSESELECTSTATE_H
#define HORSESELECTSTATE_H

#include "BaseState.h"
#include <vector>

class HorseSelectState : public BaseState
{
public:
	HorseSelectState(void);
	virtual ~HorseSelectState(void);
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

