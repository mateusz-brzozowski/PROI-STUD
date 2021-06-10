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
`sudo apt install pkg-config googletest libsdl2-dev`

### Arch/Manjaro
`sudo pacman -Syu gtest sdl2`


# Wygląd programu

![](images/screenshot.png)


# Struktura klas

```mermaid
classDiagram
    class IMapView
    <<Interfejs>> IMapView

    class WindowRenderer
    IMapView <|-- WindowRenderer : Implementuje

    class IMap
    <<Interfejs>> IMap

    class MapWithSDL
    IMap <|-- MapWithSDL : Implementuje

    class MapNoGui
    IMap <|-- MapNoGui : Implementuje

    class Window
    WindowRenderer *-- Window : Zawiera
    MapWithSDL --* Window : Zawiera

    IMapView o-- IMap : Korzysta

    class IMapObject
    <<Interfejs>> IMapObject
    IMapObject o-- IMap : Korzysta

    IMapObject <|-- Car : Implementuje
    Car <|-- AutonomousCar : Dziedziczy
    IMapObject <|-- Object : Implementuje
    Object <|-- Bus : Dziedziczy
    Object <|-- Bush : Dziedziczy
    Object <|-- Hole : Dziedziczy
    Object <|-- Lake : Dziedziczy

    class IRendererAddon
    <<Interfejs>> IRendererAddon
    AutonomousCar --|> IRendererAddon : Implementuje
    WindowRenderer --o IRendererAddon : Korzysta

    class Vector2D
    class RotatedRect
```

Podział odpowiedzialności:
1. Mikołaj Kuranowski
    - Interfejs IMap
    - Interfejs IMapView
    - Interfejs IMapObject
    - Klasa MapNoGui
    - Klasa MapWithSDL
    - Klasa Window
    - Klasa WindowRenderer
    - CMakeLists
2. Mateusz Brzozowski
    - Klasa Car
    - Klasa AutonomousCar
3. Jan Rusak
    - Klasa Object
    - Klasa Bus
    - Klasa Bush
    - Klasa Hole
    - Klasa Lake
    - Testy

Opisy klas znajdują się w headerach i są kompatybilne z generatorem dokumentacji
`doxygen`. Dołączono również przykładowy plik `.doxygen-config`.
