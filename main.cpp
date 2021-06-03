#include <SDL.h>

#include <memory>

#include "Car.h"
#include "Map.h"
#include "Object.h"

int main(int argc, const char* argv[]) {
    Map m{};

    auto c1 = std::unique_ptr<Car>(new Car({500, 500}));
    auto c2 =
        std::unique_ptr<AutonomousCar>(new AutonomousCar({20, 20}, c1.get()));

    m.add(std::move(c1));
    m.add(std::move(c2));
    m.add(std::move(std::unique_ptr<IMapObject>(new Hole({100, 100, 1, 1}))));
    m.add(std::move(std::unique_ptr<IMapObject>(new Lake({250, 100, 1, 1}))));
    m.add(std::move(std::unique_ptr<IMapObject>(new Bus({150, 200, 1, 1}))));
    m.add(std::move(std::unique_ptr<IMapObject>(new Bush({300, 200, 1, 1}))));

    m.init();
    m.loop();
    return 0;
}
