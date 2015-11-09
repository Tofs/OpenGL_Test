#ifndef shader_util_h
#define shader_util_h

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

void print_shader_info_log(GLuint shader_index, const char* shader);

void print_programme_info_log(GLuint programme);

GLuint buildShaderProgram(const char* vertex_shader,const char* fragment_shader);

void print_all (GLuint programme);

#endif
