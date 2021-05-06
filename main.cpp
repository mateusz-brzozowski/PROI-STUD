#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <cstdio>
#include "Window.h"

int main(int argc, const char* argv[]) {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;

    Window window{};
	window.init("SIEMA", 800, 600, false);
	while (window.running())
	{
        frameStart = SDL_GetTicks();

		window.handleEvents();
		window.update();
		window.render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
	}
	window.clean();
    return 0;
}
