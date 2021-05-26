#pragma once
#include <SDL.h>

#include "IMapObject.h"
#include "Map.h"
#include "Tools.h"

/**
 * Car is an IMapObject that represents, well, a Car.
 */
class Car : public IMapObject {
   private:
    const char& m_file;
    SDL_Texture* m_texture{NULL};
    SDL_Rect m_texture_position{0, 0, 0, 0};

    Vector2D m_position{0.0, 0.0};
    double m_angle{0.0};
    int m_count{0};
    Map* m_map{nullptr};


    bool userCar_;
    Car* follow_car_;
    Vector2D dst_position{700.0, 400.0};
    double move_speed = 150.0;

   public:
    Car(const bool userCar, const Vector2D& start_positon,
        const char& file, Car* follow_car = nullptr);
    void set_map(Map* map) override;
    void update() override;
    SDL_Texture* get_texture() override;
    SDL_Rect* get_texture_position() override;
    double get_texture_rotation() override;
};
