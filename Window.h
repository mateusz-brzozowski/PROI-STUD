#pragma once
#include <SDL.h>
#include <stdio.h>

class Window {
private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	SDL_Texture* carTexture;
	SDL_Rect srcR, destR;
	double angle = 0.0;

public:
	Window();
	~Window();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	static SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* renderer);

};
