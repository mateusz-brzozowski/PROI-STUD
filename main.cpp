#include <SDL.h>

#include <memory>

#include "Car.h"
#include "Map.h"

int main(int argc, const char* argv[]) {
    Map m{};
    Car u_car(false, {100.0, 50.0});
    m.add(std::move(std::unique_ptr<IMapObject>(&u_car)));
    m.add(std::move(std::unique_ptr<IMapObject>(new Car(true, {10.0, 10.0}, &u_car))));
    m.init();
    m.loop();
    return 0;
}
