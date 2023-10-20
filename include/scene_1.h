#ifndef SCENE_1
#define SCENE_1

#include <vector>
#include <chrono>

#include "gl.h"
#include "glm/glm.hpp"

#include "camera.h"
#include "shader.h"

namespace scene_1 {
    
class Scene_1 {
public:
    Scene_1() = default;
    Scene_1(const Scene_1 &)=delete;
    Scene_1(Scene_1 &&)=delete;
    Scene_1& operator=(const Scene_1 &)=delete;
    Scene_1& operator=(Scene_1 &&)=delete;
    ~Scene_1();

    bool init(int32_t width, int32_t height);
    void set_window_size(int32_t width, int32_t height);

    void draw();
    void draw_cube();
    void draw_texture();
    void draw_gauss_filter();
private:
    int32_t m_window_width = -1;
    int32_t m_window_height = -1;

    camera::Camera m_camera;

    GLuint m_cube_vbo = 0u;
    GLuint m_cube_vao = 0u;

    ShaderProgram m_shader_program_texture;
    ShaderProgram m_shader_program_cube;
    ShaderProgram m_shader_gauss_3x3;

    GLfloat m_cube_current_algle = 0.0f;
    glm::vec3 m_cube_position = glm::vec3(0.0f);

    static constexpr GLsizei NUM_OF_FRAMES = 2u;
    GLuint m_frames_textures[NUM_OF_FRAMES] = {0u, 0u};
    GLuint m_frames_postorocess[NUM_OF_FRAMES] = {0u, 0u};
    GLuint m_draw_framebuffer;
    GLint m_tex_width, m_tex_height;

    uint32_t m_current_frame = 0u;

    constexpr static uint16_t m_num_of_timings = 16u;
    uint16_t m_timing_index = 0u;
    constexpr static uint16_t m_fps_print_num = 240u;
    uint16_t m_fps_print_count = 0u;
    std::vector<uint64_t> m_frame_timings{};
    std::chrono::time_point<std::chrono::steady_clock> m_last_time{};
    void check_FPS();
};

} // namespace scene_1

#endif // SCENE_1