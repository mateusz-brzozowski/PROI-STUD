#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <cstdio>
#include "Window.h"

int main(int argc, const char* argv[]) {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;

	Window* window = nullptr;
	window = new Window();
	window->init("SIEMA", 800, 600, false);
	while (window->running())
	{
        frameStart = SDL_GetTicks();

		window->handleEvents();
		window->update();
		window->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
	}
	window->clean();

    //if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    //    return 1;
    //}

    //SDL_Window* window = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    //                                      640, 480, SDL_WINDOW_SHOWN);

    //if (window == NULL) {
    //    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    //    return 1;
    //}
    //SDL_Surface* surface = SDL_GetWindowSurface(window);
    //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0xff, 0x00));
    //SDL_UpdateWindowSurface(window);
    //SDL_Delay(2000);
    //SDL_DestroyWindow(window);
    //SDL_Quit();
    return 0;
}
