#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
// GLFW µµ Æ÷ÇÔ
#include <GLFW/glfw3.h>
#include <fstream>
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

