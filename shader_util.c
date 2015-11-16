#include "openGL_util.h"
#include "shader_util.h"
#include "log.h"

GLuint buildShaderProgram(const char* vertex_shader,const char* fragment_shader)
{
	GLuint vs, fs;
	GLuint returnProgram;

	// Compile vertex shader
	vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader (vs);

	//Cheach for errors from vertex shader compilation
	int params = -1;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
	if (params != GL_TRUE)
	{
		gl_log_err("ERROR: Vertex shader did not compile correct\n");
		print_shader_info_log(vs,vertex_shader);
		return -1;
	}

	//Compile fragmen shader
	fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);

	//Cheach for errors from fragment shader compilation
	params = -1;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
	if (params != GL_TRUE)
	{
		gl_log_err("ERROR: Vertex shader did not compile correct\n");
		print_shader_info_log(fs,fragment_shader);
		return -1;
	}

	// Create one big piple from the vertex and fragment shaders.
	returnProgram = glCreateProgram ();
	glAttachShader (returnProgram, fs);
	glAttachShader (returnProgram, vs);
	glLinkProgram (returnProgram);

	// check if the link process was succesfull
	params = -1;
	glGetProgramiv(returnProgram, GL_LINK_STATUS, &params);
	if (params != GL_TRUE)
	{
			gl_log_err("ERROR: Build shader program failed\n");
			print_programme_info_log(returnProgram);
			return -1;
	}

	return returnProgram;
}

void print_all (GLuint programme)
{
	gl_log("-------------------- shader programme %i info:\n", programme);
	int params = -1;
	glGetProgramiv (programme, GL_LINK_STATUS, &params);
	gl_log (" GL_LINK_STATUS = %i\n", params);

	glGetProgramiv (programme, GL_ATTACHED_SHADERS, &params);
	gl_log (" GL_ATTACHED_SHADERS = %i\n", params);
	glGetProgramiv (programme, GL_ACTIVE_ATTRIBUTES, &params);
	gl_log (" GL_ACTIVE_ATTRIBUTES = %i\n", params);
	for (GLuint i = 0; i < (GLuint) params; i++)
	{
		char name[ 64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib (programme, i, max_length, &actual_length, &size, &type, name);
		if (size > 1)
		{
			for (int j = 0; j < size; j++)
			{
				char long_name[ 64];
				gl_log (long_name, "% s[% i]", name, j);
				int location = glGetAttribLocation (programme, long_name);


				gl_log(" %i) type:% s name:% s location:% i\n", i, GL_type_to_string (type), long_name, location);
			}
		}
		else
		{
			int location = glGetAttribLocation (programme, name);
			gl_log (" %i) type:% s name:% s location:% i\n", i, GL_type_to_string (type), name, location);
		}
	}
	glGetProgramiv (programme, GL_ACTIVE_UNIFORMS, &params);
	gl_log (" GL_ACTIVE_UNIFORMS = %i\n", params);
	for (GLuint i = 0; i < (GLuint) params; i++)
	{
		char name[ 64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform (programme, i, max_length, &actual_length, &size, &type, name);
		if (size > 1)
		{
			for (int j = 0; j < size; j++)
			{
				char long_name[ 64];
				gl_log (long_name, "% s[% i]", name, j);
				int location = glGetUniformLocation (programme, long_name);
				gl_log (" %i) type:% s name:% s location:% i\n", i, GL_type_to_string (type), long_name, location);
			}
		}
		else
		{
			int location = glGetUniformLocation (programme, name);
			gl_log (" %i) type:% s name:% s location:% i\n", i, GL_type_to_string (type), name, location);
		}
	}
	print_programme_info_log (programme);
}

void print_shader_info_log(GLuint shader_index, const char* shader)
{
	int max_length =2048;
	int act_length = 0;
	char log[max_length];
	glGetShaderInfoLog(shader_index, max_length, &act_length, log);
	gl_log(shader);
	gl_log("\n");
	gl_log(log);
	gl_log("\n");
}

void print_programme_info_log(GLuint programme)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[ 2048];
	glGetProgramInfoLog (programme, max_length, &actual_length, log);
	gl_log(log);
}
