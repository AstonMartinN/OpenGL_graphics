#include "scene_1.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <cmath>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "gl.h"


namespace scene_1 {

constexpr static float cube_vertices[] = {
    #include "cube_position_normal_coords.in"
};

bool Scene_1::init(int32_t width, int32_t height) {

    set_window_size(width, height);

    glGenVertexArrays(1, &m_cube_vao);
    glGenBuffers(1, &m_cube_vbo);
    glBindVertexArray(m_cube_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_cube_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    m_shader_program_texture.set_paths("../shaders/out_texture.vs", "../shaders/out_texture.fs");
    m_shader_program_texture.compile_program();

    m_shader_program_cube.set_paths("../shaders/cube.vs", "../shaders/cube.fs");
    m_shader_program_cube.compile_program();

    m_shader_gauss_3x3.set_paths("../shaders/gaussian_filter_3x3_9sample.vs", "../shaders/gaussian_filter_3x3_9sample.fs");
    m_shader_gauss_3x3.compile_program();

    std::string textures_paths[NUM_OF_FRAMES] = {
        std::string("../images/genshin_impact_frame_1.png"),
        std::string("../images/genshin_impact_frame_2.png")
    };

    stbi_set_flip_vertically_on_load(true);
    glCreateTextures(GL_TEXTURE_2D, NUM_OF_FRAMES, m_frames_textures);
    glCreateTextures(GL_TEXTURE_2D, NUM_OF_FRAMES, m_frames_postorocess);
    for(uint32_t i = 0; i < NUM_OF_FRAMES; i++) {
        glTextureParameteri(m_frames_textures[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_frames_textures[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_frames_textures[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_frames_textures[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_frames_postorocess[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_frames_postorocess[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_frames_postorocess[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_frames_postorocess[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int texWidth, texHeight, texChannels;
        stbi_uc* pixels = stbi_load(textures_paths[i].c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        if (pixels == nullptr) {
            std::cout << "Scene_1::Init - failed to load " << textures_paths[i] << std::endl;
        }
        glTextureStorage2D(m_frames_textures[i], 1, GL_RGBA8, texWidth, texHeight);
        glTextureSubImage2D(m_frames_textures[i], 0, 0, 0, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        stbi_image_free(pixels);

        glTextureStorage2D(m_frames_postorocess[i], 1, GL_RGBA8, texWidth, texHeight);

        m_tex_width = texWidth;
        m_tex_height = texHeight;
    }

    m_frame_timings.resize(m_num_of_timings);
    m_last_time = std::chrono::steady_clock::now();

    m_camera.set_project_matrix(width, height);

    glGenFramebuffers(1, &m_draw_framebuffer);
    glBindBuffer(GL_FRAMEBUFFER, m_draw_framebuffer);

    return true;
}

Scene_1::~Scene_1() {
    glDeleteTextures(NUM_OF_FRAMES, m_frames_textures);
    glDeleteTextures(NUM_OF_FRAMES, m_frames_postorocess);
    glDeleteFramebuffers(1, &m_draw_framebuffer);
}

void Scene_1::set_window_size(int32_t width, int32_t height) {
    m_window_width = width;
    m_window_height = height;
}

void Scene_1::draw() {
    draw_gauss_filter();
    draw_texture();
    draw_cube();

    check_FPS();
}

void Scene_1::draw_cube() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_SCISSOR_TEST);

    glUseProgram(m_shader_program_cube.get_program());

    GLfloat speed = 0.000005f;
    glm::mat4 model = glm::mat4(1.0f);
    //std::cout << _frame_timings[_timing_index] << std::endl;
    m_cube_current_algle = std::fmod(m_cube_current_algle + speed * static_cast<GLfloat>(m_frame_timings[m_timing_index]), 360.0f);

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
    model = glm::rotate(model, m_cube_current_algle, glm::vec3(1.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));

    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(m_camera.get_project_matrix()));

    glViewport(0, 0, m_window_width, m_window_height);
    glBindVertexArray(m_cube_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Scene_1::draw_texture() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(m_shader_program_texture.get_program());

    if (false) {
        glBindTextureUnit(0, m_frames_textures[m_current_frame]);
    } else {
        glBindTextureUnit(0, m_frames_postorocess[m_current_frame]);
    }

    glViewport(0, 0, m_window_width, m_window_height);
    glBindVertexArray(m_cube_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_current_frame = (m_current_frame + 1u) % NUM_OF_FRAMES;
}

void Scene_1::draw_gauss_filter() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_BLEND);

    glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);

    glUseProgram(m_shader_gauss_3x3.get_program());
    glBindTextureUnit(0, m_frames_textures[m_current_frame]);

    glBindFramebuffer(GL_FRAMEBUFFER, m_draw_framebuffer);
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_frames_postorocess[m_current_frame], 0);
    GLenum draw_buffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, draw_buffers);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE" << std::endl;
    }

    if (false) {
        GLuint clear_color[4] = {0, 0, 0, 0};
        glClearBufferuiv(GL_COLOR, 0, clear_color);
    } else {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glScissor(0, 0, m_tex_width, m_tex_height);
    glViewport(0, 0, m_tex_width, m_tex_height);
    glBindVertexArray(m_cube_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Scene_1::check_FPS() {
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

} // namespace scene_1