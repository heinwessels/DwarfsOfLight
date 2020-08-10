#pragma once

class Timing{
    double m_update_time = 0;
    double m_update_time_min = 0;
    double m_update_time_max = 0;
public:
    void update_timing(double time){
        m_update_time = time;
        if (m_update_time_min == 0 || m_update_time_min > time){
            m_update_time_min = time;
        }
        if (m_update_time_max == 0 || m_update_time_max < time){
            m_update_time_max = time;
        }
    }

    double get_update_time() { return m_update_time; }
    double get_update_time_min() { return m_update_time_min; }
    double get_update_time_max() { return m_update_time_max; }
};