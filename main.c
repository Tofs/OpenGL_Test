/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| Extended Initialisation. Some extra detail.                                  |
\******************************************************************************/
#include <stdio.h>
#include "OpenGLObjects.h"
#include "openGLRenderer.h"
#include "openGL_util.h"
#include "log.h"
#include <assert.h>
#include <iostream>

#include <string>
#include <fstream>
#include <streambuf>



std::string loadFileToString(const char* filePath)
{
	std::ifstream t(filePath);
	std::string str((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	return str;
}

void mainLoop(Rendebal_Object ro, GLFWwindow* window)
{
	while (!glfwWindowShouldClose (window)) {
		_update_fps_counter (window);
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);

		glUseProgram (ro.shader_programme);
		glBindVertexArray (ro.vertex_array_object);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays (GL_TRIANGLES, 0, ro.vertex_count / 3);
		// update other events like input handling
		glfwPollEvents ();
		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (window, 1);
		}
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (window);
	}
}


int main () {
	assert (restart_gl_log ());

	Rendebal_Object ro;
	GLuint shader_programme;

	GLfloat points[] = {
		0.0f,	0.5f,	0.0f,
		0.5f, -0.5f,	0.0f,
		-0.5f, -0.5f,	0.0f
	};

	GLfloat colours[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	std::string vs = loadFileToString("Resources/basic.vert");
	std::string fs = loadFileToString("Resources/basic.frag");
	const char* vertex_shader = vs.c_str();
	const char* fragment_shader = fs.c_str();

	struct render_object object;
	object.points = points;
	object.colours = colours;
	object.pointsSize = 9;

	GLFWwindow* window;
	window = CreateGLFWWindow(false);

	shader_programme = buildShaderProgram(vertex_shader, fragment_shader);

	ro.vertex_array_object = loadVertexToGPU(&object);
	ro.shader_programme = shader_programme;
	mainLoop(ro, window);
	// close GL context and any other GLFW resources
	glfwTerminate();

	return 0;
}
