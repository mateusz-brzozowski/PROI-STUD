#pragma once
#include "IMapObject.h"

/**
 * IMapView describes an object which can present all objects attached to a Map
 */
class IMapView {
   public:
    virtual ~IMapView() {}

    /**
     * before_renderer() is called every frame, right before
     * further render() calls are made.
     */
    virtual void before_render() {}

    /**
     * render() is called every frame, for every object on a Map.
     */
    virtual void render(IMapObject*) = 0;

    /**
     * after_render() is called right after all render()
     * calls are made.
     */
    virtual void after_render() {}
};
