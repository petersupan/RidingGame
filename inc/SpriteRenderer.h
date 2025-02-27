#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

class Texture;
class AnimatedTexture;
class SpriteRenderer
{
public:
	enum Position
	{
		POS_LEFT,
		POS_CENTER,
		POS_RIGHT,
		POS_TOP,
		POS_BOTTOM
	};

	SpriteRenderer(AnimatedTexture* lev);
	void SetPos(int x, int y) { xPos = x; yPos = y; }
	void SetPos(int x, int y, Position horizPos, Position vertPos);
	void Render(Texture* sb);
	void SetSpriteTexture(AnimatedTexture* spriteTex) { spriteTexture = spriteTex; }
	AnimatedTexture* GetTexture(void) { return spriteTexture; }

private:
	AnimatedTexture* spriteTexture;
	int xPos;
	int yPos;

};

#endif
