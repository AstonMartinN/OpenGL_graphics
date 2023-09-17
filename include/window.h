#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace window_glfw {

struct WindowCreateInfo {
    int32_t m_width;
    int32_t m_height;
    int32_t m_major_GL_version;
    int32_t m_minor_GL_version;
};

class WindowManagerGLFW final {
public:
    WindowManagerGLFW(const WindowManagerGLFW &)=delete;
    WindowManagerGLFW(WindowManagerGLFW &&)=delete;
    WindowManagerGLFW& operator=(const WindowManagerGLFW &)=delete;
    WindowManagerGLFW& operator=(WindowManagerGLFW &&)=delete;
    ~WindowManagerGLFW() = default;

    static WindowManagerGLFW* get_window_manager_GLFW();
    void GLFW_init_window(struct WindowCreateInfo window_create_info);
    void GLFW_destroy_window();
    GLFWwindow * get_window() { return m_window; }

    const int32_t &get_window_width() { return m_window_create_info.m_width; }
    const int32_t &get_window_height() { return m_window_create_info.m_height; }

private:
    bool m_GLFW_init_success = false;
    WindowCreateInfo m_window_create_info;
    GLFWwindow *m_window = nullptr;

    static WindowManagerGLFW *m_window_manager_GLFW;
    WindowManagerGLFW();

    static void error_callback(int error, const char* description);
    [[maybe_unused]] static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} // namespace window_glfw



#endif // WINDOW_H
