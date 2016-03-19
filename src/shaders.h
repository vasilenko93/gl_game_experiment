#ifndef _SHADERS_H_
#define _SHADERS_H_

#include <GL/glew.h>
#include <stdio.h>

GLuint openVertexShader( char* pathname );
GLuint openFragmentShader( char* pathname );

GLuint loadProgramme( GLuint vertex, GLuint fragment );


int freeShaders( GLuint* shader );

#endif
