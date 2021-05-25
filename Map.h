#pragma once
#include <SDL.h>

#include <memory>
#include <vector>

#include "IMapObject.h"
#include "IMapView.h"
#include "Window.h"

/**
 * Map is a central object that manages every object on given map
 * and handles connections to objects that view the map and can provide
 * some events back to the map.
 */
class Map {
   private:
    /// Vector of elements on this map
    std::vector<std::unique_ptr<IMapObject>> m_objects;

    /// Vector of all views of this map
    std::vector<std::unique_ptr<IMapView>> m_views;

    /// Window connencted to this map
    Window m_window{};

   public:
    /**
     * Adds an object to the map and assumes ownership of that object.
     */
    void add(std::unique_ptr<IMapObject> object);

    /**
     * Attaches view to a map and assumes ownership of that view.
     */
    inline void add_view(std::unique_ptr<IMapView> view) {
        m_views.push_back(std::move(view));
    }

    /**
     * Initializes connections with all windows.
     */
    void init();

    /**
     * Runs and updates all objects as long as the main Window
     * is running.
     */
    void loop();

    /**
     * Updates all objects
     */
    void update();

    /**
     * Renders all objects on all views
     */
    void render();

    /**
     * Returns a reference to the attached Window
     */
    inline Window& get_window() { return m_window; }

    /**
     * Returns a reference to the list of objects
     */
    inline std::vector<std::unique_ptr<IMapObject>> const& get_objects() {
        return m_objects;
    }
};
