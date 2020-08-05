#include <bits/stdc++.h>

class MColour{
public:
    int r = 0, g = 0, b = 0, a = 0;
    MColour() { }
    MColour(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) { }

    MColour& operator += (const MColour & v){
        r += v.r; g += v.g; b += v.b; a += v.a;
        return *this;
    }
    MColour operator + (const MColour &v) const{
        MColour t (*this); t += v; return t;
    }

    MColour& operator -= (const MColour & v){
        r -= v.r; g -= v.g; b -= v.b; a -= v.a;
        return *this;
    }
    MColour operator - (const MColour &v) const{
        MColour t (*this); t -= v; return t;
    }

    MColour& operator *= (const MColour & v){
        r *= v.r; g *= v.g; b *= v.b; a *= v.a;
        return *this;
    }
    MColour operator * (const MColour &v) const{
        MColour t (*this); t *= v; return t;
    }

    MColour& operator /= (const MColour & v){
        r /= v.r; g /= v.g; b /= v.b; a /= v.a;
        return *this;
    }
    MColour operator / (const MColour &v) const{
        MColour t (*this); t /= v; return t;
    }

    MColour clamp (MColour &colour){
        MColour &c (*this);
        c.r = std::min(0, std::max(c.r, 255));
        c.g = std::min(0, std::max(c.g, 255));
        c.b = std::min(0, std::max(c.b, 255));
        c.a = std::min(0, std::max(c.a, 255));
        return c;
    }
};