#pragma once

#include <SDL.h>

#include <memory>
#include <vector>

#include "IMapObject.h"
#include "IMapView.h"
#include "Tools.h"

#define KEY_W 1
#define KEY_A 2
#define KEY_S 4
#define KEY_D 8
#define KEY_Space 16

/**
 * Map is a central Class that manages updating all of the attached objects,
 * rendering those objects on attached views, handling events from the
 * underlaying libraries, and all that kind of jazz.
 *
 * The IMap virtual base class already comes with a m_objects and m_views vector
 * attributes, helpers to add IMapObjects and IMapViews and basic
 * implementations of update() and render().
 */
class IMap {
   public:
    using objects_t = std::vector<std::shared_ptr<IMapObject>>;
    using views_t = std::vector<std::shared_ptr<IMapView>>;

   protected:
    /// A vector of all attached IMapObjects
    objects_t m_objects{};

    /// A vector of all attached IMapViews
    views_t m_views{};

   public:
    virtual ~IMap() {}

    //~~~ Object-related methods ~~~//

    /**
     * Add an IMapObject to the map.
     */
    virtual void add(std::shared_ptr<IMapObject> o) {
        o->set_map(this);
        m_objects.push_back(std::move(o));
    }

    /**
     * Add an IMapObject to the map.
     * This overload will immediately wrap the argument in a shared_ptr.
     */
    virtual void add(IMapObject* o) {
        o->set_map(this);
        m_objects.emplace_back(o);
    }

    /**
     * Get the list of all attached objects
     */
    virtual objects_t const& get_objects() { return m_objects; }

    //~~~ View-related methods ~~~//

    /**
     * Add an IMapView to the map.
     */
    virtual void add_view(std::shared_ptr<IMapView> o) {
        m_views.push_back(std::move(o));
    }

    /**
     * Add an IMapView to the map.
     * This overload will immediately wrap the argument in a shared_ptr.
     */
    virtual void add_view(IMapView* o) { m_views.emplace_back(o); }

    /**
     * Get the list of all attached views
     */
    virtual views_t const& get_views() { return m_views; }

    //~~~ Main methods ~~~//

    /**
     * init() is a method that shall be called precisely once,
     * before calling the loop() method.
     *
     * Some of the Map implementations might require setup code,
     * e.g. creating windows.
     */
    virtual void init(){};

    /**
     * loop() is a method that will, presumably,
     * run the Map until an exit or error condition is met.
     *
     * This will involve multiple calls to update() and render().
     */
    virtual void loop() = 0;

    /**
     * update() is a proxy method to update all attached objects.
     */
    virtual void update() {
        for (auto const& obj : m_objects) obj->update();
    }

    /**
     * render() is a method that will call appropiate methods
     * on all of the attached views in order to properly render current scene.
     */
    virtual void render() {
        for (auto const& view : m_views) {
            view->before_render();
            for (auto const& obj : m_objects) view->render(obj.get());
            view->after_render();
        }
    }

    /**
     * load_texture() is a method to load an SDL_Texture from a file,
     * while also saving the texture's dimensions.
     */
    virtual SDL_Texture* load_texture(char const* file, int* w = nullptr,
                                      int* h = nullptr) {
        return nullptr;
    };

    /**
     * get_bounds() is a method to get the maximum allowed position
     * of an object
     */
    virtual Vector2D const get_bounds() { return {-1, -1}; };

    /**
     * get_pressed_keys() is a method that is supposed to return a number
     * encoding the information on key presses.
     *
     * See the KEY_* macros for values corresponding to particular keys.
     */
    virtual unsigned char const get_pressed_keys() { return 0; }
};
