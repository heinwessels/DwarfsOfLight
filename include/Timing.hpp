#pragma once

class Timing{
    float m_update_time = 0;
    float m_update_time_min = 0;
    float m_update_time_max = 0;
public:
    void update_timing(float time){
        m_update_time = time;
        if (m_update_time_min == 0 || m_update_time_min > time){
            m_update_time_min = time;
        }
        if (m_update_time_max == 0 || m_update_time_max < time){
            m_update_time_max = time;
        }
    }

    float get_update_time() { return m_update_time; }
    float get_update_time_min() { return m_update_time_min; }
    float get_update_time_max() { return m_update_time_max; }
};