#ifndef TIMERENDERER_H
#define TIMERENDERER_H

class AnimatedTexture;
class Texture;

class TimeRenderer
{
public:
	TimeRenderer();
	~TimeRenderer();
	void RenderTime(Texture* sb, int x, int y, int timeInMilliseconds);
	void RenderDescription(Texture* sb, int x, int y);

private:
	void RenderNumber(Texture* sb, int number, int x, int y);
	AnimatedTexture* numberTexture;
	Texture* description;
};

#endif
