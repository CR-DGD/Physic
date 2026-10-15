#pragma once

// A demo scene. main.cpp calls reset() on load and on R, step() at a fixed 60 Hz, draw() every frame.
struct Scene {
    const char* name;
    void (*reset)();
    void (*step)(float dt);
    void (*draw)();
};

// Defined in scenes.cpp. Keys 1-9 pick a scene.
extern const Scene kScenes[];
extern const int kSceneCount;
