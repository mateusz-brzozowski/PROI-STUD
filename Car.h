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
    /// Texture of that car
    SDL_Texture* m_texture{nullptr};

    /// Position of this car's texture
    SDL_Rect m_texture_position{0, 0, 0, 0};

    /// Position of the car
    Vector2D m_position{0.0, 0.0};

    /// Angle of the car
    double m_angle{0.0};

    /// A pointer to the connected map
    Map* m_map{nullptr};

    /**
     * validate_new_position() first checks if the new position is within the
     * bound of the Map, then checks if the new position collides with any other
     * object on the Map, and then finally updates the m_texture_position.
     *
     * @returns true if the new position was deemed valid and the Car was
     * actually moved
     */
    bool validate_new_position(Vector2D);

   public:
    Car(Vector2D start_position) : m_position(start_position) {}
    void set_map(Map* map) override;
    void update() override;

    Vector2D const& get_position() { return m_position; }
    SDL_Texture* get_texture() override;
    SDL_Rect* get_texture_position() override;
    double get_texture_rotation() override;
};

/**
 * AutonomousCar is an extension to the Car class,
 * that provides an autonomous car, which follows another Car.
 */
class AutonomousCar : public Car {
   protected:
    /// The car to follow
    Car* m_follow_car;

    /// Max allowed speed of this autonomous car
    double m_speed;

   public:
    AutonomousCar(Vector2D start_position, Car* car_to_follow,
                  double speed = 150.0)
        : Car(start_position), m_follow_car(car_to_follow), m_speed(speed) {}

    SDL_Texture* get_texture() override;
    void update() override;
};
