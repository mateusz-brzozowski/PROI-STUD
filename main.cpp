#include <SDL.h>

#include <memory>

#include "Car.h"
#include "Map.h"

int main(int argc, const char* argv[]) {
    Map m{};

    auto c1 = std::unique_ptr<Car>(new Car({100, 100}));
    auto c2 =
        std::unique_ptr<AutonomousCar>(new AutonomousCar({20, 20}, c1.get()));

    m.add(std::move(c1));
    m.add(std::move(c2));

    m.init();
    m.loop();
    return 0;
}
