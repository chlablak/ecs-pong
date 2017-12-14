# ecs-pong
Pong game to practice [ECS](https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system) pattern ([other link](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/)), new [C++17](https://isocpp.org/files/papers/p0636r0.html) features, [SFML](https://www.sfml-dev.org/index.php) library and basic physics.

## Build and run
Build tool required: [scons](http://scons.org/)
```console
$ cd ecs-pong/
$ scons
$ ./ecs-pong
```

## ECS

### Model
/!\ UPDATE NEEDED

Components (with fields):
```text
AI ()
Body (Circle (Radius) | Rectangle (Width, Height))
Bound (Min (X, Y), Max (X, Y))
Contact (Normal (X, Y), Penetration, With)
Input ()
Movement (Velocity (X, Y))
Position (Coords (X, Y))
```

Entities (with components):
```text
Ball (Body, Movement, Position)
Bot (AI, Body, Position)
Player (Body, Input, Position)
Wall (Body, Position)
```

Systems (with components and in order):
```text
Input (Input, Position)
Bound (Bound, Position)
Collision (Body, Movement, Position)
Impulse (Contact, Movement, Position)
Movement (Movement, Position)
Game (Movement, Position)
Render (Body, Position)
```
