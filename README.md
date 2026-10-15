# Physics Engine

A 2D rigid-body physics engine in C++, written from scratch to learn how engines like Box2D work under the hood. Rendering and input use [raylib](https://www.raylib.com/); the physics itself has no dependencies.

> **Status:** just started. The app shell, fixed-timestep loop and debug drawing are in place; the physics is next.

## Roadmap

- [ ] Vector math
- [ ] Particles: gravity, semi-implicit Euler, wall bounces
- [ ] Circle collisions: detection, impulse response, restitution, positional correction
- [ ] Boxes: AABB vs circle, mass and inverse mass, static bodies
- [ ] Rotation: oriented boxes with SAT, angular impulse, friction
- [ ] Broadphase (spatial hash), demo scenes, stability tuning

**Goal:** a stack of 10 boxes that comes to rest without jitter.

## Build

Requires CMake 3.20+ and a C++20 compiler. raylib is downloaded automatically.

```
cmake -S . -B build
cmake --build build --config Debug
```

Or open the folder in Visual Studio 2022+ (CMake support built in) and run `physics.exe`.

## Controls

| Key | Action |
|-----|--------|
| 1-9 | Switch scene |
| R | Reset scene |
| Space | Pause |
| . | Step one frame (while paused) |
| S | Toggle slow-mo |

## Layout

- `src/main.cpp`: window, fixed 60 Hz timestep, input, HUD
- `src/debug_draw.*`: world-space drawing (meters, y-up)
- `src/scenes.cpp`: demo scenes
- Physics code: coming soon

## License

[MIT](LICENSE)
