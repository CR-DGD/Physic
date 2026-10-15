#include "debug_draw.h"

#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <raylib.h>

namespace dd {

static int   sW = 0, sH = 0;
static float sPpm = 50.0f;
static int   sHudY = 0;
constexpr float kOriginFromBottom = 60.0f; // pixels, so the y=0 floor line is visible

static Vector2 toScreen(float x, float y) {
    return {sW * 0.5f + x * sPpm, sH - kOriginFromBottom - y * sPpm};
}

void beginFrame(int screenW, int screenH, float pixelsPerMeter) {
    sW = screenW;
    sH = screenH;
    sPpm = pixelsPerMeter;
    sHudY = 10 + 3 * 22; // below main.cpp's three stat lines
}

void grid() {
    const Color faint = {255, 255, 255, 14};
    float halfMetersX = sW * 0.5f / sPpm, metersY = sH / sPpm;
    for (int i = (int)-halfMetersX - 1; i <= (int)halfMetersX + 1; ++i)
        DrawLineV(toScreen((float)i, -2), toScreen((float)i, metersY), faint);
    for (int j = -2; j <= (int)metersY + 1; ++j)
        DrawLineV(toScreen(-halfMetersX - 1, (float)j), toScreen(halfMetersX + 1, (float)j), faint);
    DrawLineV(toScreen(-halfMetersX - 1, 0), toScreen(halfMetersX + 1, 0), Fade(GetColor(Gray), 0.6f));
}

void circle(float x, float y, float radius, float angle, Rgba color) {
    Vector2 c = toScreen(x, y);
    DrawCircleLinesV(c, radius * sPpm, GetColor(color));
    // Radius line so rotation is visible.
    line(x, y, x + std::cos(angle) * radius, y + std::sin(angle) * radius, color);
}

void box(float x, float y, float halfW, float halfH, float angle, Rgba color) {
    float c = std::cos(angle), s = std::sin(angle);
    const float local[4][2] = {{-halfW, -halfH}, {halfW, -halfH}, {halfW, halfH}, {-halfW, halfH}};
    float xy[8];
    for (int i = 0; i < 4; ++i) {
        xy[i * 2]     = x + local[i][0] * c - local[i][1] * s;
        xy[i * 2 + 1] = y + local[i][0] * s + local[i][1] * c;
    }
    polygon(xy, 4, color);
}

void polygon(const float* xy, int pointCount, Rgba color) {
    for (int i = 0; i < pointCount; ++i) {
        int j = (i + 1) % pointCount;
        line(xy[i * 2], xy[i * 2 + 1], xy[j * 2], xy[j * 2 + 1], color);
    }
}

void line(float x1, float y1, float x2, float y2, Rgba color) {
    DrawLineEx(toScreen(x1, y1), toScreen(x2, y2), 1.5f, GetColor(color));
}

void arrow(float x, float y, float dx, float dy, Rgba color) {
    float len = std::sqrt(dx * dx + dy * dy);
    line(x, y, x + dx, y + dy, color);
    if (len < 1e-6f) return;
    float head = std::fmin(0.25f, len * 0.4f), ux = dx / len, uy = dy / len;
    float tx = x + dx, ty = y + dy;
    line(tx, ty, tx - head * (ux - uy * 0.5f), ty - head * (uy + ux * 0.5f), color);
    line(tx, ty, tx - head * (ux + uy * 0.5f), ty - head * (uy - ux * 0.5f), color);
}

void point(float x, float y, Rgba color) {
    DrawCircleV(toScreen(x, y), 3.0f, GetColor(color));
}

void hud(const char* fmt, ...) {
    char buf[256];
    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buf, sizeof buf, fmt, args);
    va_end(args);
    DrawText(buf, 10, sHudY, 20, GetColor(White));
    sHudY += 22;
}

void mouseWorld(float& x, float& y) {
    Vector2 m = GetMousePosition();
    x = (m.x - sW * 0.5f) / sPpm;
    y = (sH - kOriginFromBottom - m.y) / sPpm;
}

} // namespace dd
