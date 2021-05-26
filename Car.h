#pragma once
#include <SDL.h>

#include "IMapObject.h"
#include "Map.h"
#include "Tools.h"

/**
 * Car is an IMapObject that represents, well, a Car.
 */
class Car : public IMapObject {
   protected:
    SDL_Texture* m_texture{NULL};
    SDL_Rect m_texture_position{0, 0, 0, 0};

    Vector2D m_position{0.0, 0.0};
    double m_angle{0.0};
    Map* m_map{nullptr};

    void clamp_position();

   public:
    Car(Vector2D start_position) : m_position(start_position) {}
    void set_map(Map* map) override;
    void update() override;

    Vector2D const& get_position() { return m_position; }
    SDL_Texture* get_texture() override;
    SDL_Rect* get_texture_position() override;
    double get_texture_rotation() override;
};

class AutonomousCar : public Car {
   protected:
    Car* m_follow_car;
    double m_speed;

   public:
    AutonomousCar(Vector2D start_position, Car* car_to_follow,
                  double speed = 150.0)
        : Car(start_position), m_follow_car(car_to_follow), m_speed(speed) {}

    SDL_Texture* get_texture() override;
    void update() override;
};
