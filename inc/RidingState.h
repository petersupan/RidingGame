#ifndef RIDINGSTATE_H
#define RIDINGSTATE_H

union SDL_Event;

#include "BaseState.h"
#include "LevelRenderer.h"
#include "LevelCollider.h"
#include "SpriteRenderer.h"
#include "ObstacleCollider.h"
#include "TimeRenderer.h"

class Texture;

class RidingState : public BaseState
{
public:
	RidingState();
	~RidingState();

	void Init();
	void Exit();

	void Render(Texture* sb);
	void Update(float timePassed);
	bool HandleInput(SDL_Event& event);


private:

	enum SubState
	{
		SS_RIDING,
		SS_FALLING,
		SS_JUMPING,
		SS_FINISHED
	};
	LevelRenderer rend;
	LevelCollider coll;
	ObstacleCollider obstColl;
	SpriteRenderer sprite;
	TimeRenderer timeRend;
	int scrollX;
	int scrollY;
	float posX;
	float posY;
	float verticalSpeed;
	float horizontalSpeed;
	float speedMult;
	float height;
	SubState state;
	float timeInSubState;
	float ridingTime;
	int heightOffset;

	bool doubleJump;

	void SwitchSubState(SubState target);
	void SetHorseSlopeFrames(int floorHeight);
};

#endif
