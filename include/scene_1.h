#ifndef SCENE_1
#define SCENE_1

#include "scene_base.h"

#include <vector>
#include <chrono>

#include "gl.h"
#include "glm/glm.hpp"

#include "camera.h"
#include "shader.h"

namespace scene_1 {
    
class Scene_1 : public scene_base::Scene_base {
public:
    Scene_1() = default;
    Scene_1(const Scene_1 &)=delete;
    Scene_1(Scene_1 &&)=delete;
    Scene_1& operator=(const Scene_1 &)=delete;
    Scene_1& operator=(Scene_1 &&)=delete;
    ~Scene_1();

    bool init(int32_t width, int32_t height);

    void draw();

    void draw_cube();
    void draw_texture();
    void draw_gauss_filter();
private:
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
};

} // namespace scene_1

#endif // SCENE_1