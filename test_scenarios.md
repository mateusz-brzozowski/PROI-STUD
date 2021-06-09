```
auto main_car = new Car({700, 300});
auto autonomous_car = new AutonomousCar({200, 300}, main_car);

m.add(main_car);
m.add(autonomous_car);
```

### simple obstacle

```
m.add(new Lake({232, 220}));
m.add(new Lake({232, 380}));
m.add(new Bus({280, 268}));
m.add(new Bus({280, 332}));
```

### closed rectangle (no way out)

```
m.add(new Lake({232, 220}));
m.add(new Lake({232, 380}));
m.add(new Bus({280, 268}));
m.add(new Bus({280, 332}));
m.add(new Lake({168, 220}));
m.add(new Lake({168, 380}));
m.add(new Bus({120, 268}));
m.add(new Bus({120, 332}));
```

### extended version of the first first obstacle

```
m.add(new Lake({232, 220}));
m.add(new Lake({232, 380}));
m.add(new Bus({280, 268}));
m.add(new Bus({280, 332}));
m.add(new Lake({232, 540}));
m.add(new Bus({280, 492}));
m.add(new Bus({280, 428}));
```

### simple tunnel

```
double pos;
m.add(new Lake({232, 220}));
m.add(new Bus({280, 268}));
m.add(new Bus({280, 332}));
m.add(new Lake({168, 220}));


pos = 268;
for (int i = 0; i < 4; ++i) {
    m.add(new Bus({120, pos}));
    pos += 64;
}

pos = 168;
for (int i = 0; i < 7; ++i) {
    m.add(new Lake({pos, 508}));
    pos += 64;
}

m.add(new Lake({328, 348}));
m.add(new Lake({392, 348}));

pos = 332;
for (int i = 0; i < 4; ++i) {
    m.add(new Bus({440, pos}));
    pos -= 64;
}

pos = 460;
for (int i = 0; i < 4; ++i) {
    m.add(new Bus({600, pos}));
    pos -= 64;
}

m.add(new Lake({488, 92}));
m.add(new Lake({552, 92}));
```
