#include "Window.h"
#include <iostream>

void Window::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialization...\n";
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

		if (window)
			std::cout << "Window created\n";

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created\n";
		}

		isRunning = true;
	}
	else
		isRunning = false;

	carTexture = LoadTexture("images/car.bmp", renderer);
}
void Window::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Window::update()
{
	cnt++;
	destR.h = 18;
	destR.w = 18;
	destR.x = cnt;
	destR.y = 0;
	angle = cnt;
}
void Window::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopyEx(renderer, carTexture, NULL, &destR, angle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
}


void Window::clean()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit;
	std::cout << "Window closed\n";
}
bool Window::running()
{
	return isRunning;
}

SDL_Renderer* Window::get_renderer()
{
	return renderer;
}

SDL_Texture* Window::LoadTexture(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface* tmpSurface = SDL_LoadBMP(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return texture;
}
