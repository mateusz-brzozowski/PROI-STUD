#pragma once
#include <SDL.h>

#include <memory>
#include <vector>

#include "IMapObject.h"
#include "Window.h"

class Map {
   private:
    std::vector<std::unique_ptr<IMapObject>> m_objects;
    Window m_window;
    void draw(IMapObject* object);

   public:
    Map(const Window& window);
    void add(std::unique_ptr<IMapObject> object);
    void init();
    void render();
    void update();
};
