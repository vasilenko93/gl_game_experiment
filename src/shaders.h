#ifndef _SHADERS_H_
#define _SHADERS_H_

#include <GL/glew.h>

GLuint openVertexShader( char* pathname );
GLuint openFragmentShader( char* pathname );
char* readFile( char* pathname );

GLuint createProgram( char* vertexPath, char* fragmentPath );

#endif
