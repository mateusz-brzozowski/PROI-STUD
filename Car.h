#pragma once
#include <SDL.h>

#include <array>

#include "IMap.h"
#include "IMapObject.h"
#include "IMapView.h"
#include "IRenderAddon.h"
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
    IMap* m_map{nullptr};

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
    void set_map(IMap* map) override;
    void update() override;

    SDL_Texture* get_texture() override { return m_texture; }

    inline SDL_Rect* get_texture_position() override {
        return &m_texture_position;
    }

    inline double get_texture_rotation() override {
        return m_position.angle_deg();
    }

    inline RotatedRect const* get_bbox() const override { return &m_position; }
};

/**
 * AutonomousCar is an extension to the Car class,
 * that provides an autonomous car, which follows another Car.
 *
 * This car also implements IRenderAddon, which will render
 * the sensors on any SDL_Renderer.
 */
class AutonomousCar : public Car, public IRenderAddon {
   protected:
    // --- sub-classes --- ///

    /// Half of the collision-detecting sensor length
    static constexpr int SENSOR_LEN_HALF = 18;

    /**
     * Sensor is a helper class for collsion sensors
     * of the AutonomousCar.
     */
    struct Sensor {
        Vector2D const center_offset;  // Offset from the car center
        double const angle_offset;     // Angle offset, based on the car's angle
        double const avoid_factor;     // Turning factor on a detection
        RotatedRect bbox{{0, 0}, SENSOR_LEN_HALF, 0.5};

        Sensor(Vector2D co = {0, 0}, double ao = 0, double af = 0, int ofi = 0)
            : center_offset(co), angle_offset(ao), avoid_factor(af) {}
    };

    // --- attributes --- //

    /// The car to follow
    IMapObject* m_target;

    /// Max allowed speed of this autonomous car
    double m_speed;

    /// Name of the BMP with a given texture
    static constexpr char const* m_texture_file = "images/car2.bmp";

    /// List of sensors
    std::vector<Sensor> m_sensors{};

    // --- protected methods --- //

    /**
     * checks whether a particular sensor collides with anything.
     *
     * @returns the pointer to a colliding object's bbox; nullptr on no
     * collision
     */
    RotatedRect const* sensor_collides(Sensor const&) const;

    /**
     * moves all of the sensors to match AutonomousCar's position
     */
    void update_sensor_pos();

    /**
     * Fills the m_sensors vector; needs to be called
     * after the texture dimensions are known.
     */
    void initialize_sensors();

   public:
    AutonomousCar(Vector2D start_position, IMapObject* target,
                  double speed = 1.0, double angle = 0)
        : Car(start_position, angle), m_target(target), m_speed(speed) {}

    void set_map(IMap* map) override;
    void update() override;
    void render_on(SDL_Renderer*) override;
};
