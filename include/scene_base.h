#ifndef SCENE_BASE
#define SCENE_BASE

#include <vector>
#include <chrono>

namespace scene_base {
    
class Scene_base {
public:
    Scene_base() = default;
    Scene_base(const Scene_base &)=delete;
    Scene_base(Scene_base &&)=delete;
    Scene_base& operator=(const Scene_base &)=delete;
    Scene_base& operator=(Scene_base &&)=delete;
    ~Scene_base() = default;

    virtual bool init(int32_t width, int32_t height) = 0;
    virtual void draw() = 0;

protected:
    int32_t m_window_width = -1;
    int32_t m_window_height = -1;

    constexpr static uint16_t m_num_of_timings = 16u;
    uint16_t m_timing_index = 0u;
    constexpr static uint16_t m_fps_print_num = 240u;
    uint16_t m_fps_print_count = 0u;
    std::vector<uint64_t> m_frame_timings{};
    std::chrono::time_point<std::chrono::steady_clock> m_last_time{};
    void check_fps();
};

} // namespace scene_base

#endif // SCENE_BASE