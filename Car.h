#pragma once
#include "IMapObject.h"

class Car: IMapObject
{
    int xpose;
    int ypose;
    SDL_Texture* carTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;
public:
    Car(const char* texture, SDL_Rednerer* ren);
    ~Car();
    void set_map(Map const&);
    void update();
    void render();
    SDL_Texture* get_texture();
    SDL_Rect* get_texture_position();
    double get_texture_rotation();
};

