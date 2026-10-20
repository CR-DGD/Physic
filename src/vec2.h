//
// Created by iiya_yeeet on 10/18/2026.
//

#pragma once
#include <cmath>


struct  Vec2
{
    float x = 0;
    float y = 0;
};

inline Vec2 operator+(Vec2 a,Vec2 b){ return {a.x+b.x,a.y+b.y}; }

inline Vec2 operator-(Vec2 a,Vec2 b){ return {a.x-b.x,a.y-b.y}; }

inline Vec2 operator*(Vec2 a,float b){ return {a.x*b,a.y*b}; }
inline Vec2 operator*(float b,Vec2 a){ return {a.x*b,a.y*b}; }

inline Vec2& operator+=(Vec2& a,Vec2 b){ a.x+=b.x; a.y+=b.y; return a; }

inline Vec2& operator-=(Vec2& a,Vec2 b){ a.x-=b.x; a.y-=b.y; return a; }

inline Vec2& operator*=(Vec2& a,float b){ a.x*=b; a.y*=b; return a; }

inline Vec2 operator-(Vec2 a){ return {-a.x,-a.y}; }

inline float dot(Vec2 a,Vec2 b){return a.x*b.x + a.y*b.y;}
//9
inline float lengthSq(Vec2 a){return a.x*a.x+a.y*a.y;}

inline float length(Vec2 a){return std::sqrt(lengthSq(a));}

inline Vec2 normalize(Vec2 a) {
    float len = length(a);
    if (len < 1e-6f) return {0,0};
    float inv = 1/len;
    return a*inv;
}

inline float cross(Vec2 a,Vec2 b){return a.x*b.y - a.y*b.x;}

