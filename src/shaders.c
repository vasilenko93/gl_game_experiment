#include "shaders.h"

#include <stdio.h>
#include <stdlib.h>

GLuint openVertexShader( char* pathname )
{
    GLuint vertex_shader;
    const GLchar *source = (const GLchar *) readFile( pathname );

    if( !source )
        return 0;

    vertex_shader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertex_shader, 1, &source, NULL );
    glCompileShader( vertex_shader );

    free( (GLchar*) source );

    return vertex_shader;
}

GLuint openFragmentShader( char* pathname )
{
    GLuint fragment_shader;
    const GLchar *source = (const GLchar *) readFile( pathname );

    if( !source )
        return 0;

    fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragment_shader, 1, &source, NULL );
    glCompileShader( fragment_shader );

    free( (GLchar*) source );

    return fragment_shader;
}

char* readFile( char* pathname )
{
    char* text = NULL;
    long filesize;

    FILE* fd = fopen( pathname, "r" );

    fseek(fd, 0, SEEK_END);
    filesize = ftell(fd);
    rewind(fd);

    if( filesize == 0 )
    {
        fclose( fd );
        return NULL;
    }

    text = malloc( (filesize + 1) * sizeof(*text) );

    int read = fread( text, filesize, 1, fd );
    text[filesize] = '\0';

    fclose( fd );
    return text;
}


GLuint createProgram( char* vertexPath, char* fragmentPath )
{
    GLuint program;
    GLuint vertex_shader = openVertexShader(vertexPath);
    GLuint fragment_shader = openFragmentShader(fragmentPath);

    if( !vertex_shader || !fragment_shader )
        return 0;

    program = glCreateProgram( );
    glAttachShader( program, vertex_shader );
    glAttachShader( program, fragment_shader );
    glLinkProgram( program );

    glDeleteShader( vertex_shader );
    glDeleteShader( fragment_shader );

    return program;
}
