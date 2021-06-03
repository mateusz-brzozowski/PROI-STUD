#pragma once
#include <SDL.h>

#include "IMapObject.h"
#include "Map.h"

class Object : public IMapObject {
   protected:
    char const* m_texture_file;
    SDL_Texture* m_texture{nullptr};
    SDL_Rect m_texture_position{0, 0, 0, 0};

    Map* m_map{nullptr};
    double m_angle{0.0};

   public:
    Object(char const* texture_file, SDL_Rect texture_position = {0, 0, 0, 0},
           double angle = 0)
        : m_texture_file(texture_file),
          m_texture_position(texture_position),
          m_angle(angle) {}
    void set_map(Map* map) override;
    void update() override;

    SDL_Texture* get_texture() override;
    SDL_Rect* get_texture_position() override;
    double get_texture_rotation() override;
};

class Lake : public Object {
   public:
    Lake(SDL_Rect texture_position = {0, 0, 0, 0}, double angle = 0)
        : Object("images/lake.bmp", texture_position, angle) {}
};

class Hole : public Object {
   public:
    Hole(SDL_Rect texture_position = {0, 0, 0, 0}, double angle = 0)
        : Object("images/hole.bmp", texture_position, angle) {}
};

class Bush : public Object {
   public:
    Bush(SDL_Rect texture_position = {0, 0, 0, 0}, double angle = 0)
        : Object("images/bush.bmp", texture_position, angle) {}
};

class Bus : public Object {
   public:
    Bus(SDL_Rect texture_position = {0, 0, 0, 0}, double angle = 0)
        : Object("images/bus.bmp", texture_position, angle) {}
};
