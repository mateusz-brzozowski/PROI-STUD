#pragma once
#include <SDL.h>

#include "IMapObject.h"
#include "Map.h"

/**
 * Object is an IMapObject representing a static, non-moving object
 */
class Object : public IMapObject {
   protected:
    /// Path to the file with texture
    char const* m_texture_file;

    /// SDL_Texture of that object, if loaded
    SDL_Texture* m_texture{nullptr};

    /// Position of the Object
    SDL_Rect m_texture_position{0, 0, 0, 0};

    /// Rotation of the Object
    double m_angle{0.0};

    /// Link to the underlying Map; required for texture loading
    Map* m_map{nullptr};

   public:
    /**
     * Create an Object.
     *
     * @param texture_file path to a BMP with texture of the object
     * @param texture_position where to place this Object on the Map; w and h
     * attributes are ignored
     * @param angle at which angle place to place this object (in degrees)
     */
    Object(char const* texture_file, SDL_Rect texture_position = {0, 0, 0, 0},
           double angle = 0)
        : m_texture_file(texture_file),
          m_texture_position(texture_position),
          m_angle(angle) {}

    /**
     * Set a link to any Map. An Object without a Map will not be able
     * to load its Texture
     */
    void set_map(Map* map) override;

    /**
     * No-op, since static Object by definition don't udpate
     */
    void update() override;

    SDL_Texture* get_texture() override;
    SDL_Rect* get_texture_position() override;
    double get_texture_rotation() override;
};

/**
 * An Object with a Lake texture
 */
class Lake : public Object {
   public:
    /**
     * Create a static Lake on the map.
     * @param texture_position where to place this Object on the Map; w and h
     * attributes are ignored
     * @param angle at which angle place to place this object (in degrees)
     */
    Lake(SDL_Rect texture_position = {0, 0, 0, 0}, double angle = 0)
        : Object("images/lake.bmp", texture_position, angle) {}
};

/**
 * An Object with a Hole texture
 */
class Hole : public Object {
   public:
    /**
     * Create a static Hole on the map.
     * @param texture_position where to place this Object on the Map; w and h
     * attributes are ignored
     * @param angle at which angle place to place this object (in degrees)
     */
    Hole(SDL_Rect texture_position = {0, 0, 0, 0}, double angle = 0)
        : Object("images/hole.bmp", texture_position, angle) {}
};

/**
 * An Object with a Bush texture
 */
class Bush : public Object {
   public:
    /**
     * Create a static Bush on the map.
     * @param texture_position where to place this Object on the Map; w and h
     * attributes are ignored
     * @param angle at which angle place to place this object (in degrees)
     */
    Bush(SDL_Rect texture_position = {0, 0, 0, 0}, double angle = 0)
        : Object("images/bush.bmp", texture_position, angle) {}
};

/**
 * An Object with a Bus texture
 */
class Bus : public Object {
   public:
    /**
     * Create a static Bus on the map.
     * @param texture_position where to place this Object on the Map; w and h
     * attributes are ignored
     * @param angle at which angle place to place this object (in degrees)
     */
    Bus(SDL_Rect texture_position = {0, 0, 0, 0}, double angle = 0)
        : Object("images/bus.bmp", texture_position, angle) {}
};
