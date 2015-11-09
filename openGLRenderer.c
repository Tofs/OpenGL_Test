#include "openGLRenderer.h"
#include "OpenGLObjects.h"
#include "log.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h> // for doing gl_log() functions that work like printf()
//#include <stdbool.h> /* for visual studio i had to comment this out and define pure-C bool :( */
// keep track of window size for things like the viewport and the mouse cursor

/* we will tell GLFW to run this function whenever the window is resized */
void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
//	g_gl_width = width;
//	g_gl_height = height;
	printf ("width %i height %i\n", width, height);
	/* update any perspective matrices used here */
}

/* start a new log file. put the time and date at the top */
/* we will tell GLFW to run this function whenever it finds an error */
void glfw_error_callback (int error, const char* description) {
	gl_log_err ("GLFW ERROR: code %i msg: %s\n", error, description);
}
/* we can use a function like this to print some GL capabilities of our adapter
to the log file. handy if we want to debug problems on other people's computers
*/
void log_gl_params () {
	int i;
	int v[2];
	unsigned char s = 0;
	GLenum params[] = {
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS,
		GL_STEREO,
	};
	const char* names[] = {
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO",
	};
	gl_log ("GL Context Params:\n");
	// integers - only works if the order is 0-10 integer return types
	for (i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv (params[i], &v);
		gl_log ("%s %i\n", names[i], v);
	}
	// others
	v[0] = v[1] = 0;
	glGetIntegerv (params[10], v);
	gl_log ("%s %i %i\n", names[10], v[0], v[1]);
	glGetBooleanv (params[11], &s);
	gl_log ("%s %i\n", names[11], (unsigned int)s);
	gl_log ("-----------------------------\n");
}

double previous_seconds;
int frame_count;

/* we will use this function to update the window title with a frame rate */
void _update_fps_counter (GLFWwindow* window) {
	double current_seconds;
	double elapsed_seconds;
	char tmp[128];

	current_seconds = glfwGetTime ();
	elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;

		double fps = (double)frame_count / elapsed_seconds;
		sprintf (tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle (window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

GLFWwindow*  CreateGLFWWindow(bool full_screen)
{
	GLFWwindow* window;


	// start GL context and O/S window using the GLFW helper library
	gl_log ("starting GLFW\n%s\n", glfwGetVersionString ());
	// register the error call-back function that we wrote, above
	glfwSetErrorCallback (glfw_error_callback);
	if (!glfwInit ()) {
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return NULL;
	}

	if (full_screen)
	{

		GLFWmonitor* mon = glfwGetPrimaryMonitor ();
		const GLFWvidmode* vmode = glfwGetVideoMode (mon);
		window = glfwCreateWindow (
			vmode->width,
			vmode->height,
			"Extended GL Init",
			mon,
			NULL
			);
	}
	else
	{
		window = glfwCreateWindow (
			g_gl_width, g_gl_height, "Extended Init.", NULL, NULL
		);
	}
	if (!window) {
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return NULL;
	}
	glfwSetWindowSizeCallback (window, glfw_window_size_callback);
	glfwMakeContextCurrent (window);

	glfwWindowHint (GLFW_SAMPLES, 4);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit ();



	// get version info
	const GLubyte* renderer;
	const GLubyte* version;
	renderer = glGetString (GL_RENDERER); // get renderer string
	version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);
	gl_log ("renderer: %s\nversion: %s\n", renderer, version);
	log_gl_params ();
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	return window;
}
