#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <memory>

#include "Car.h"
#include "Map.h"

int main(int argc, const char* argv[]) {
    Map m{};
    m.add(std::move(std::unique_ptr<IMapObject>(new Car)));
    m.init();
    m.loop();
    return 0;
}
