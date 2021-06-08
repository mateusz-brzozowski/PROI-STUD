#include <SDL.h>

#include <cmath>
#include <memory>

#include "Car.h"
#include "Map.h"
#include "Object.h"

int main(int argc, const char* argv[]) {
    MapWithSDL m{};

    auto main_car = new Car({200, 200});
    auto autonomous_car = new AutonomousCar({20, 200}, main_car);

    m.add(main_car);
    m.add(autonomous_car);
    m.add(new Hole({100, 100}));
    m.add(new Lake({250, 100}));
    m.add(new Bus({150, 200}));
    m.add(new Bush({300, 200}));

    m.init();
    m.get_window().get_renderer()->add_addon(autonomous_car);
    m.loop();
    return 0;
}
