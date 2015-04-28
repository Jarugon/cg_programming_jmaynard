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








GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Read in shader code
	string vertexShaderCode = "";
	ifstream vertexShaderStream(vertex_file_path, ios::in);

	if(vertexShaderStream.is_open()) {
		string line = "";
		while(getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	}


	string fragmentShaderCode = "";
	ifstream fragmentShaderStream(fragment_file_path, ios::in);

	if(fragmentShaderStream.is_open()) {
		string line = "";
		while(getline(fragmentShaderStream, line)) {
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength = 0;

	//Compile shaders here...
	printf("Compiling shader: %s\n", vertex_file_path);
	char const *vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	//Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	char* vertexShaderErrorMessage = new char[infoLogLength];
	glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &vertexShaderErrorMessage[0]);

	//Compile the Fragment Shader
	printf("Compiling fragment shader: %s\n", fragment_file_path);
	char const *fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	//Check Vertex Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	char* fragmentShaderErrorMessage = new char[infoLogLength];
	glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &fragmentShaderErrorMessage[0]);


	//Link the program...
	fprintf(stdout, "Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check the program...
	glGetProgramiv(programID,GL_LINK_STATUS, &result);
	glGetProgramiv(programID,GL_INFO_LOG_LENGTH, &infoLogLength);

	char *programErrorMessage = new char[glm::max(infoLogLength,int(1))];
	glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
	fprintf(stdout, "%s\n", &programErrorMessage[0]);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	delete(programErrorMessage);
	programErrorMessage = NULL;

	delete(vertexShaderErrorMessage);
	vertexShaderErrorMessage = NULL;

	delete(fragmentShaderErrorMessage);
	fragmentShaderErrorMessage = NULL;

	return programID;

}

int InitGlewFailed() {
	glewExperimental = true;	// Has to do with core profile.
	if(glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return EXIT_WITH_ERROR;
	}

}



GLuint& LoadTriangle() {
	static const GLfloat g_vertex_buffer_data[] = {

	-1.0f,-1.0f, 0.0f,
		1.0f,-1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint vertexBuffer = 0;
	glGenBuffers(1,&vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexBuffer;
}

GLuint& LoadQuad() {
	static GLfloat g_vertex_buffer_data[] = {

		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f

	};

	for(int i = 0, size = 18; i < size; ++i) {
		g_vertex_buffer_data[i] -= 0.5;

	}

	GLuint vertexBuffer = 0;
	glGenBuffers(1,&vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexBuffer;
}



GLuint& LoadColorQuad() {
	static GLfloat g_color_buffer_data[] = {

	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f

	};


	GLuint colorBuffer = 0;
	glGenBuffers(1,&colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	return colorBuffer;
}


mat4 RenderVertex(GLuint vertexBuffer, const vec3& position,const vec3& scaler) {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(
		0,			//Attribute Layout
		3,			//Elements in array
		GL_FLOAT,	// Each element is a type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array Buffer offset...
		);
	//mat4 identityMatrix = mat4(1.0f);
	mat4 positionMatrix = translate(mat4(1.0f), position);
	mat4 scaleMatrix = scale(positionMatrix, scaler);


	//return positionMatrix;
	return scaleMatrix;
}
void RenderColor(GLuint colorBuffer) {
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

	glVertexAttribPointer(
		1,			//Attribute Layout
		3,			//Elements in array
		GL_FLOAT,	// Each element is a type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array Buffer offset...
		);

	

}

/*void RenderTriangle(GLuint vertexBuffer) {
	RenderVertex(vertexBuffer);



	glDrawArrays(GL_TRIANGLES, 0 , 3);
	glDisableVertexAttribArray(0);

}*/
mat4 RenderQuad(GLuint vertexBuffer, const vec3& position, const vec3& scaler) {
	mat4 positionMatrix = RenderVertex(vertexBuffer, position, scaler);

	


	glDrawArrays(GL_TRIANGLES, 0 , 6);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	return positionMatrix;
	

}

float& getDeltaTime() {
	static float lastTime = glfwGetTime();
	float now = glfwGetTime();
	float deltaTime = now - lastTime;

	lastTime = now;
	return deltaTime;



}


int main() {
	if(InitWindowFailed() | InitGlewFailed()) {
		return EXIT_WITH_ERROR;
	}

	GLuint vertexArrayID = 0;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//Create and compile glsl program from shaders...
	GLuint programID = LoadShaders("Basic_Vertex_Shader.vertexshader", "BasicFragmentShader.fragmentshader");
	GLuint MVPMatrixID = glGetUniformLocation(programID, "MVP");
	float aspectRatio = SCREEN_WIDTH / (float) SCREEN_HEIGHT;
	mat4 projectionMatrix = perspective(FIELD_OF_VIEW, aspectRatio, Z_NEAR, Z_FAR);

	//GLuint triangleID = LoadTriangle();
	GLuint QuadID = LoadQuad();

	GLuint ColorID = LoadColorQuad();

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float deltaTime = getDeltaTime();
		glUseProgram(programID);
		//RenderTriangle(triangleID);
		mat4 viewMatrix= lookAt( 
		vec3(0,0,3),
		vec3(0,0,0),
		vec3(0,1,0)
		);
		static vec3 ballPosition = vec3(0);
		static vec3 ballVelocity = vec3(1.0f,0.0f,0.0f);

		ballPosition += ballVelocity *deltaTime;
		if( ballPosition.x >= 1.4f) {
			ballPosition.x = 1.4f;
			ballVelocity.x = -ballVelocity.x;
		}
		else if(ballPosition.x <= -1.4f) {
			ballPosition.x = -1.4f;
			ballVelocity.x = -ballVelocity.x;

		}
	

		
		mat4 MVPMatrix = projectionMatrix * viewMatrix * RenderQuad(QuadID,ballPosition, vec3(0.05));
		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);

		MVPMatrix = projectionMatrix * viewMatrix * RenderQuad(QuadID,vec3(1.5f,0.0f,0.0f), vec3(0.08f,0.5f,1.0f));
		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);

		MVPMatrix = projectionMatrix * viewMatrix * RenderQuad(QuadID,vec3(-1.5f,0,0), vec3(0.08f,0.5f,1.0f));
		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);

		RenderColor(ColorID);

		//Update();
		//Render();
		glfwSwapBuffers(window);
		glfwPollEvents();

	}while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	


	return EXIT_WITH_SUCCESS;
}