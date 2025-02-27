#ifndef HIGHSCORESTATE_H
#define HIGHSCORESTATE_H

#include "TimeRenderer.h"
#include "BaseState.h"

class Texture;
class AnimatedTexture;

class HighscoreState : public BaseState
{
public:
	void Render(Texture* sb);
	void Update(float timePassed);
	bool HandleInput(SDL_Event& event);
	void Init();
	void Exit();

private:
	struct HighScoreEntry
	{
		int riderNameId;
		int horseNameId;
		int time;
	};
	Texture* backGroundTex;
	Texture* winnerOverlayTex;
	Texture* riderNames[3];
	Texture* horseNames[2];

	HighScoreEntry entries[5];
	TimeRenderer timeRend;
	int currentRank;
	void RenderTexture(Texture* sb, Texture* tex, int x, int y);
};

#endif
