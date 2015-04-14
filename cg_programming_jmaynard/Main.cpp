#include "Application.h"

GLFWwindow* window = NULL;

int InitWindowFailed() {
	if(glfwInit() == GLFW_FAIL) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return EXIT_WITH_ERROR;
	}

	glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// gets working on mac...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old open gl we want the new...

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME,NULL,NULL); 

	if(window == NULL) {
		fprintf(stderr, "Failed to create/open GLFW window\n");
		glfwTerminate();
		return EXIT_WITH_ERROR;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window , GLFW_STICKY_KEYS, GL_TRUE);
	return EXIT_WITH_SUCCESS;
}






int InitGlewFailed() {
	glewExperimental = true;	// Has to do with core profile.
	if(glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return EXIT_WITH_ERROR;
	}

}



int main() {
	if(InitWindowFailed() | InitGlewFailed()) {
		return EXIT_WITH_ERROR;
	}

	do{

		//Update();
		//Render();
		glfwSwapBuffers(window);
		glfwPollEvents();

	}while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	


	return EXIT_WITH_SUCCESS;
}