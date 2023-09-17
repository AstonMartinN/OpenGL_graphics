#ifndef GL_H
#define GL_H

#include "GL/glcorearb.h"

extern "C" {

#define GLLOAD(proc, name) extern proc name;

#include "gl_function.in"

#undef GLLOAD

}

#endif // GL_H
