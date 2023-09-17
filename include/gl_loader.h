#ifndef GL_LOADER_H
#define GL_LOADER_H

constexpr bool PRINT_LOADED_FUNCTIONS = false;

namespace gl_loader {

bool load_GL();
void print_GL_strings();

} // namespace gl_loader

#endif // GL_LOADER_H
