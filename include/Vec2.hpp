#pragma once

class Vec2 {

    public:
    float x, y;

    Vec2() : x(0), y(0) {};
    Vec2(float i) : x(i), y(i) {}
    Vec2(float i, float j) : x(i), y(j) {}

    Vec2& operator += (const Vec2 & v){
        x += v.x;
        y += v.y;
        return *this;
    }
    Vec2 operator + (const Vec2 &v) const{
        Vec2 t (*this);
        t += v;
        return t;
    }

    Vec2& operator -= (const Vec2 & v){
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vec2 operator - (const Vec2 &v) const{
        Vec2 t (*this);
        t -= v;
        return t;
    }

    Vec2& operator *= (const Vec2 & v){
        x *= v.x;
        y *= v.y;
        return *this;
    }
    Vec2 operator * (const Vec2 &v) const{
        Vec2 t (*this);
        t *= v;
        return t;
    }

    Vec2& operator /= (const Vec2 & v){
        x /= v.x;
        y /= v.y;
        return *this;
    }
    Vec2 operator / (const Vec2 &v) const{
        Vec2 t (*this);
        t /= v;
        return t;
    }

    static float dist_sq(const Vec2 &a, const Vec2 &b){
        return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
    }
};
