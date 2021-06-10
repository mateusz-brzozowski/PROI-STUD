#include <SDL.h>

#include <cmath>
#include <memory>

#include "Car.h"
#include "Map.h"
#include "Object.h"

int main(int argc, const char* argv[]) {
    MapWithSDL m{};
    m.init();

    // Add the target Car and an Autonomous vehicle
    auto main_car = new Car({700, 300});
    auto autonomous_car = new AutonomousCar({200, 300}, main_car);
    m.add(main_car);
    m.add(autonomous_car);

    // Add obstacles
    m.add(new Lake({232, 220}));
    m.add(new Lake({232, 380}));
    m.add(new Bus({280, 268}));
    m.add(new Bus({280, 332}));
    m.add(new Lake({232, 540}));
    m.add(new Bus({280, 492}));
    m.add(new Bus({280, 428}));

    m.get_window().get_renderer()->add_addon(autonomous_car);
    m.loop();
    return 0;
}
