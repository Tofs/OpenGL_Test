#ifndef log_h
#define log_h


#include <string>
enum log_level { INFO, DEBUG, WARNING, ERROR };


void log(log_level levl, std::string message);

bool restart_gl_log ();


bool gl_log (const char* message, ...);
bool gl_log_err (const char* message, ...);
#endif
