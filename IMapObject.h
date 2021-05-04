#pragma once
#include <SDL.h>

// Forward declaration, as Map.h/Map.cpp will include IMapObject.h
class Map;

/**
 * IMapObject describes a single object on the map
 */
class IMapObject {
   public:
    /**
     * set_map will be called when an object is added to the map,
     * as some object might want to talk with other objects.
     */
    virtual void set_map(Map const&) = 0;

    /**
     * update will be called by the map object every frame
     */
    virtual void update() = 0;

    /**
     * get_texture() should return an SDL_Texture* to draw on the screen
     */
    virtual SDL_Texture* get_texture() = 0;

    /**
     * get_texture_position() should return an SDL_Rect* describing where
     * on the screen to put the texture and how big is there texture
     */
    virtual SDL_Rect* get_texture_position() = 0;

    /**
     * get_texture_position() should return the angle in degrees
     * for the texture to be rotated before being drawn on the screen
     */
    virtual double get_texture_rotation() = 0;
};