#pragma once
#include <SDL.h>

#include "IMapObject.h"
#include "Map.h"

class Object : public IMapObject {
   protected:
    const char& m_texture_file;
    SDL_Texture* m_texture{NULL};
    SDL_Rect m_texture_position{0, 0, 0, 0};

    Map* m_map{nullptr};
    double m_angle{0.0};

   public:
    Object(const char& texture_file, SDL_Rect, texture_position)
        : m_texture_file(texture_file), m_texture_position(texture_position) {}
    void set_map(Map* map) override;
    void update() override;

    SDL_Texture* get_texture() override;
    SDL_Rect* get_texture_position() override;
    double get_texture_rotation() override;
};

class Lake : public Object {
   public:
    SDL_Texture* get_texture() override;
};

class Hole : public Object {
};

class Bush : public Object {
};

class Bus : public Object {
   public:
    SDL_Texture* get_texture() override;
};