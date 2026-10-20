#include "debug_draw.h"
#include "scene.h"
#include "vec2.h"

#include <algorithm>
#include <cassert>
#include <raylib.h>

// Runs once at startup. assert only fires in Debug builds.
static void runVec2Tests() {

    assert(dot({1,0},{0,1}) == 0);

    assert(cross({1,0},{0,1}) == 1);

    assert(lengthSq({3,4}) == 25);

    assert(length({3,4}) == 5);

    assert(normalize({0,0}).x == 0);
    assert(normalize({0,0}).y == 0);

    Vec2 norm = normalize({3,4});
    float x = norm.x;
    float y = norm.y;
    assert(std::fabs(x - 0.6f)<0.001);
    assert(std::fabs(y - 0.8f)<0.001);

    Vec2 a = {2,5};
    Vec2 b = {1,6};
    Vec2 sub = (a - b);
    assert(sub.x == 1);
    assert(sub.y == -1);
}

int main() {
    runVec2Tests();
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Physics Engine");

    constexpr float kDt = 1.0f / 60.0f;
    constexpr int kMaxStepsPerFrame = 8; // if a frame needs more, drop the backlog instead of spiralling
    constexpr float kPixelsPerMeter = 50.0f;

    int current = 0;
    kScenes[current].reset();
    float accumulator = 0.0f, timeScale = 1.0f;
    bool paused = false;
    double stepMs = 0.0;

    while (!WindowShouldClose()) {
        for (int i = 0; i < std::min(kSceneCount, 9); ++i)
            if (IsKeyPressed(KEY_ONE + i)) { current = i; kScenes[current].reset(); accumulator = 0.0f; }
        if (IsKeyPressed(KEY_R)) { kScenes[current].reset(); accumulator = 0.0f; }
        if (IsKeyPressed(KEY_SPACE)) paused = !paused;
        if (IsKeyPressed(KEY_S)) timeScale = timeScale == 1.0f ? 0.25f : 1.0f;

        double t0 = GetTime();
        if (!paused) {
            accumulator += std::min(GetFrameTime(), 0.25f) * timeScale;
            int steps = 0;
            while (accumulator >= kDt && steps < kMaxStepsPerFrame) {
                kScenes[current].step(kDt);
                accumulator -= kDt;
                ++steps;
            }
            if (steps == kMaxStepsPerFrame) accumulator = 0.0f;
        } else if (IsKeyPressed(KEY_PERIOD)) {
            kScenes[current].step(kDt);
        }
        stepMs = (GetTime() - t0) * 1000.0;

        BeginDrawing();
        ClearBackground({24, 26, 30, 255});
        dd::beginFrame(GetScreenWidth(), GetScreenHeight(), kPixelsPerMeter);
        dd::grid();
        DrawText(TextFormat("[%d] %s%s%s", current + 1, kScenes[current].name,
                            paused ? "  PAUSED" : "", timeScale != 1.0f ? "  SLOW-MO" : ""),
                 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("%d fps   physics %.2f ms", GetFPS(), stepMs), 10, 32, 20, GRAY);
        DrawText("1-9 scene  R reset  Space pause  . step  S slow-mo", 10, 54, 20, GRAY);
        kScenes[current].draw();
        EndDrawing();
    }

    CloseWindow();
}
