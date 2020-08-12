#pragma once

#include "Vec2.hpp"

class Camera{

    // These two "boresight" variables are in game distance units,
    // NOT pixels!
    Vec2 *m_target;
    Vec2 m_position;   // If no target, then follow posision

    double m_zoom;
    Vec2 m_screen_size;

public:
    Camera(Vec2 *target, Vec2 posision, double zoom, Vec2 screen_size)
        :   m_target(target), m_position(posision),
        m_zoom(zoom), m_screen_size(screen_size) { }
    Camera(Vec2 *target, double zoom, Vec2 screen_size)
        : Camera(target, Vec2(0.0), zoom, screen_size) { }
    Camera(Vec2 posision, double zoom, Vec2 screen_size)
        : Camera(nullptr, posision, zoom, screen_size) { }

    Vec2 get_position_on_screen(Vec2 position){
        // Origin is at (0,0) which is at the top left of the screen
        Vec2 boresight = m_target ? *m_target : m_position;   // Choose boresight based on if there is a target
        return (position- boresight)*m_zoom  + m_screen_size / 2.0;
    }

    void set_zoom(double zoom){ m_zoom = zoom; }
    double get_zoom(){ return m_zoom; }

    void set_target(Vec2 *target) { m_target = target; /* Can be nullptr*/ }
    void set_position(Vec2 posision) { m_position = posision; m_target = nullptr; /* Cancels target */ }
    Vec2 get_position(){ return m_position; }
};