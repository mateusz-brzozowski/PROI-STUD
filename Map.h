#pragma once
#include <SDL.h>

#include <memory>
#include <vector>

#include "IMapObject.h"
#include "Window.h"

class Map {
   private:
    std::vector<std::unique_ptr<IMapObject>> m_objects;
    Window m_window{};
    void draw(IMapObject* object);

   public:
    void add(std::unique_ptr<IMapObject> object);
    void init();
    void loop();

    void update();
    void render();

    inline Window& get_window() { return m_window; }
};
