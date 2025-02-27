#ifndef LEVELCOLLIDER_H
#define LEVELCOLLIDER_H


class Texture;
class LevelCollider
{
public:
	LevelCollider(Texture* coll);
	void SetPosition(int x, int y) { xPos = x; yPos = y; }
	void SetColliderTexture(Texture* collTex) { collTexture = collTex; }
	int GetHighestFloor();
	int GetFloorBelow();
	int GetFloorBelow(int x, int y);
	int GetSlope(int currentHeight);
	float GetCurrentGroundSpeed();
	
	Texture* collTexture;

private:
	
	int xPos;
	int yPos;
	int currentGround;

};

#endif

