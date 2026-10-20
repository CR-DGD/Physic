#include "debug_draw.h"
#include "scene.h"
#include "vec2.h"

// Scene 1 only checks that drawing works. Delete it once real scenes exist.
namespace draw_test {
    static float t = 0.0f;
    static void reset() { t = 0.0f; }
    static void step(float dt) { t += dt; }
    static void draw() {
        dd::circle(-4, 2, 1.0f, t, dd::Blue);
        dd::box(0, 2, 1.0f, 0.5f, t * 0.5f, dd::Green);
        dd::arrow(4, 1, 1.5f, 2.0f);
        float mx, my;
        dd::mouseWorld(mx, my);
        dd::point(mx, my);
        dd::hud("mouse: %.2f, %.2f m", mx, my);
    }
}

// Your physics goes here: create a world in reset(), advance it in step(), draw its bodies in draw().
namespace sandbox {
    static Vec2 pos = {0, 0};
    static Vec2 vel = {0, 0};

    static void reset() {
        pos = {0, 8};
        vel = {0, 0};
    }
    static void step(float dt) {
        vel+={0,-9.81f*dt};
        pos+=vel*dt;
    }
    static void draw() {

        dd::circle(pos.x,pos.y,2);
        dd::hud("vel: %.2f", vel.y);
    }
}

const Scene kScenes[] = {
    {"Draw test", draw_test::reset, draw_test::step, draw_test::draw},
    {"Sandbox",   sandbox::reset,   sandbox::step,   sandbox::draw},
};
const int kSceneCount = sizeof(kScenes) / sizeof(kScenes[0]);
