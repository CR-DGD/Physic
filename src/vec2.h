//
// Created by iiya_yeeet on 10/18/2026.
//

#pragma once
#include <cmath>

//Vector 2, Meter units.
struct Vec2 {
    float x = 0;
    float y = 0;
};

//Inline operators
inline Vec2 operator+(Vec2 a, Vec2 b) { return {a.x + b.x, a.y + b.y}; }
inline Vec2 operator-(Vec2 a, Vec2 b) { return {a.x - b.x, a.y - b.y}; }
inline Vec2 operator*(Vec2 a, float b) { return {a.x * b, a.y * b}; }
inline Vec2 operator*(float b, Vec2 a) { return {a.x * b, a.y * b}; }


inline Vec2 &operator+=(Vec2 &a, Vec2 b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline Vec2 &operator-=(Vec2 &a, Vec2 b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

inline Vec2 &operator*=(Vec2 &a, float b) {
    a.x *= b;
    a.y *= b;
    return a;
}

//Unary operator
inline Vec2 operator-(Vec2 a) { return {-a.x, -a.y}; }

//Dot Product. Positive = Same dir, Negative = Opposite dir, 0 = Perpendicular. How aligned two vectors are.
inline float dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }

//Distance comparison, avoids expensive sqrting, compared against a squared value anyways. used for collison calcs and similar.
inline float lengthSq(Vec2 a) { return a.x * a.x + a.y * a.y; }

//True Length (Magnitude)
inline float length(Vec2 a) { return std::sqrt(lengthSq(a)); }

//Keeps direction, limits to 1. Epsilon in there to avoid division by zero or near zero, can get extreme values.
inline Vec2 normalize(Vec2 a) {
    float len = length(a);
    if (len < 1e-6f) return {0, 0};
    float inv = 1 / len;
    return a * inv;
}

//Cross Product, Positive = CCW, Negative = CW, 0 = Parallel. How much two vectors turn. Torque force.
inline float cross(Vec2 a, Vec2 b) { return a.x * b.y - a.y * b.x; }
