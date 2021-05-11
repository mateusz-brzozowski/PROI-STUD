#pragma once
#include "IMapObject.h"

class Car : IMapObject {
    int xpos;
    int ypos;
    SDL_Texture* carTexture;
    SDL_Rect srcRect{}, destRect{};
    SDL_Renderer* renderer;
    double angle = 0.0;

   public:
    Car(const char* texture, SDL_Renderer* ren, int x, int y);
    ~Car();
    void set_map(Map const&);
    void update();
    void render();
    SDL_Texture* get_texture();
    SDL_Rect* get_texture_position();
    double get_texture_rotation();
};
