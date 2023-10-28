#include "scene_base.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>

namespace scene_base {

void Scene_base::check_fps() {
    auto new_time = std::chrono::steady_clock::now();
    m_frame_timings[m_timing_index] = std::chrono::duration_cast<std::chrono::microseconds>(new_time - m_last_time).count();
    m_timing_index = (m_timing_index + 1u) % m_num_of_timings;
    m_last_time = std::move(new_time);
    
    m_fps_print_count = (m_fps_print_count + 1u) % m_fps_print_num;
    if(m_fps_print_count == 0u) {
        uint32_t sum = std::accumulate(m_frame_timings.begin(), m_frame_timings.end(), 0u);
        std::cout << "FPS = " << 1e6 / (static_cast<float>(sum) / static_cast<float>(m_num_of_timings)) << std::endl;
    }
}

} // namespace scene_base