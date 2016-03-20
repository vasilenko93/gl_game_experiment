#ifndef _SHADERS_H_
#define _SHADERS_H_

#include <GL/glew.h>

GLuint openVertexShader( char* pathname );
GLuint openFragmentShader( char* pathname );
char* readFile( char* pathname );

GLuint createProgramme( char* vertexPath, char* fragmentPath );

#endif
