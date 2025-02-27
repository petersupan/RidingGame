#include "RidingState.h"
#include "LevelRenderer.h"
#include "LevelCollider.h"
#include "SpriteRenderer.h"
#include "TimeRenderer.h"
#include "TextureRessourceManager.h"
#include "AnimatedTexture.h"
#include "MenuSelector.h"
#include "GameLogic.h"
#include "SDL/sdl_events.h"
#include "Sound.h"
#include <assert.h>

static const char layer0level1[] = "../images/level1/backGround.bmp";
static const char layer0level2[] = "../images/level2/backGround.bmp";

static const char layer1level1[] = "../images/level1/middleGround.bmp";
static const char layer1level2[] = "../images/level2/middleGround.bmp";

static const char layer2level1[] = "../images/level1/foreGround.bmp";
static const char layer2level2[] = "../images/level2/foreGround.bmp";

static const char colllevel1[] = "../images/level1/collision.bmp";
static const char colllevel2[] = "../images/level2/collision.bmp";

static const char obstlevel1[] = "../images/level1/obstacles.bmp";
static const char obstlevel2[] = "../images/level2/obstacles.bmp";

static const char* layer0FileNames[] = {layer0level1, layer0level2};
static const char* layer1FileNames[] = {layer1level1, layer1level2};
static const char* layer2FileNames[] = {layer2level1, layer2level2};
//static const char* colorFileNames[] = {collevel1, collevel2};
static const char* collisionFileNames[] = {colllevel1, colllevel2};
static const char* obstacleFileNames[] = {obstlevel1, obstlevel2};

static const int Levels = 2;

#define SPEED_PER_MILLISECOND 0.1f
#define GRAVITY_PER_MILLISECOND 0.00025f
#define DECELERATION_PER_MILLISECOND 0.0005f
#define JUMP_ACC_NORMAL -0.2f
#define JUMP_ACC_DOUBLE -0.25f
#define JUMP_DOUBLE_HORIZ_DEC 0.5f


RidingState::RidingState() :
	coll(0),
	obstColl(0),
	sprite(0),
	timeRend(),
	scrollX(0),
	scrollY(0),
	posX(5),
	posY(0),
	verticalSpeed(0.0f),
	horizontalSpeed(1.0f),

	speedMult(0.0f),
	height(300),
	state(SS_RIDING),
	timeInSubState(0),
	ridingTime(0.0f),
	doubleJump(false),
	heightOffset(0)
{

}

RidingState::~RidingState()
{

}

void RidingState::Init()
{
	Sound::PlayMusic(true);
	int levelNum = GameLogic::getInstance()->GetLevel();
	Texture* layer0 = TextureRessourceManager::loadTexture(layer0FileNames[levelNum]);
	Texture* layer1 = TextureRessourceManager::loadTexture(layer1FileNames[levelNum]);
	Texture* layer2 = TextureRessourceManager::loadTexture(layer2FileNames[levelNum]);
	Texture* col = TextureRessourceManager::loadTexture(collisionFileNames[levelNum]);

	GameLogic* gl = GameLogic::getInstance();
	int riderNum = gl->GetRider();
	int horseNum = gl->GetHorse();
	AnimatedTexture* sprTex;
	if (riderNum == 0 && horseNum == 0)
		sprTex = TextureRessourceManager::LoadAnimatedTexture("../images/matrixVici.bmp", 22);
	else if (riderNum == 1 && horseNum == 0)
		sprTex = TextureRessourceManager::LoadAnimatedTexture("../images/matrixRainer.bmp", 22);
	else if (riderNum == 2 && horseNum == 0)
		sprTex = TextureRessourceManager::LoadAnimatedTexture("../images/matrixLuky.bmp", 22);
	else if (riderNum == 0 && horseNum == 1)
		sprTex = TextureRessourceManager::LoadAnimatedTexture("../images/gluecksfeeVici.bmp", 22);
	else if (riderNum == 1 && horseNum == 1)
		sprTex = TextureRessourceManager::LoadAnimatedTexture("../images/gluecksfeeRainer.bmp", 22);
	else if (riderNum == 2 && horseNum == 1)
		sprTex = TextureRessourceManager::LoadAnimatedTexture("../images/gluecksfeeLuky.bmp", 22);
    else
	{
		sprTex = 0;
        assert(false);
	}

	Texture* obst = TextureRessourceManager::loadTexture(obstacleFileNames[levelNum]);
	rend.Init(layer2, layer1, layer0);
	coll = LevelCollider(col);
	sprite = SpriteRenderer(sprTex);
	obstColl = ObstacleCollider(obst);
	sprTex->AnimateFrames(0,4, true);
	//timeRend = TimeRenderer();
}

void RidingState::Exit()
{
	TextureRessourceManager::freeTexture(rend.foreGroundTexture);
	TextureRessourceManager::freeTexture(rend.middleGroundTexture);
	TextureRessourceManager::freeTexture(rend.backGroundTexture);

	TextureRessourceManager::freeTexture(coll.collTexture);
	TextureRessourceManager::freeTexture(obstColl.collTexture);

	TextureRessourceManager::freeAnimatedTexture(sprite.GetTexture());
	Sound::PlayMusic(false);
	//Texture* col = TextureRessourceManager::loadTexture(col);
}

void RidingState::Render(Texture* sb)
{
	rend.Render(sb, 0);
	rend.Render(sb, 1);
	sprite.Render(sb);
	rend.Render(sb, 2);
	timeRend.RenderTime(sb, 550, 50, (int)ridingTime);
	timeRend.RenderDescription(sb, 450, 45);
}

void RidingState::SwitchSubState(SubState target)
{
	AnimatedTexture* sprTex = sprite.GetTexture();
	if (state != target)
	{
		switch (target)
		{
		case SS_RIDING:
			doubleJump = false;
			horizontalSpeed = 1.0f;
			sprTex->AnimateFrames(0,4,true);
			break;
		case SS_JUMPING:
			speedMult = 1.0f;
			verticalSpeed = JUMP_ACC_NORMAL;
			break;
		case SS_FALLING:
			speedMult = 1.0f;
			sprTex->AnimateFrames(8,11,true);
			break;
		case SS_FINISHED:

			break;
		}
		state = target;
		timeInSubState = 0.0f;
	}
}

void RidingState::SetHorseSlopeFrames(int floorHeight)
{
	AnimatedTexture* sprTex = sprite.GetTexture();
	//float beforeHeight = (float)coll.GetFloorBelow();
	int difference = coll.GetSlope(floorHeight);
	printf("currentSlope: %i\n", difference);

	if (difference > 8)
	{
		heightOffset = 13;
		sprTex->SetAnimateOffset(17);
	}
	else if (difference < -8)
	{
		heightOffset = 13;
		sprTex->SetAnimateOffset(12);
	}
	else
	{
		heightOffset = 0;
		sprTex->SetAnimateOffset(0);
	}
}

void RidingState::Update(float timePassed)
{
	timeInSubState += timePassed;
	ridingTime += timePassed;
	float dx = horizontalSpeed * timePassed * SPEED_PER_MILLISECOND * speedMult;
	posX += dx;

	float floorHeight = (float)coll.GetFloorBelow();//GetHighestFloor();
	//printf("speedMult: %f\n", speedMult);

	rend.SetScroll((int)posX, (int)posY);
	coll.SetPosition((int)posX + 400, (int)height);
	obstColl.SetPosition((int)posX + 400, (int)height);
	//printf("height: %f\n", height);

	int obstHeight = obstColl.GetObstacleBelow();//GetHighestObstacle();
	if (height > obstHeight)
	{
		SwitchSubState(SS_FALLING);
		//printf("collided \n");
	}
	//else
		//printf("obstHeight: %i\n", obstHeight);

	AnimatedTexture* sprTex = sprite.GetTexture();
	sprTex->Update(timePassed);

	switch (state)
	{
	case SS_RIDING:
		height = floorHeight;
		speedMult = coll.GetCurrentGroundSpeed();
		SetHorseSlopeFrames((int)floorHeight);
		break;
	case SS_JUMPING:
		height = height + verticalSpeed * timePassed;
		if (verticalSpeed < -0.1f)
			sprTex->AnimateFrames(5,5,true);
		else if (verticalSpeed > 0.1f)
			sprTex->AnimateFrames(7,7,true);
		else
			sprTex->AnimateFrames(6,6,true);

		verticalSpeed += GRAVITY_PER_MILLISECOND * timePassed;
		if (height > floorHeight)
		{
			height = floorHeight;
			sprTex->AnimateFrames(0,4,true);
			SwitchSubState(SS_RIDING);
		}
		break;
	case SS_FALLING:
		height = height + verticalSpeed;
		horizontalSpeed -= DECELERATION_PER_MILLISECOND * timePassed;
		horizontalSpeed = horizontalSpeed < 0.0f ? 0.0f : horizontalSpeed;
		verticalSpeed += GRAVITY_PER_MILLISECOND * timePassed;
		if (height > floorHeight)
		{
			height = floorHeight;
		}
		if (timeInSubState > 3000.0f)
		{
			SwitchSubState(SS_RIDING);
		}
    break;
    case SS_FINISHED:

    break;
	}

	sprite.SetPos(400, (int)height+heightOffset, SpriteRenderer::POS_CENTER, SpriteRenderer::POS_BOTTOM);

	if (posX > (rend.foreGroundTexture->mWidth - 800))
	{
		GameLogic* gl = GameLogic::getInstance();
		int currentLevel = GameLogic::getInstance()->GetLevel();
		gl->SetLevel(currentLevel+1);
		gl->SetTime(gl->GetTime() + (int)ridingTime);

		MenuSelector::getInstance()->SwitchToNext();
	}
}

bool RidingState::HandleInput(SDL_Event& event)
{
    switch( event.type )
	{
        /* Look for a keypress */
        case SDL_KEYDOWN:
            /* Check the SDLKey values and move change the coords */
            switch( event.key.keysym.sym )
			{
                case SDLK_LEFT:
					//scrollX = -1;
                    break;
                case SDLK_RIGHT:
					//scrollX = 1;
                    break;
                case SDLK_UP:
					//scrollY = -1;
                    break;
                case SDLK_DOWN:
					//scrollY = 1;
                    break;
				case SDLK_PAGEUP:
                    break;
				case SDLK_PAGEDOWN:
                    break;
				case SDLK_SPACE:
						if (state  == SS_JUMPING)
						{
							if (!doubleJump && timeInSubState < 300.0f)
							{
								horizontalSpeed -= JUMP_DOUBLE_HORIZ_DEC;
								verticalSpeed = JUMP_ACC_DOUBLE;
								doubleJump = true;
							}
						}
						if (state != SS_FALLING)
							SwitchSubState(SS_JUMPING);
					break;
                default:
                    break;
            }
			break;
		case SDL_KEYUP:
			/* Check the SDLKey values and move change the coords */
            switch( event.key.keysym.sym )
			{
                case SDLK_LEFT:
                    //break;	//intentional fallthrough
                case SDLK_RIGHT:
					scrollX = 0;
                    break;
                case SDLK_UP:
                    //break;	//intentional fallthrough
                case SDLK_DOWN:
					scrollY = 0;
                    break;
				case SDLK_PAGEUP:
                    break;
				case SDLK_PAGEDOWN:
                    break;
                default:
                    break;
			}
			break;
		}
	return true;
}
