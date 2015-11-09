#include "log.h"


#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <iostream>
#include <time.h>
#include <assert.h>
#include <stdarg.h> // for doing gl_log() functions that work like printf()
#include <stdio.h>
#define GL_LOG_FILE "gl.log"
void log(log_level level, std::string message)
{
  std::cout << message;
}

bool restart_gl_log () {
	time_t now;
	char* date;
	FILE* file = fopen (GL_LOG_FILE, "w");

	if (!file) {
		fprintf (
			stderr,
			"ERROR: could not open GL_LOG_FILE log file %s for writing\n",
			GL_LOG_FILE
		);
		return false;
	}
	now = time (NULL);
	date = ctime (&now);
	fprintf (file, "GL_LOG_FILE log. local time %s", date);
	fprintf (file, "build version: %s %s\n\n", __DATE__, __TIME__);
	fclose (file);
	return true;
}


/* add a message to the log file. arguments work the same way as printf() */
bool gl_log (const char* message, ...) {
	va_list argptr;
	FILE* file = fopen (GL_LOG_FILE, "a");
	if (!file) {
		fprintf (
			stderr,
			"ERROR: could not open GL_LOG_FILE %s file for appending\n",
			GL_LOG_FILE
		);
		return false;
	}
	va_start (argptr, message);
	vfprintf (file, message, argptr);
	va_end (argptr);
	fclose (file);
	return true;
}

/* same as gl_log except also prints to stderr */
bool gl_log_err (const char* message, ...) {
	va_list argptr;
	FILE* file = fopen (GL_LOG_FILE, "a");
	if (!file) {
		fprintf (
			stderr,
			"ERROR: could not open GL_LOG_FILE %s file for appending\n",
			GL_LOG_FILE
		);
		return false;
	}
	va_start (argptr, message);
	vfprintf (file, message, argptr);
	va_end (argptr);
	va_start (argptr, message);
	vfprintf (stderr, message, argptr);
	va_end (argptr);
	fclose (file);
	return true;
}
