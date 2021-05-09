#include "Car.h"
#include "Window.h"
#include <stdlib.h>

Car::Car(const char* texture, SDL_Renderer* ren, int x, int y)
{
	renderer = ren;
	carTexture = Window::LoadTexture(texture, ren);
	xpos = x; ypos = y;
}

void Car::set_map(Map const&)
{
	// to do
}

void Car::update()
{
	xpos += rand() % 1;
	xpos -= rand() & 1;
	ypos += rand() % 1;
	ypos -= rand() & 1;
	angle++;

	srcRect.h = 18;
	srcRect.w = 18;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h * 2;
	destRect.w = srcRect.w * 2;
}

void Car::render()
{
	SDL_RenderCopyEx(renderer, carTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}

SDL_Texture* Car::get_texture()
{
	return carTexture;
}

SDL_Rect* Car::get_texture_position()
{
	// to do
}

double Car::get_texture_rotation()
{
	return angle;
}
