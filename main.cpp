#include <SDL.h>

#include <memory>

#include "Car.h"
#include "Map.h"

int main(int argc, const char* argv[]) {
    Map m{};
    Car u_car({100.0, 50.0});
    m.add(std::move(std::unique_ptr<IMapObject>(&u_car)));
    m.add(std::move(std::unique_ptr<IMapObject>(
        new AutonomousCar({10.0, 10.0}, &u_car, 250))));
    m.init();
    m.loop();
    return 0;
}
