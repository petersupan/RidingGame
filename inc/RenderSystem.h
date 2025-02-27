#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

class SpriteRenderer;
class RayCastRenderer;
class FloorRenderer;
class SpriteRenderManager;
class Texture;
class Level;

class RenderSystem {
private:

    Texture* mScreenBuf;

public:
    RenderSystem(Texture* screenBuf, Level* level);
    void render();

};

#endif
