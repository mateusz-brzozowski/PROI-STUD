#pragma once
#include <SDL.h>

#include "IMap.h"
#include "IMapObject.h"

/**
 * Object is an IMapObject representing a static, non-moving object
 */
class Object : public IMapObject {
   protected:
    /// Path to the file with texture
    char const* m_texture_file;

    /// SDL_Texture of that object, if loaded
    SDL_Texture* m_texture{nullptr};

    /// Position of the texture
    SDL_Rect m_texture_position{0, 0, 0, 0};

    /// Position of the Object
    RotatedRect m_position;

    /// Link to the underlying Map; required for texture loading
    IMap* m_map{nullptr};

   public:
    /**
     * Create an Object.
     *
     * @param texture_file path to a BMP with texture of the object
     * @param center where to place this Object on the Map
     * @param angle at which angle place to place this object (in radians)
     */
    Object(char const* texture_file, Vector2D center = {0, 0}, double angle = 0)
        : m_texture_file(texture_file), m_position(center, 0, 0, angle) {}

    /**
     * Set a link to any Map. An Object without a Map will not be able
     * to load its Texture
     */
    void set_map(IMap* map) override;

    /**
     * No-op, since static Object by definition don't udpate
     */
    void update() override {}

    SDL_Texture* get_texture() override { return m_texture; }
    SDL_Rect* get_texture_position() override { return &m_texture_position; }
    double get_texture_rotation() override { return m_position.angle_deg(); }
    RotatedRect const* get_bbox() const override { return &m_position; }
};

/**
 * An Object with a Lake texture
 */
class Lake : public Object {
   public:
    /**
     * Create a static Lake on the map.
     * @param center where to place this Object on the Map
     * @param angle at which angle place to place this object (in radians)
     */
    Lake(Vector2D center = {0, 0}, double angle = 0)
        : Object("images/lake.bmp", center, angle) {}
};

/**
 * An Object with a Hole texture
 */
class Hole : public Object {
   public:
    /**
     * Create a static Hole on the map.
     * @param center where to place this Object on the Map
     * @param angle at which angle place to place this object (in radians)
     */
    Hole(Vector2D center = {0, 0}, double angle = 0)
        : Object("images/hole.bmp", center, angle) {}
};

/**
 * An Object with a Bush texture
 */
class Bush : public Object {
   public:
    /**
     * Create a static Bush on the map.
     * @param center where to place this Object on the Map
     * @param angle at which angle place to place this object (in radians)
     */
    Bush(Vector2D center = {0, 0}, double angle = 0)
        : Object("images/bush.bmp", center, angle) {}
};

/**
 * An Object with a Bus texture
 */
class Bus : public Object {
   public:
    /**
     * Create a static Bus on the map.
     * @param center where to place this Object on the Map
     * @param angle at which angle place to place this object (in radians)
     */
    Bus(Vector2D center = {0, 0}, double angle = 0)
        : Object("images/bus.bmp", center, angle) {}
};
