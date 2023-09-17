#include <iostream>

#include "window.h"

namespace window_glfw {

WindowManagerGLFW *WindowManagerGLFW::m_window_manager_GLFW = nullptr;

WindowManagerGLFW::WindowManagerGLFW() {
    if (!glfwInit()) {
        std::cout << "WindowManagerGLFW::WindowManagerGLFW - glfw init failed" << std::endl;
    } else {
        m_GLFW_init_success = true;
    }
}

void WindowManagerGLFW::GLFW_destroy_window() {
    // std::cout << "WindowManagerGLFW::GLFWDestroyWindow()" << std::endl;
    glfwDestroyWindow(m_window);
    glfwTerminate();
    delete m_window_manager_GLFW;
}

WindowManagerGLFW* WindowManagerGLFW::get_window_manager_GLFW() {
    if(!m_window_manager_GLFW) {
        m_window_manager_GLFW = new WindowManagerGLFW;
    }
    return m_window_manager_GLFW;
}

void WindowManagerGLFW::GLFW_init_window(struct WindowCreateInfo window_create_info) {
    if (!m_GLFW_init_success) {
        std::cout << "WindowManagerGLFW::GLFWInitWindow - glfw init not success" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, window_create_info.m_major_GL_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, window_create_info.m_minor_GL_version);
    // glfwGetPrimaryMonitor()
    m_window = glfwCreateWindow(window_create_info.m_width, window_create_info.m_height, "Window", glfwGetPrimaryMonitor(), NULL);
    if (!m_window) {
        std::cout << "main::glfwCreateWindow failed" << std::endl;
        glfwTerminate();
    }

    m_window_create_info = window_create_info;

    glfwSetKeyCallback(m_window, WindowManagerGLFW::key_callback);
    glfwSetErrorCallback(WindowManagerGLFW::error_callback);
    glfwMakeContextCurrent(m_window);
}

void WindowManagerGLFW::error_callback(int error, const char* description){
    std::cout << "GLFW Error: " <<  description << std::endl << ", error = " << error;
}

[[maybe_unused]] void WindowManagerGLFW::key_callback(GLFWwindow* window, int key,
    [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

} // namespace window_glfw
