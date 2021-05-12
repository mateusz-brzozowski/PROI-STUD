#pragma once
#include <SDL.h>

#include "IMapObject.h"
#include "Map.h"
#include "Tools.h"

class Car : public IMapObject {
   private:
    SDL_Texture* m_texture{NULL};
    SDL_Rect m_texture_position{0, 0, 0, 0};

    Vector2D m_position{0.0, 0.0};
    double m_angle{0.0};
    int m_count{0};
    Map* m_map{nullptr};

   public:
    void set_map(Map* map) override;
    void update() override;
    SDL_Texture* get_texture() override;
    SDL_Rect* get_texture_position() override;
    double get_texture_rotation() override;
};
