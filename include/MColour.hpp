#pragma once

#include <bits/stdc++.h>

class MColour{
public:
    int r = 0, g = 0, b = 0, a = 0;
    MColour() { }
    MColour(int c) : r(c), g(c), b(c), a(255) { }
    MColour(int r, int g, int b) : r(r), g(g), b(b), a(255) { }
    MColour(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) { }

    void clamp (){
        r = std::max(0, std::min(r, 255));
        g = std::max(0, std::min(g, 255));
        b = std::max(0, std::min(b, 255));
        a = std::max(0, std::min(a, 255));
    }

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

};