#ifndef openGLRenderer_h
#define openGLRenderer_h
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "OpenGLObjects.h"

/* we will tell GLFW to run this function whenever the window is resized */
void glfw_window_size_callback (GLFWwindow* window, int width, int height);


#define g_gl_width 640
#define g_gl_height 480

/* we will tell GLFW to run this function whenever the window is resized */
void glfw_window_size_callback (GLFWwindow* window, int width, int height);

GLFWwindow*  CreateGLFWWindow(bool full_screen);

/* start a new log file. put the time and date at the top */
/* we will tell GLFW to run this function whenever it finds an error */
void glfw_error_callback (int error, const char* description);

/* we can use a function like this to print some GL capabilities of our adapter
to the log file. handy if we want to debug problems on other people's computers
*/
void log_gl_params ();

/* we will use this function to update the window title with a frame rate */
void _update_fps_counter (GLFWwindow* window);

#endif
