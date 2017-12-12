# ecs-pong
Pong game to practise the [ECS](https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system) pattern.

## Build and run
```console
$ cd ecs-pong/
$ scons
$ ./ecs-pong
```

## ECS

### Models
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
Collision (Body)
Player (Position, Input)
Bot (Position, AI)
Balls (Position, Movement)
Render (Body)
```
