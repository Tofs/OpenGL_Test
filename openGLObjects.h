#ifndef OpenGLObject_h
#define OpenGLObject_h


#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

struct render_object
{
	GLfloat* points;
	GLfloat* colours;
	int pointsSize;
	char* fragment_shader;
	char* vertex_shader;
};

struct Rendebal_Object
{
	GLuint shader_programme;
	GLuint vertex_buffer_object_points;
	GLuint vertex_buffer_object_colours;
	GLuint vertex_array_object;
	int vertex_count;
};

#endif
