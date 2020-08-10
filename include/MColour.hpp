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
    void scale_to_max_channel(){
        // Scale the colour to the maximum r,g,b channel
        // But only if any channel is above 255
        int max = std::max(r, std::max(g, b));
        if (max > 255){
            r = (r * 255) / max;
            g = (g * 255) / max;
            b = (b * 255) / max;
        }
        else{
            clamp();
        }
    }

    MColour& operator += (const MColour & v){
        r += v.r; g += v.g; b += v.b; a += v.a;
        return *this;
    }
    MColour operator + (const MColour &v) const{
        MColour t (*this); t += v; return t;
    }
    MColour& operator += (const float & f){
        r += f; g += f; b += f; a += f;
        return *this;
    }
    MColour operator + (const float &f) const{
        MColour t (*this); t += f; return t;
    }

    MColour& operator -= (const MColour & v){
        r -= v.r; g -= v.g; b -= v.b; a -= v.a;
        return *this;
    }
    MColour operator - (const MColour &v) const{
        MColour t (*this); t -= v; return t;
    }
    MColour& operator -= (const float & f){
        r -= f; g -= f; b -= f; a -= f;
        return *this;
    }
    MColour operator - (const float &f) const{
        MColour t (*this); t -= f; return t;
    }

    MColour& operator *= (const MColour & v){
        r *= v.r; g *= v.g; b *= v.b; a *= v.a;
        return *this;
    }
    MColour operator * (const MColour &v) const{
        MColour t (*this); t *= v; return t;
    }
    MColour& operator *= (const float & f){
        r *= f; g *= f; b *= f; a *= f;
        return *this;
    }
    MColour operator * (const float &f) const{
        MColour t (*this); t *= f; return t;
    }

    MColour& operator /= (const MColour & v){
        r /= v.r; g /= v.g; b /= v.b; a /= v.a;
        return *this;
    }
    MColour operator / (const MColour &v) const{
        MColour t (*this); t /= v; return t;
    }
    MColour& operator /= (const float & f){
        r /= f; g /= f; b /= f; a /= f;
        return *this;
    }
    MColour operator / (const float &f) const{
        MColour t (*this); t /= f; return t;
    }
};