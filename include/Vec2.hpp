#pragma once

class Vec2 {

    typedef float T;

    public:
    T x, y;

    Vec2() : x(0), y(0) {};
    Vec2(T i) : x(i), y(i) {}
    Vec2(T i, T j) : x(i), y(j) {}

    Vec2& operator += (const Vec2 & v){
        x += v.x;
        y += v.y;
        return *this;
    }
    Vec2 operator + (const Vec2 &v){
        Vec2 t (*this);
        t += v;
        return t;
    }
    Vec2& operator += (const T &c){
        x += c;
        y += c;
        return *this;
    }
    Vec2 operator + (const T &c){
        Vec2 t (*this);
        t += c;
        return t;
    }

    Vec2& operator -= (const Vec2 & v){
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vec2 operator - (const Vec2 &v){
        Vec2 t (*this);
        t -= v;
        return t;
    }
    Vec2& operator -= (const T &c){
        x -= c;
        y -= c;
        return *this;
    }
    Vec2 operator - (const T &c){
        Vec2 t (*this);
        t -= c;
        return t;
    }

    Vec2& operator *= (const Vec2 & v){
        x *= v.x;
        y *= v.y;
        return *this;
    }
    Vec2 operator * (const Vec2 &v){
        Vec2 t (*this);
        t *= v;
        return t;
    }
    Vec2& operator *= (const T &c){
        x *= c;
        y *= c;
        return *this;
    }
    Vec2 operator * (const T &c){
        Vec2 t (*this);
        t *= c;
        return t;
    }

    Vec2& operator /= (const Vec2 & v){
        x /= v.x;
        y /= v.y;
        return *this;
    }
    Vec2 operator / (const Vec2 &v){
        Vec2 t (*this);
        t /= v;
        return t;
    }
    Vec2& operator /= (const T &c){
        x /= c;
        y /= c;
        return *this;
    }
    Vec2 operator / (const T &c){
        Vec2 t (*this);
        t /= c;
        return t;
    }
};
