// Include standard headers
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/text2D.hpp>

#include "scene.hpp"


int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Task 03 - Shooter", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	Scene scene;

	initText2D("Holstein.DDS");

	double previous = glfwGetTime();
	double shoot_time = 0;
	double update_lag = 0;
	double fps_lag = 0;
	double SEC_PER_UPDATE = 0.025; // 40 updates per second
	int fps = 0;
	int tick = 0;
	int score = 0;
	char stat_text[32] = {};

    do{
    	double current = glfwGetTime();
    	double elapsed = current - previous;
    	previous = current;
    	update_lag += elapsed;
    	fps_lag += elapsed;
    	++fps;

		// Handle input 
		computeMatricesFromInputs();

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetTime() - shoot_time > 0.1)
		{
			shoot_time = glfwGetTime();
			scene.shoot(getCameraPosition(), getCameraDirection() * 0.3f);
		}

		while (update_lag >= SEC_PER_UPDATE)
		{
			scene.update(tick);

			int curr_score = scene.checkCollisions();
			if (curr_score > 0)
			{
				score += curr_score;
				sprintf(stat_text, "FPS: %d SCORE: %d", fps, score);
			}

			update_lag -= SEC_PER_UPDATE;
			++tick;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.render(getViewMatrix(), getProjectionMatrix());

		// Print statistics
		if (fps_lag >= 1.0)
		{
			sprintf(stat_text, "FPS: %d SCORE: %d", fps, score);
			fps = 0;
			fps_lag -= 1.0;
		}

		printText2D(stat_text, 10, 570, 20);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0);

	glDeleteVertexArrays(1, &vertexArrayID);

	cleanupText2D();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

