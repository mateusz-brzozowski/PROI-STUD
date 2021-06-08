#pragma once
#include <SDL.h>

/**
 * RenderAddon is an interface that describes
 * anything that would like to be rendered on an SDL Window.
 */
class IRenderAddon {
   public:
    virtual void render_on(SDL_Renderer*) = 0;
};
