#include "gl_loader.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.h"

#include <iostream>

#define GLLOAD(proc, name) \
    proc name = nullptr;
#include "gl_function.in"
#undef GLLOAD

namespace gl_loader {

bool load_GL() {
    bool res = true;

    #define GLLOAD(proc, name) \
        name = (proc)glfwGetProcAddress(#name);                                   \
        if(!name) {                                                               \
            res = false;                                                          \
            std::cout << "function name not load" << std::endl;                   \
        } else {                                                                  \
            if (PRINT_LOADED_FUNCTIONS) {                                         \
                std::cout << #name << " " << (void*)name << " load" << std::endl; \
            }                                                                     \
        }
    #include "gl_function.in"

    #undef GLLOAD

    return res;
}

void print_GL_strings() {
    std::cout << std::endl;
    std::cout << "GL_VENDOR - " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_RENDERER - " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GL_VERSION - " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL_SHADING_LANGUAGE_VERSION - " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

} // namespace gl_loader
