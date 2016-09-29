#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "shaders.h"

#define PROJECT_NAME "OpenGL Game Experiment"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480


GLFWwindow* init_glfw( void )
{
	GLFWwindow* window = NULL;
	if (!glfwInit ()) {
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow ( WINDOW_WIDTH, WINDOW_HEIGHT, PROJECT_NAME, NULL, NULL );
	if (!window) {
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent (window);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit ();


	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

	return window;
}


int main( int argc, char** argv )
{
	GLFWwindow* window = init_glfw( );


	float points[] = {
   0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
	};

	GLuint vbo = 0;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	GLuint shader_program = createProgram( "./shaders/simple.vert", "./shaders/simple.frag" );
	if( shader_program == 0 ) //Program did not load correctly
		return -1;


	while ( !glfwWindowShouldClose(window) )
	{
	  // wipe the drawing surface clear
	  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  glUseProgram (shader_program);
	  glBindVertexArray (vao);
	  // draw points 0-3 from the currently bound VAO with current in-use shader
	  glDrawArrays (GL_TRIANGLES, 0, 3);
	  // update other events like input handling
	  glfwPollEvents ();
	  // put the stuff we've been drawing onto the display
	  glfwSwapBuffers (window);
	}

	glfwTerminate();
	return 0;
}
