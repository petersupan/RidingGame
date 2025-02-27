#ifndef OBSTACLECOLLIDER_H
#define OBSTACLECOLLIDER_H


class Texture;
class ObstacleCollider
{
public:
	ObstacleCollider(Texture* coll);
	~ObstacleCollider();
	void SetPosition(int x, int y) { xPos = x; yPos = y; }
	void SetColliderTexture(Texture* collTex) { collTexture = collTex; }
	int GetHighestObstacle();
	int GetObstacleBelow(void);
	
	Texture* collTexture;

private:
	
	int xPos;
	int yPos;

};

#endif
