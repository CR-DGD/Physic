#pragma once
// Debug drawing in world space. Physics code calls these and never touches raylib.
// World units are meters, y points up, and (0,0) sits at the bottom-centre of the window.

namespace dd {

using Rgba = unsigned int; // 0xRRGGBBAA
constexpr Rgba White  = 0xE8E8E8FF;
constexpr Rgba Gray   = 0x707070FF;
constexpr Rgba Red    = 0xE5534BFF;
constexpr Rgba Green  = 0x57AB5AFF;
constexpr Rgba Blue   = 0x539BF5FF;
constexpr Rgba Yellow = 0xDAAA3FFF;

// Shapes. Angles are radians, counter-clockwise.
void circle(float x, float y, float radius, float angle = 0.0f, Rgba color = White);
void box(float x, float y, float halfW, float halfH, float angle = 0.0f, Rgba color = White);
void polygon(const float* xy, int pointCount, Rgba color = White); // xy = {x0,y0, x1,y1, ...}
void line(float x1, float y1, float x2, float y2, Rgba color = White);
void arrow(float x, float y, float dx, float dy, Rgba color = Yellow); // e.g. velocity or contact normal
void point(float x, float y, Rgba color = Red);

// printf-style text line in the top-left HUD, under the built-in stats.
void hud(const char* fmt, ...);

// Mouse position in world space.
void mouseWorld(float& x, float& y);

// Used by main.cpp.
void beginFrame(int screenW, int screenH, float pixelsPerMeter);
void grid();

} // namespace dd
