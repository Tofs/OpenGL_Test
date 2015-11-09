#include "openGL_util.h"
#include "log.h"



const char* GL_type_to_string(GLenum type)
{
	switch (type) {
		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "sampler2D";
		case GL_SAMPLER_3D: return "sampler3D";
		case GL_SAMPLER_CUBE: return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
		default: break;
	}
	return "other";
}

void loadVertexToGPU(render_object *ro1, Rendebal_Object *ro2)
{
	GLuint vao;
	GLuint vbo;

	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, ro1->pointsSize * sizeof (GLfloat), ro1->points, GL_STATIC_DRAW);

	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	ro2->vertex_array_object = vao;
	ro2->vertex_buffer_object = vbo;
	ro2->vertex_count = ro1->pointsSize;
}
