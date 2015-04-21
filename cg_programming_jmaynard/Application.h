//Standard Headers...
#pragma once

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>


#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>






//Name spaces...

using namespace std;
using namespace glm;

#define GLFW_DLL
#define APP_NAME "<<James Maynard>>"
#define EXIT_WITH_ERROR -1
#define EXIT_WITH_SUCCESS 0 
#define OPEN_GL_VERSION 3 
#define ANTIALIASING 4
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define GLFW_FAIL 0

extern GLFWwindow* window;
extern GLint shaderStatus;
extern bool activeRef;
