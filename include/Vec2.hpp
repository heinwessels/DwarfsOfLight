#pragma once

#include <cmath>

class Vec2 {

    public:
    double x, y;

    Vec2() : x(0), y(0) {};
    Vec2(double i) : x(i), y(i) {}
    Vec2(double i, double j) : x(i), y(j) {}

    double sum (){ return x + y; }
    double norm (){ return sqrt(dot(*this, *this)); }

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

    static double dist_sq(const Vec2 &a, const Vec2 &b){
        return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
    }

    static Vec2 floor(const Vec2 &a){
        return Vec2(std::floor(a.x), std::floor(a.y));
    }

    static Vec2 transpose(const Vec2 &a){
        return Vec2(a.y, a.x);
    }

    static double dot(const Vec2 &a, const Vec2 &b){
        return a.x*b.x + a.y*b.y;
    }

    static double cross(const Vec2 &a, const Vec2 &b){
        return a.x*b.y - a.y*b.x;
    }


};
