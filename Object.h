#pragma once
#include <SDL.h>

#include "IMapObject.h"
#include "Map.h"

class Object : public IMapObject {
   protected:
    char const* m_texture_file;
    SDL_Texture* m_texture{NULL};
    SDL_Rect m_texture_position{0, 0, 0, 0};

    Map* m_map{nullptr};
    double m_angle{0.0};

   public:
    Object(char const* texture_file, SDL_Rect texture_position)
        : m_texture_file(texture_file), m_texture_position(texture_position) {}
    void set_map(Map* map) override;
    void update() override;

    SDL_Texture* get_texture() override;
    SDL_Rect* get_texture_position() override;
    double get_texture_rotation() override;
};

class Lake : public Object {
   public:
    Lake(SDL_Rect texture_position)
        : Object("images/lake.bmp", texture_position) {}
    SDL_Texture* get_texture() override;
};

class Hole : public Object {
   public:
    Hole(SDL_Rect texture_position)
        : Object("images/hole.bmp", texture_position) {}
};

class Bush : public Object {
   public:
    Bush(SDL_Rect texture_position)
        : Object("images/bush.bmp", texture_position) {}
};

class Bus : public Object {
   public:
    Bus(SDL_Rect texture_position)
        : Object("images/bus.bmp", texture_position) {}
    SDL_Texture* get_texture() override;
};
