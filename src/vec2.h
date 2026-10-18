//
// Created by iiya_yeeet on 10/18/2026.
//

#pragma once


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

