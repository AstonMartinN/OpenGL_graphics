#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "gl.h"

#include "gl_loader.h"
#include "window.h"

#include "scene_1.h"

void DrawScene(window_glfw::WindowManagerGLFW* window_manager_GLFW) {
    scene_1::Scene_1 scene_1;
    scene_1.init(window_manager_GLFW->get_window_width(), window_manager_GLFW->get_window_height());

    while (true) {
        glfwPollEvents();
        if(glfwWindowShouldClose(window_manager_GLFW->get_window())) {
            break;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0u);
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        scene_1.draw();

        glfwSwapBuffers(window_manager_GLFW->get_window());
    }
}

int main(){

    window_glfw::WindowManagerGLFW* window_manager_GLFW = window_glfw::WindowManagerGLFW::get_window_manager_GLFW();

    struct window_glfw::WindowCreateInfo window_create_info;
    window_create_info.m_width = 1920;
    window_create_info.m_height = 1080;
    window_create_info.m_major_GL_version = 4;
    window_create_info.m_minor_GL_version = 6;
    window_manager_GLFW->GLFW_init_window(window_create_info);

    gl_loader::load_GL();
    gl_loader::print_GL_strings();

    DrawScene(window_manager_GLFW);

    window_manager_GLFW->GLFW_destroy_window();

    return 0;
}
