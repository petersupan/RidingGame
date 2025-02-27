#ifndef LEVELRENDERER_H
#define LEVELRENDERER_H


class Texture;
class LevelRenderer
{
public:
	LevelRenderer();
	void Init(Texture* foreGround, Texture* middleGround, Texture* backGround);
	void Exit();
	void SetScroll(int x, int y) { xScroll = x; yScroll = y; }
	void Render(Texture* sb, int layer = 0);
	void SetLevelTextures(Texture* foreGround, Texture* middleGround) { foreGroundTexture = foreGround; middleGroundTexture = middleGround; }
	Texture* foreGroundTexture;
	Texture* middleGroundTexture;
	Texture* backGroundTexture;

private:
	int xScroll;
	int yScroll;

};

#endif


