#ifndef openGL_util_h
#define openGL_util_h

#include "OpenGLObjects.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

GLuint buildShaderProgram(const char* vertex_shader,const char* fragment_shader);

void print_all (GLuint programme);

void loadVertexToGPU(render_object *ro1, Rendebal_Object *ro2);

#endif
