#pragma once
#include <SDL.h>

#include "Tools.h"

// Forward declaration, as Map.h/Map.cpp will include IMapObject.h
class IMap;

/**
 * IMapObject describes a single object on the map
 */
class IMapObject {
   public:
    virtual ~IMapObject() {}

    /**
     * set_map will be called when an object is added to the map,
     * as some object might want to talk with other objects.
     */
    virtual void set_map(IMap* map) = 0;

    /**
     * update will be called by the map object every frame
     */
    virtual void update() = 0;

    /**
     * get_texture() should return an SDL_Texture* to draw on the screen
     */
    virtual SDL_Texture* get_texture() = 0;

    /**
     * get_texture_position() should return an SDL_FRect* describing where
     * on the screen to put the texture and how big is there texture
     */
    virtual SDL_FRect* get_texture_position() = 0;

    /**
     * get_texture_position() should return the angle in degrees
     * for the texture to be rotated before being drawn on the screen
     */
    virtual double get_texture_rotation() = 0;

    /**
     * get_bbox() should return a pointer to a RotatedRect,
     * which will be treadted as a bounding box for collision detection.
     */
    virtual RotatedRect const* get_bbox() const = 0;

    /**
     * Checks if some IMapObject is a different from another one
     */
    virtual bool operator!=(IMapObject const& other) const {
        return this != &other;
    }
};
