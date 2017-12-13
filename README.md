# ecs-pong
Pong game to practice [ECS](https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system) pattern ([other link](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/)), new [C++17](https://isocpp.org/files/papers/p0636r0.html) features, [SFML](https://www.sfml-dev.org/index.php) library and some collision [physics](https://gamedevelopment.tutsplus.com/series/how-to-create-a-custom-physics-engine--gamedev-12715).

## Build and run
Build tool required: [scons](http://scons.org/)
```console
$ cd ecs-pong/
$ scons
$ ./ecs-pong
```

## ECS

### Models
UPDATE NEEDED

Components (with fields):
```text
Body (Circle (Radius) | Rectangle (Width, Height))
Position (X, Y)
Input ()
AI ()
Movement (DX, DY)
```

Entities (with components):
```text
Player (Body, Position, Input)
Bot (Body, Position, AI)
Ball (Body, Position, Movement)
Wall (Body, Position)
```

Systems (with components and in order):
```text
Collision (Body, Position)
Input (Position, Input)
Bot (Position, AI)
Balls (Position, Movement)
Render (Body, Position)
```
