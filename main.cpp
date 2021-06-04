#include <SDL.h>

#include <cmath>
#include <memory>

#include "Car.h"
#include "Map.h"
#include "Object.h"

int main(int argc, const char* argv[]) {
    Map m{};

    auto main_car = new Car({500, 500});

    m.add(main_car);
    m.add(new AutonomousCar({20, 20}, main_car));
    m.add(new Hole({100, 100}));
    m.add(new Lake({250, 100}));
    m.add(new Bus({150, 200}, M_PI_4));
    m.add(new Bush({300, 200}));

    m.init();
    m.loop();
    return 0;
}
