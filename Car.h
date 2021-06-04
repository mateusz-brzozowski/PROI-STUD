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
    RotatedRect m_position;

    /// A pointer to the connected map
    Map* m_map{nullptr};

    /// Name of the BMP with a given texture
    static constexpr char const* m_texture_file = "images/car.bmp";

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
    Car(Vector2D start_position, double angle = 0)
        : m_position(start_position, 0, 0, angle) {}
    void set_map(Map* map) override;
    void update() override;

    SDL_Texture* get_texture() override;
    inline SDL_Rect* get_texture_position() override {
        return &m_texture_position;
    }
    inline double get_texture_rotation() override {
        return m_position.angle_deg();
    }
    inline RotatedRect* get_bbox() override { return &m_position; }
};

/**
 * AutonomousCar is an extension to the Car class,
 * that provides an autonomous car, which follows another Car.
 */
class AutonomousCar : public Car {
   protected:
    /// The car to follow
    IMapObject* m_target;

    /// Max allowed speed of this autonomous car
    double m_speed;

    /// Name of the BMP with a given texture
    static constexpr char const* m_texture_file = "images/car2.bmp";

   public:
    AutonomousCar(Vector2D start_position, IMapObject* target,
                  double speed = 150.0, double angle = 0)
        : Car(start_position, angle), m_target(target), m_speed(speed) {}

    SDL_Texture* get_texture() override;
    void update() override;
};
