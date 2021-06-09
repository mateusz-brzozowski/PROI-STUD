# 203.1 Pojazd Autonomiczny

Skład zespołu: Mateusz Brzozowski, Mikołaj Kuranowski, Jan Rusak


# Budowanie projektu

Projekt korzysta z systemu CMake.

Problem występuje jednak z zarządzaniem zewnętrznymi bibliotekami - obecnie CMakeLists.txt
zawiera różne ścieżki rozwiązywania zależności: na Windowsie za pomocą `vcpkg` i `pkg-config`
na pozostałych platformach.

Lista wymaganych pakietów

### Windows (vcpkg)
`vcpkg install gtest:x64-windows sdl2:x64-windows`

### Debian/Ubuntu
`sudo apt install googletest libsdl2-dev`

### Arch/Manjaro
`sudo pacman -Syu gtest sdl2`
