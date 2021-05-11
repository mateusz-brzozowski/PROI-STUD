#pragma once
#include <SDL.h>

#include <memory>
#include <vector>

#include "IMapObject.h"
#include "Window.h"

class Map {
   private:
    std::vector<std::unique_ptr<IMapObject>> map;
    Window window;
    void draw(const std::unique_ptr<IMapObject>& object);

   public:
    Map(const Window& window_);
    ~Map();
    void add(std::unique_ptr<IMapObject>& object);
    void init();
    void render();
    void update();
};
